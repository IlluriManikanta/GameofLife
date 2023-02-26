#include <getopt.h>
#include <stdbool.h>
#include "numtheory.h"
#include "randstate.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include <gmp.h>
#include "ss.h"

#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv) {
    int opt = 0;
    bool check = false;
    FILE *inputfile = stdin;
    FILE *outputfile = stdout;
    FILE *private;
    char *privatefile = "ss.priv";
    mpz_t pq, d;
    mpz_inits(pq, d, NULL);

    while ((opt = getopt(argc, argv, "i:o:n:vh")) != -1) {
        switch (opt) {
        case 'i': inputfile = fopen(optarg, "r"); break;
        case 'o': outputfile = fopen(optarg, "w"); break;
        case 'n': privatefile = optarg; break;
        case 'v': check = true; break;
        case 'h':
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Decrypts data using SS decryption.\n");
            fprintf(stderr, "   Encrypted data is decrypted by the decrypt program.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./decrypt [OPTIONS]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr, "   -i infile       Input file of data to encrypt (default: stdin).\n");
            fprintf(
                stderr, "   -o outfile      Output file for encrypted data (default: stdout).\n");
            fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
            return 0;
        case '?':
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Decrypts data using SS decryption.\n");
            fprintf(stderr, "   Encrypted data is decrypted by the decrypt program.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./decrypt [OPTIONS]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr, "   -i infile       Input file of data to encrypt (default: stdin).\n");
            fprintf(
                stderr, "   -o outfile      Output file for encrypted data (default: stdout).\n");
            fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
            return 1;
        }
    }

    private = fopen(privatefile, "r");
    if (inputfile == NULL || outputfile == NULL || private == NULL) {
        fprintf(stderr, "File not opening\n");
        return 1;
    }

    ss_read_priv(pq, d, private);
    if (check) {
        gmp_fprintf(stderr, "pq: (%zu bits) = %Zd\n", mpz_sizeinbase(pq, 2), pq);
        gmp_fprintf(stderr, "d: (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    ss_decrypt_file(inputfile, outputfile, d, pq);
    fclose(private);
    mpz_clears(pq, d, NULL);
}
