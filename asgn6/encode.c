//DONE
#include "code.h"
#include "io.h"
#include "trie.h"
#include <sys/stat.h>
#include <getopt.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
            return 0;
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
            return 1;
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

    uint8_t curr_sym = 0;
    uint8_t prev_sym = 0;
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
        double saving = 1.0 - ((float) !(total_bits % 8) ? (total_bits / 8) : (total_bits / 8) + 1 / (float) total_syms);
        fprintf(
            stderr, "Compressed file size: %" PRIu64 " bytes\n", !(total_bits % 8) ? (total_bits / 8) : (total_bits / 8) + 1);
        fprintf(stderr, "Uncompressed file size: %" PRIu64 " bytes\n", total_syms);
        fprintf(stderr, "Space saving: %.2f%%\n", 100 * saving);
    }

    return 0;
}

