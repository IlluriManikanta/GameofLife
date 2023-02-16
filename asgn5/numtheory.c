//DONE NEED TO CHECK
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <gmp.h>
#include "randstate.h"
#include "numtheory.h"

//gmp_randstate_t state;
//git test
void gcd(mpz_t d, mpz_t a, mpz_t b){
	//the if statments check the corner cases of when b or are is equal to 0 and 1.
	//Mpz_cmp_ui check the parameters and will return 0 if b or a are equal to 0.
	if(mpz_cmp_ui(b, 0) == 0 || mpz_cmp_ui(b, 1) == 0 || mpz_cmp_ui(a, 0) == 0 || mpz_cmp_ui(a, 1) == 0) {
		mpz_set_ui(d, 0);
		return;
	}
	mpz_t val, vala, valb;
	mpz_inits(val, vala, valb, NULL);
	mpz_set(vala, a);
	mpz_set(valb, b);
	while(mpz_cmp_ui(valb, 0) != 0){
		mpz_set(val, valb);
		mpz_mod(valb, vala, valb);
		mpz_set(vala, val);
	}
	mpz_set(d, vala);
	mpz_clears(val, vala, valb);

}

void mod_inverse(mpz_t o, mpz_t a, mpz_t n){
	mpz_t r, rp, t, tp, q, qtp, qrp;
	mpz_t tempval, tempval_1;
	mpz_inits(r, rp, t, tp, q, qtp, qrp, NULL);
	mpz_inits(tempval, tempval_1, NULL);
	mpz_set(r, n);
	mpz_set(rp, a);
	mpz_set_ui(t, 0);
	mpz_set_ui(tp, 1);

	while(mpz_cmp_ui(rp, 0) != 0){
		mpz_fdiv_q(q, r, rp);
		mpz_set(tempval, r);
		mpz_set(r, rp);
		mpz_mul(qrp, q, rp);
		mpz_sub(rp, tempval, qrp);
		mpz_set(tempval_1, t);
		mpz_set(t, tp);
		mpz_mul(qtp, q, tp);
		mpz_sub(tp, tempval_1, qtp);
	}
	if(mpz_cmp_ui(r, 1) > 0 ){
		mpz_set_ui(o, 0);
		return;
	}
	if(mpz_cmp_ui(t, 0) < 0) {
        	mpz_add(t, t, n);
        	mpz_set(o, t);
        	return;
    }

    mpz_set(o, t);
    mpz_clears(r, rp, t, tp, q, qrp, qtp, tempval, tempval_1, NULL);

}

void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n){
	mpz_t v, p, ex, vp, ptemp, temp;
	mpz_inits(v, p, ex, vp, ptemp, temp, NULL );
	mpz_set_ui(v, 1);
	mpz_set(p, a);
	mpz_set(ex, d);
	while(mpz_cmp_ui(ex, 0) > 0){
	//	printf("pow_mod: while loop\n");
		if(mpz_divisible_ui_p(ex, 2) == 0){
		//printf("pow_mod: in if in while loop\n");
			mpz_mul(vp, v, p);
			mpz_mod(temp, vp, n);
			mpz_set(v, temp);
		}
	//	printf("pow_mod: end of if in while loop\n");
		mpz_mul(ptemp, p, p);
		mpz_mod(p, ptemp, n);
		mpz_fdiv_q_ui(ex, ex, 2);
//	printf("pow_mod: end of while loop\n");
		//break;
	}
	//printf("pow_mod: after while loop\n");
	mpz_set(o, v);
	//mpz_set(d, ex);
	mpz_clears(v, p, ex, vp, ptemp, temp, NULL);
	
}


    
bool is_prime(mpz_t n, uint64_t iters) {
	mpz_t res, val, n1, rm2, aval, yval, temp, s1, j, pm2; 
	mpz_inits(res, val, n1, rm2, aval, yval, temp, s1, j, pm2, NULL); 
	mpz_sub_ui (n1, n1, 1); 
	mpz_set(res, n1); 
	mpz_set_ui(val, 0); 
	mpz_mod_ui(rm2, res, 2); 
	while(mpz_cmp_ui(rm2, 1) != 0){ 
		//printf("is_prime while loop\n");
		mpz_fdiv_q_ui (res, res, 2); 
		mpz_mod_ui(rm2, res, 2); 
		mpz_add_ui (val, val, 1); 
	}
	mpz_sub_ui(s1, val, 1); 
	mpz_set_ui(pm2, 2); // setting 2 to mpz type because powmod only takes mpz types got help from TA for this part
	for(mpz_set_ui(temp, 1); mpz_cmp_ui(temp, iters); mpz_add_ui(temp, temp, 1)){ 
		//printf("is_prime for loop\n");
		mpz_urandomm(aval, state, n); 
		//printf("is_prime in for after urandomm\n");
		mpz_add_ui(aval, aval, 2);
		//printf("is_prime in for after mpz_add_ui\n"); 
		pow_mod(yval, aval, res, n); 
		//printf("is_prime in for after pow_mod\n");
		if((mpz_cmp(yval, n1) != 0 && mpz_cmp_ui(yval,1) != 0)){ 
			mpz_set_ui(j, 1);
		//	printf("is_prime if in for loop\n");
			while((mpz_cmp(j, s1) <= 0) && (mpz_cmp(yval, n1) != 0)){ 
		//		printf("is_prime while loop in for loop\n");
				pow_mod(yval, yval, pm2, n1); 
				if(mpz_cmp_ui(yval, 1) == 0){
					return false; 
				}
				mpz_add_ui(j, j, 1); 
			}
			if (mpz_cmp(yval, n1) != 0){ 
				return false; 
			}
		}
	}
	mpz_clears(res, val, n1, rm2, aval, yval, temp, s1, j, pm2, NULL);
	return true;
}


          
void make_prime(mpz_t p, uint64_t bits, uint64_t iters){
         // returning from the fucntions
	mpz_t val;
	mpz_init(val);
	int tf = 0;
	mpz_ui_pow_ui(val, 2, bits);
	while(tf == 0){
		//printf("inf in make prime\n");
		mpz_urandomb(p, state, bits);
		mpz_add(p, val, p);
		if(is_prime(p, iters) == true){
			tf = 1;
		}
		if(is_prime(p, iters) == false){
			tf = 0;
		}
	}
	mpz_clear(val);
	return;

}


