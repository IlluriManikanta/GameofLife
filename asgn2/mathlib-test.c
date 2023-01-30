#include "mathlib.h"

#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "aebmrvnsh"

void help() {
    fprintf(stderr, "SYNOPSIS\n");
    fprintf(stderr, "   This is a test harness for the numerical library.\n\n");
    fprintf(stderr, "USAGE\n");
    fprintf(stderr, "   ./mathlib-testc [-aebmrvnsh]\n\n");
    fprintf(stderr, "OPTIONS\n");
    fprintf(stderr, "  -a   Runs all tests.\n");
    fprintf(stderr, "  -e   Runs e approximation test.\n");
    fprintf(stderr, "  -b   Runs bbp pi approximation test.\n");
    fprintf(stderr, "  -m   Runs Madhava pi approximation test.\n");
    fprintf(stderr, "  -r   Runs Euler pi approximation test.\n");
    fprintf(stderr, "  -v   Runs Viete pi approximation test.\n");
    fprintf(stderr, "  -n   Runs Newton square root approximation tests.\n");
    fprintf(stderr, "  -s   Enable printing of statistics to see computed terms and factors for "
                    "each tested function.\n");
    fprintf(stderr, "  -h   Help message detailing program usage.\n");
}

int main(int argc, char **argv) {
    int opt = 0;
    bool all = false;
    bool efile = false;
    bool madhava = false;
    bool euler = false;
    bool bbp = false;
    bool viete = false;
    bool newton = false;
    bool verbose = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': all = true; break;
        case 'e': efile = true; break;
        case 'm': madhava = true; break;
        case 'r': euler = true; break;
        case 'b': bbp = true; break;
        case 'v': viete = true; break;
        case 'n': newton = true; break;
        case 's': verbose = true; break;
        case 'h': help(); exit(0);
        default: help(); exit(1);
        }
    }

    if (verbose == true) {
        if (all == true) {

		double tmp_e = e();
            printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(tmp_e - M_E));
            printf("e() terms = %d\n", e_terms());

            double tmp_euler = pi_euler();
            printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_euler, M_PI,
                absolute(tmp_euler - M_PI));
            printf("pi_euler() terms = %d\n", pi_euler_terms());

            double tmp_bbp = pi_bbp();
            printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_bbp, M_PI,
                absolute(tmp_bbp - M_PI));
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());

            double tmp_madhava = pi_madhava();
            printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_madhava,
                M_PI, absolute(tmp_madhava - M_PI));
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());

            double tmp_v = pi_viete();
            printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_v, M_PI,
                absolute(tmp_v - M_PI));
            printf("pi_viete() terms = %d\n", pi_viete_factors());
            
            for (double i = 0.0; i <= 10.0; i += 0.1) {
            
                printf("sqrt_newton(%0.5lf) = %16.15lf, sqrt(%0.5lf) = %16.15lf, diff = %16.15lf\n",
                    i, sqrt_newton(i), i, sqrt(i), absolute(sqrt_newton(i) - sqrt(i)));
                printf("sqrt_newton_terms() = %d\n", sqrt_newton_iters());
            }
        }

        if (efile == true) {
        	double tmp_e = e();
            printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(tmp_e - M_E));
            printf("e() terms = %d\n", e_terms());
        }
        if (madhava == true) {
        	double tmp_madhava = pi_madhava();
            printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_madhava,
                M_PI, absolute(tmp_madhava - M_PI));
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
        if (euler == true) {
        	double tmp_euler = pi_euler();
            printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_euler, M_PI,
                absolute(tmp_euler - M_PI));
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
        if (bbp == true) {
        	double tmp_bbp = pi_bbp();
            printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_bbp, M_PI,
                absolute(tmp_bbp - M_PI));
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
        if (viete == true) {
        	double tmp_v = pi_viete();
            printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_v, M_PI,
                absolute(tmp_v - M_PI));
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
        if (newton == true) {
            for (double i = 0.0; i <= 10.0; i += 0.1) {
                printf("sqrt_newton(%0.5lf) = %16.15lf, sqrt(%0.5lf) = %16.15lf, diff = %16.15lf\n",
                    i, sqrt_newton(i), i, sqrt(i), absolute(sqrt_newton(i) - sqrt(i)));
                printf("sqrt_newton_terms() = %d\n", sqrt_newton_iters());
            }
        }
    }

    if (verbose == false) {
        if (all == true) {
            
		double tmp_e = e();
            printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(tmp_e - M_E));
           

            double tmp_euler = pi_euler();
            printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_euler, M_PI,
                absolute(tmp_euler - M_PI));
            

            double tmp_bbp = pi_bbp();
            printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_bbp, M_PI,
                absolute(tmp_bbp - M_PI));
            

            double tmp_madhava = pi_madhava();
            printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_madhava,
                M_PI, absolute(tmp_madhava - M_PI));
           

            double tmp_v = pi_viete();
            printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_v, M_PI,
                absolute(tmp_v - M_PI));
          
            
            for (double i = 0.0; i <= 10.0; i += 0.1) {
            
                printf("sqrt_newton(%0.5lf) = %16.15lf, sqrt(%0.5lf) = %16.15lf, diff = %16.15lf\n",
                    i, sqrt_newton(i), i, sqrt(i), absolute(sqrt_newton(i) - sqrt(i)));
                
            }
        }

        if (efile == true) {
        	double tmp_e = e();
            printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(tmp_e - M_E));
            
        }
        if (madhava == true) {
        	double tmp_madhava = pi_madhava();
            printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_madhava,
                M_PI, absolute(tmp_madhava - M_PI));
           
        }
        if (euler == true) {
        	double tmp_euler = pi_euler();
            printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_euler, M_PI,
                absolute(tmp_euler - M_PI));
           
        }
        if (bbp == true) {
        	double tmp_bbp = pi_bbp();
            printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_bbp, M_PI,
                absolute(tmp_bbp - M_PI));
           
        }
        if (viete == true) {
        	double tmp_v = pi_viete();
            printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", tmp_v, M_PI,
                absolute(tmp_v - M_PI));
            
        }
        if (newton == true) {
            for (double i = 0.0; i <= 10.0; i += 0.1) {
                printf("sqrt_newton(%0.5lf) = %16.15lf, sqrt(%0.5lf) = %16.15lf, diff = %16.15lf\n",
                    i, sqrt_newton(i), i, sqrt(i), absolute(sqrt_newton(i) - sqrt(i)));
               
            }
        }
        }
    return 0.0;
}
