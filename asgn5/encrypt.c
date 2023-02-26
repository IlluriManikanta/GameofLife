#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <time.h>

#include "numtheory.h"
#include "randstate.h"
#include "ss.h"

#define OPTIONS "i:o:n:vh"

//git test
int main(int argc, char **argv) {
    //initializing variables
    int opt = 0;
    FILE *inputfile = stdin;
    FILE *outputfile = stdout;
    FILE *public;
    char *public_key = "ss.pub";
    bool verbos = false;
    mpz_t n;
    mpz_init(n);
    char user_name[1024];

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {
        case 'i': inputfile = fopen(optarg, "r"); break;
        case 'o': outputfile = fopen(optarg, "w"); break;
        case 'n': public_key = optarg; break;
        case 'v': verbos = 1; break;
        case 'h':
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Encrypts data using SS encryption.\n");
            fprintf(stderr, "   Encrypted data is decrypted by the decrypt program.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./encrypt [OPTIONS]\n\n");
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
            fprintf(stderr, "   Encrypts data using SS encryption.\n");
            fprintf(stderr, "   Encrypted data is decrypted by the decrypt program.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./encrypt [OPTIONS]\n\n");
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

    public = fopen(public_key, "r");
    if (inputfile == NULL || outputfile == NULL || public == NULL) {
        fprintf(stderr, "File not opening\n");
        return 1;
    }

    ss_read_pub(n, user_name, public);

    if (verbos) {
        gmp_fprintf(stderr, "username: %s\n", user_name);

        gmp_fprintf(stderr, "n - modulus (%lu bits): %Zd\n", mpz_sizeinbase(n, 2), n);
    }

    ss_encrypt_file(inputfile, outputfile, n);
    fclose(public);
    mpz_clear(n);
}

/*
#include <stdio.h>
#include <getopt.h>
#include <gmp.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "numtheory.h"
#include "randtstae.h"
#include "ss.c"

#define OPTIONS "i:o:n:v:h"

int main(int argc, char **argv) {
    int opt = 0; // variable for getting option form array
    char *public_key_file = "ss.pub"; // public key name

    FILE *infile = stdin;
    FILE *outfile = stdout;
    FILE *public_key = NULL;
    bool verbose = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
            switch (opt) {
            
            
            }
    }

}

*/
