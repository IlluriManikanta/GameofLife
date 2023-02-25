//NEED TO FIX ERRORS
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <gmp.h>
#include "randstate.h"
#include "numtheory.h"

//DONE
void gcd(mpz_t g, const mpz_t a, const mpz_t b){
	//the if statments check the corner cases of when b or are is equal to 0 and 1.
	//Mpz_cmp_ui check the parameters and will return 0 if b or a are equal to 0.
	if(mpz_cmp_ui(b, 0) == 0 || mpz_cmp_ui(b, 1) == 0 || mpz_cmp_ui(a, 0) == 0 || mpz_cmp_ui(a, 1) == 0) {
		mpz_set_ui(g, 0);
		return;
	}
	mpz_t val, vala, valb;
	mpz_inits(vala, valb, val, NULL);
	mpz_set(vala, a);
	mpz_set(valb, b);
	//printf("%s\n", "before while loop c^^^^^^^^^^^^^^^");
        while(mpz_cmp_ui(valb, 0) != 0){
        //printf("%s\n", "inside while loop: -1------------------");
                mpz_set_ui(val, 0);
		mpz_set(val, valb);
		mpz_mod(valb, vala, valb);
		mpz_set(vala, val);
	//printf("%s\n", "end of while loop*************************");
	}
	//printf("%s\n", "after loop  while loop&&&&&&&&&&&&&&&&&&&&&&&&");
	mpz_set(g, vala);
	mpz_clears(vala, valb, val, NULL);

}


void mod_inverse(mpz_t o, const mpz_t a, const mpz_t n){
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

void pow_mod(mpz_t o, const mpz_t a, const mpz_t d, const mpz_t n){
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


    
bool is_prime(const mpz_t n, uint64_t iters) {
//if statments check if numbers are 2 and 3 are present, if so will automaticly return true
    if (mpz_cmp_ui(n, 2) == 0){
        return true;
    }
    if(mpz_cmp_ui(n, 3) == 0){
        return true;
    }
    if ((mpz_divisible_ui_p(n, 2) != 0)) {
        return false;
    }
//if statments check if numbers are 1 and 0 are present and automaticly return false
    if(mpz_cmp_ui(n, 1) == 0){
        return false;
    }
    if(mpz_cmp_ui(n, 0) == 0){
        return false;
    }    

    
    //declaring the variables
    mpz_t aval, yval, j, itter, res, powmod, nmin, prob;
    mpz_inits(aval, yval, j, itter, res, powmod, nmin, prob, NULL);
    
	//variables for bit calculation
	mp_bitcnt_t bit = 1;
	mp_bitcnt_t bitval;
	
	//calculating number n-1 bits
	mpz_sub_ui(nmin, n, 1); 
	
	int number = mpz_divisible_2exp_p(nmin, bit);
      
	while(number == 0){
	  bit++;
	  number = mpz_divisible_2exp_p(nmin, bit);
	}
	
        mpz_set_ui(prob, 1);
        mpz_mul_2exp(prob, prob, bit);
        mpz_cdiv_q(res, nmin, prob);
	
	
	for(mpz_set_ui(itter, 1); mpz_cmp_ui(itter, iters) < 0; mpz_add_ui(itter, itter, 1)){ 
		
		mpz_urandomm(aval, state, n); 
	
		mpz_add_ui(aval, aval, 2);
		
		pow_mod(yval, aval, res, n); 
		
		if((mpz_cmp_ui(yval, 1) != 0) && (mpz_cmp(yval, nmin) != 0)){ 
			mpz_set_ui(j, 1);
			bitval = bit - 1;
			
			while((mpz_cmp(yval, nmin) != 0) && (mpz_cmp_ui(j, bitval) <= 0)){ 
		
				mpz_set_ui(powmod, 2);
				pow_mod(yval, yval, powmod, nmin); 
				
				if(mpz_cmp_ui(yval, 1) == 0){
				        mpz_clears(aval, yval, j, itter, res, powmod, nmin, prob, NULL);
					return false; 
				}
				
				mpz_add_ui(j, j, 1); 
			}
			
			if (mpz_cmp(yval, nmin) != 0){ 
			        mpz_clears(aval, yval, j, itter, res, powmod, nmin, prob, NULL);
				return false; 
			}
		}
	}
	
	mpz_clears(aval, yval, j, itter, res, powmod, nmin, prob, NULL);
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

