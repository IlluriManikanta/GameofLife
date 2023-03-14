//DONE
#include "code.h"
#include "io.h"
#include "trie.h"
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

//created this function to calculate bit lenght, Idea was derived from previous quarter work.
int bit_length(uint16_t code) {
    int bitlen = 0;

    while (code > 0) {
        bitlen++;
        code = code >> 1;
    }
    return bitlen;
}

int main(int argc, char *argv[]) {
    int options = 0;
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    bool verbose = false;
    while ((options = getopt(argc, argv, "hvi:o:")) != -1) {
        switch (options) {
        case 'v': verbose = true; break;
        case 'i': infile = open(optarg, O_RDONLY | O_WRONLY | O_RDWR); break;
        case 'o': outfile = open(optarg, O_RDONLY | O_WRONLY | O_RDWR); break;
        case 'h':
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Decompresses files with the LZ78 decompression algorithm.\n");
            fprintf(stderr, "   Used with files compressed with the corresponding encoder.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./decode [-vh] [-i input] [-o output]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -v          Display decompression statistics\n");
            fprintf(stderr, "   -i input    Specify input to decompress (stdin by default)\n");
            fprintf(stderr,
                "   -o output   Specify output of decompressed input (stdout by default)\n");
            fprintf(stderr, "   -h          Display program usage\n");
            return 0;
        default:
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Decompresses files with the LZ78 decompression algorithm.\n");
            fprintf(stderr, "   Used with files compressed with the corresponding encoder.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./decode [-vh] [-i input] [-o output]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -v          Display decompression statistics\n");
            fprintf(stderr, "   -i input    Specify input to decompress (stdin by default)\n");
            fprintf(stderr,
                "   -o output   Specify output of decompressed input (stdout by default)\n");
            fprintf(stderr, "   -h          Display program usage\n");
            return 1;
        }
    }
    FileHeader header = { 0, 0 };
    read_header(infile, &header);

    if (header.magic != MAGIC) {
        fprintf(stderr, "Not the correct Magic number.\n");
        close(infile);
        close(outfile);
        return 1;
    }

    fchmod(outfile, header.protection);

    WordTable *table = wt_create();
    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = START_CODE;

    while ((read_pair(infile, &curr_code, &curr_sym, bit_length(next_code)))) {
        table[next_code] = word_append_sym(table[curr_code], curr_sym);
        write_word(outfile, table[next_code]);
        next_code += 1;

        if (next_code == MAX_CODE) {
            wt_reset(table);
            next_code = START_CODE;
        }
    }

    flush_words(outfile);

    if (verbose) {
        double saving = 1.0
                        - ((float) !(total_bits % 8) ? (total_bits / 8)
                                                     : (total_bits / 8) + 1 / (float) total_syms);
        fprintf(stderr, "Compressed file size: %" PRIu64 " bytes\n",
            !(total_bits % 8) ? (total_bits / 8) : (total_bits / 8) + 1);
        fprintf(stderr, "Uncompressed file size: %" PRIu64 " bytes\n", total_syms);
        fprintf(stderr, "Space saving: %.2f%%\n", 100 * saving);
    }
}
