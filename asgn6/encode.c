#include "code.h"
#include "io.h"
#include "trie.h"

#include <getopt.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

uint64_t length_of_the_byte(uint64_t bits) {
    return !(bits % 8) ? (bits / 8) : (bits / 8) + 1;
}

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
        case 'i':
            if ((infile = open(optarg, O_RDONLY | O_WRONLY | O_RDWR)) == -1) {
                fprintf(stderr, "Error : failed to open input file.\n");
                return EXIT_FAILURE;
            }
            break;
        case 'o':
            if ((outfile = open(optarg, O_RDONLY | O_WRONLY | O_RDWR)) == -1) {
                fprintf(stderr, "Error : failed to open output file.\n");
                close(infile);
                return EXIT_FAILURE;
            }
            break;
        case 'h':
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Compresses files using the LZ78 compression algorithm.\n");
            fprintf(
                stderr, "   Compressed files are decompressed with the corresponding decoder.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./encode [-vh] [-i input] [-o output]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -v          Display decompression statistics\n");
            fprintf(stderr, "   -i input    Specify input to compress (stdin by default)\n");
            fprintf(
                stderr, "   -o output   Specify output of compressed input (stdout by default)\n");
            fprintf(stderr, "   -h          Display program usage\n");
            return EXIT_SUCCESS;
        default:
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Compresses files using the LZ78 compression algorithm.\n");
            fprintf(
                stderr, "   Compressed files are decompressed with the corresponding decoder.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./encode [-vh] [-i input] [-o output]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -v          Display decompression statistics\n");
            fprintf(stderr, "   -i input    Specify input to compress (stdin by default)\n");
            fprintf(
                stderr, "   -o output   Specify output of compressed input (stdout by default)\n");
            fprintf(stderr, "   -h          Display program usage\n");
            return EXIT_FAILURE;
        }
    }
    struct stat statbuff;
    fstat(infile, &statbuff);
    fchmod(outfile, statbuff.st_mode);

    FileHeader header;
    header.magic = MAGIC;
    header.protection = statbuff.st_mode;

    write_header(outfile, &header);

    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    TrieNode *prev_node = NULL;

    uint8_t curr_sym = 0, prev_sym = 0;
    int next_code = START_CODE;

    while (read_sym(infile, &curr_sym)) {
        TrieNode *next_node = trie_step(curr_node, curr_sym);

        if (next_node) {
            prev_node = curr_node;
            curr_node = next_node;
        } else {
            write_pair(outfile, curr_node->code, curr_sym, bit_length(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code = next_code + 1;
        }

        if (next_code == MAX_CODE) {
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }

        prev_sym = curr_sym;
    }

    if (curr_node != root) {
        write_pair(outfile, prev_node->code, prev_sym, bit_length(next_code));
        next_code = (next_code + 1) % MAX_CODE;
    }

    write_pair(outfile, STOP_CODE, 0, bit_length(next_code));
    flush_pairs(outfile);

    trie_delete(root);
    close(infile);
    close(outfile);

    if (verbose) {
        double saving = 1.0 - ((float) length_of_the_byte(total_bits) / (float) total_syms);
        fprintf(
            stderr, "Compressed file size: %" PRIu64 " bytes\n", length_of_the_byte(total_bits));
        fprintf(stderr, "Uncompressed file size: %" PRIu64 " bytes\n", total_syms);
        fprintf(stderr, "Space saving: %.2f%%\n", 100 * saving);
    }

    return EXIT_SUCCESS;
}
