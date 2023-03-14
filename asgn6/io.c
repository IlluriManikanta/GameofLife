#include "io.h"
#include "code.h"
#include "endian.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Global varibales declared for later use
static uint8_t sym_buffer[BLOCK] = { 0 };
static int sym_index_val = 0;
static int bit_index_val = 0;
static uint8_t bit_buffer[BLOCK] = { 0 };
uint64_t total_syms = 0;
uint64_t total_bits = 0;

int read_bytes(int infile, uint8_t *buf, int to_read) {
    int fnl, bytes;
    fnl = 0;
    bytes = -1;
    while ((bytes != 0) && (fnl != to_read)) {
        bytes = read(infile, buf, to_read);
        fnl += bytes;
        buf += bytes;
    }
    return fnl;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {
    int fnl, bytes;
    fnl = 0;
    bytes = -1;
    while ((bytes != 0) && (fnl != to_write)) {
        bytes = write(outfile, buf, to_write);
        fnl += bytes;
        buf += bytes;
    }
    return fnl;
}

void read_header(int infile, FileHeader *header) {
    total_bits = total_bits + (sizeof(FileHeader) * 8);
    if (!little_endian()) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    read_bytes(infile, (uint8_t *) header, sizeof(FileHeader));
}

void write_header(int outfile, FileHeader *header) {
    total_bits = total_bits + (sizeof(FileHeader) * 8);
    if (!little_endian()) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    write_bytes(outfile, (uint8_t *) header, sizeof(FileHeader));
}

bool read_sym(int infile, uint8_t *sym) {
    static int finish = -1;
    int read_b;
    if (!sym_index_val) {
        read_b = read_bytes(infile, sym_buffer, BLOCK);
        if (read_b < BLOCK) {
            finish = read_b + 1;
        }
    }

    *sym = sym_buffer[sym_index_val];
    uint8_t sym_index_val_val = (sym_index_val + 1);
    sym_index_val = sym_index_val_val % BLOCK;
    if (sym_index_val != finish) {
        total_syms++;
    }
    if (sym_index_val == finish) {
        return false;
    } else {
        return true;
    }
}

void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    if (!little_endian()) {
        swap16(code);
    }

    int i = 0, j = 0;

    while (i < bitlen) {
        if (code >> (i % 16) & 1) {
            bit_buffer[bit_index_val / 8]
                |= (1 << (bit_index_val
                          % 8)); //Derived idea from last quarter cse13s with Prof. Ethan Miller
        }
        bit_index_val++;
        if (bit_index_val == 8 * BLOCK) {
            write_bytes(outfile, bit_buffer, BLOCK);
            memset(bit_buffer, 0, BLOCK);
            bit_index_val = 0;
        }
        i++;
    }
    while (j < 8) {
        if (sym >> (j % 8) & 1) {
            bit_buffer[bit_index_val / 8]
                |= (1 << (bit_index_val
                          % 8)); //Derived idea from last quarter cse13s with Prof. Ethan Miller
        }
        bit_index_val++;
        if (bit_index_val == 8 * BLOCK) {
            write_bytes(outfile, bit_buffer, BLOCK);
            memset(bit_buffer, 0, BLOCK);
            bit_index_val = 0;
        }
        j++;
    }
}

void flush_pairs(int outfile) {
    if (outfile) {
        int number_of_bytes = 0;
        if (bit_index_val % 8) {
            number_of_bytes = (bit_index_val / 8);
        } else {
            number_of_bytes = (bit_index_val / 8) + 1;
        }
        if (write_bytes(outfile, bit_buffer, number_of_bytes)) {
            return;
        }
    } else {
        exit(EXIT_FAILURE);
    }
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
    if (!infile) {
        exit(EXIT_FAILURE);
    } else {

        *code = 0, *sym = 0;
        int i = 0, j = 0;
        while (i < bitlen) {
            uint8_t calc = ((bit_buffer[bit_index_val / 8] >> (bit_index_val % 8)) & 1);
            if (!bit_index_val) {
                read_bytes(infile, bit_buffer, BLOCK);
            }

            *code = *code | calc << i;

            bit_index_val = (bit_index_val + 1) % (8 * BLOCK);
            i++;
        }

        while (j < 8) {
            uint8_t calc2 = ((bit_buffer[bit_index_val / 8] >> (bit_index_val % 8)) & 1);
            if (!bit_index_val) {
                read_bytes(infile, bit_buffer, BLOCK);
            }

            *sym = *sym | calc2 << j;
            bit_index_val = (bit_index_val + 1) % (8 * BLOCK);
            j++;
        }

        total_bits = total_bits + (bitlen + 8);

        if (!little_endian()) {
            *code = swap16(*code);
        }

        if (*code != STOP_CODE) {
            return true;
        } else {
            return false;
        }
    }
}

void write_word(int outfile, Word *w) {
    if (outfile) {
        if (w == NULL) {
            exit(EXIT_FAILURE);
        } else {
            uint32_t i = 0;
            while (i < w->len) {
                if (sym_index_val == BLOCK) {
                    write_bytes(outfile, sym_buffer, BLOCK);
                    sym_index_val = 0;
                }
                sym_buffer[sym_index_val] = w->syms[i];
                sym_index_val += 1;
                i++;
            }
            total_syms += w->len;
            return;
        }
    }
}

void flush_words(int outfile) {
    if (!outfile) {
        exit(EXIT_FAILURE);
    } else {
        write_bytes(outfile, sym_buffer, sym_index_val);
        return;
    }
}
