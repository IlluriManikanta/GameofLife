#include <stdio.h>
#include "ss.h"
#include "numtheory.h"
#include "randstate.h"
#include <gmp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>


void ss_make_pub(mpz_t p, mpz_t q, mpz_t n, uint64_t nbits, uint64_t iters) {
    //DONE

    mpz_t q_minus_1;
    mpz_init(q_minus_1);
    uint64_t pbits = (random() % (((2 * nbits) / 5) - (nbits / 5) + 1)) + (nbits / 5);
    uint64_t qbits = nbits - (2 * pbits);

    make_prime(p, pbits, iters);
    make_prime(q, qbits, iters);
    mpz_sub_ui(q_minus_1, q, 1);

    while (mpz_cmp(q_minus_1, p) == 0 || mpz_cmp_ui(q_minus_1, 0) == 0) {
        make_prime(p, pbits, iters);
        make_prime(q, qbits, iters);
        mpz_sub_ui(q_minus_1, q, 1);
    }
    mpz_mul(n, p, p);
    mpz_mul(n, n, q);
    mpz_clear(q_minus_1);
}

void ss_make_priv(mpz_t d, mpz_t pq, const mpz_t p, const mpz_t q) {
    mpz_t gcd_value, p_min, q_min, n, min_mul, lambda;
    mpz_inits(gcd_value, p_min, q_min, n, min_mul, lambda, NULL);
    mpz_sub_ui(p_min, p, 1);
    mpz_sub_ui(q_min, q, 1);
    mpz_mul(pq, p, q);
    mpz_mul(n, pq, p);
    gcd(gcd_value, p_min, q_min);
    mpz_mul(min_mul, p_min, q_min);
    mpz_div(lambda, min_mul, gcd_value);
    mod_inverse(d, n, lambda);
    mpz_clears(gcd_value, p_min, q_min, n, min_mul, lambda, NULL);
}

//DONE
void ss_write_pub(const mpz_t n, const char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n%s\n", n, username);
}

//DONE
void ss_write_priv(const mpz_t pq, const mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n%Zx\n", pq, d);
}

//DONE
void ss_read_pub(mpz_t n, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n%s\n", n, username);
}

//DONE
void ss_read_priv(mpz_t pq, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n%Zx\n", pq, d);
}

//DONE
void ss_encrypt(mpz_t c, const mpz_t m, const mpz_t n) {
    pow_mod(c, m, n, n);
}

//DONE
void ss_decrypt(mpz_t m, const mpz_t c, const mpz_t d, const mpz_t pq) {
    pow_mod(m, c, d, pq);
}

void ss_encrypt_file(FILE *infile, FILE *outfile, const mpz_t n) {
 
  mpz_t m, fnl_ency;
    mpz_inits(m, fnl_ency, NULL);
    size_t k = ((0.5*mpz_sizeinbase(n, 2) - 1) / 8);
    uint8_t *a = (uint8_t *) (calloc(k, sizeof(uint8_t))); // got logic/syntax for malloc from sorting.c file n assighnment 4
    a[0] = 0xFF;
    size_t s;
    while (!feof(infile)) { //run until it enocunters the end of file
        s = fread(&a[1], 1, k - 1, infile);
        mpz_import(m, s + 1, 1, 1, 1, 0, a);
        ss_encrypt(fnl_ency, m, n);
        gmp_fprintf(outfile, "%Zx\n", fnl_ency);
    }
    free(a);
    mpz_clears(m, fnl_ency, NULL);
    
    
}

void ss_decrypt_file(FILE *infile, FILE *outfile, const mpz_t d, const mpz_t pq) {
    
    mpz_t m, c, fnl_decy;
    mpz_inits(m, c, fnl_decy, NULL);
    size_t k = (mpz_sizeinbase(pq, 2) - 1) / 8;
    uint8_t *a = (uint8_t *) malloc(
        k * sizeof(uint8_t)); // got logic/syntax for malloc from sorting.c file n assighnment 4
    a[0] = 0xFF;
    size_t s;
    while (!feof(infile)) {
        gmp_fscanf(infile, "%Zx\n", c);
        ss_decrypt(m, c, d, pq);
        mpz_export(a, &s, 1, 1, 1, 0, m);
        fwrite((a + 1), 1, s - 1, outfile);
    }
    mpz_clears(m, c, fnl_decy, NULL);
    
}

