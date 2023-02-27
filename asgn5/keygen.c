//DONE
#include <stdio.h>
#include "randstate.h"
#include "numtheory.h"
#include "ss.h"
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <gmp.h>
#include <sys/stat.h>

#define OPTIONS "b:i:n:d:svh"

int main(int argc, char **argv) {
    int opt = 0;
    int check = 0;
    uint64_t bitval = 256;
    uint64_t iters = 50;
    uint64_t seed = time(NULL);
    FILE *pub_file;
    FILE *prv_file;
    char *public_file = "ss.pub";
    char *private_file = "ss.priv";
    mpz_t p, q, pq, n, d;
    mpz_inits(p, q, pq, n, d, NULL);
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b': bitval = atoi(optarg); break;
        case 'i': iters = atoi(optarg); break;
        case 'n': *public_file = atoi(optarg); break;
        case 'd': *private_file = atoi(optarg); break;
        case 's':
            seed = atoi(optarg);
            randstate_init(seed);
            break;
        case 'v': check = 1; break;
        case 'h':
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Generates an SS public/private key pair.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./keygen [OPTIONS]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr,
                "   -b bits         Minimum bits needed for public key n (default: 256).\n");
            fprintf(stderr,
                "   -i iterations   Miller-Rabin iterations for testing primes (default: 50).\n");
            fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
            fprintf(stderr, "   -d pvfile       Private key file (default: ss.priv).\n");
            fprintf(stderr, "   -s seed         Random seed for testing.\n");
            return 0;
        case '?':
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Generates an SS public/private key pair.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./keygen [OPTIONS]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr,
                "   -b bits         Minimum bits needed for public key n (default: 256).\n");
            fprintf(stderr,
                "   -i iterations   Miller-Rabin iterations for testing primes (default: 50).\n");
            fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
            fprintf(stderr, "   -d pvfile       Private key file (default: ss.priv).\n");
            fprintf(stderr, "   -s seed         Random seed for testing.\n");
            return 1;
        }
    }
    pub_file = fopen(public_file, "w");
    prv_file = fopen(private_file, "w");
    if (pub_file == NULL || prv_file == NULL) {
        fprintf(stderr, "File cannot be opened");
        return 1;
    }

    fchmod(fileno(prv_file), 0600);
    randstate_init(seed);

    ss_make_pub(p, q, n, bitval, iters);

    ss_make_priv(d, pq, p, q);

    char *username = getenv("USERNAME");

    ss_write_pub(n, username, pub_file);

    ss_write_priv(pq, d, prv_file);

    if (check) {

        fprintf(stderr, "username: %s\n", username);
        gmp_fprintf(stderr, "p: (%zu bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_fprintf(stderr, "q: (%zu bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_fprintf(stderr, "n:  (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_fprintf(stderr, "pq: (%zu bits) = %Zd\n", mpz_sizeinbase(pq, 2), pq);
        gmp_fprintf(stderr, "d:  (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }
    fclose(pub_file);
    fclose(prv_file);
    mpz_clears(p, q, pq, n, d, NULL);
    randstate_clear();
}
