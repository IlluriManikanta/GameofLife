#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "heap.h"
#include "stats.h"
#include "set.h"

#include "batcher.h"
#include "stats.h"
#include "shell.h"
#include "quick.h"

#define OPTIONS "p:r:n:asbqHh"


#define SHELL_SORT 0
#define BATCHER_SORT 1
#define QUICK_SORT 2
#define HEAP_SORT 3

int main(int argc, char **argv) {

    Stats *test = (Stats *)malloc(sizeof(Stats));
    int opt = 0;
    uint64_t random_seed = 13371453;
    srandom(random_seed);
    uint32_t len = 100;
    uint32_t ele = 100;
    Set my_set = set_empty();

    while((opt = getopt(argc,argv, OPTIONS)) != -1){

        switch(opt){
        case 'a':
            my_set = set_insert(my_set, SHELL_SORT);
            my_set = set_insert(my_set, BATCHER_SORT);
            my_set = set_insert(my_set, QUICK_SORT);
            my_set = set_insert(my_set, HEAP_SORT);
            break;
       
        case 's':
            my_set = set_insert(my_set, SHELL_SORT);
            break;
        
        case 'b':
            my_set = set_insert(my_set, BATCHER_SORT);
            break;
        
        case 'q':
            my_set = set_insert(my_set, QUICK_SORT);
            break;
        
        case 'h':
            my_set = set_insert(my_set, HEAP_SORT);
            break;
        
        case 'r':
            random_seed = strtoul(optarg, NULL, 10);
            break;
        
        case 'n':
            len = strtoul(optarg, NULL, 10);
            break;
        
        case 'p':
            ele = strtoul(optarg, NULL, 10);
        break;
        
        case 'H':
        printf("SYNOPSIS\n");
    printf("   A collection of comparison-based sorting algorithms.\n\n");
    printf("USAGE\n");
    printf("   ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
    printf("OPTIONS\n");
    printf("   -H              Display program help and usage.\n");
    printf("   -a              Enable all sorts.\n");
    printf("   -s              Enable Shell Sort.\n");
    printf("   -b              Enable Batcher Sort.\n");
    printf("   -h              Enable Heap Sort.\n");
    printf("   -q              Enable Quick Sort.\n");
    printf("   -n length       Specify number of array elements (default: 100).\n");
    printf("   -p elements     Specify number of elements to print (default: 100).\n");
    printf("   -r seed         Specify random seed (default: 13371453).\n");
        
        break;
        
        case '?':
        printf("SYNOPSIS\n");
    printf("   A collection of comparison-based sorting algorithms.\n\n");
    printf("USAGE\n");
    printf("   ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
    printf("OPTIONS\n");
    printf("   -H              Display program help and usage.\n");
    printf("   -a              Enable all sorts.\n");
    printf("   -s              Enable Shell Sort.\n");
    printf("   -b              Enable Batcher Sort.\n");
    printf("   -h              Enable Heap Sort.\n");
    printf("   -q              Enable Quick Sort.\n");
    printf("   -n length       Specify number of array elements (default: 100).\n");
    printf("   -p elements     Specify number of elements to print (default: 100).\n");
    printf("   -r seed         Specify random seed (default: 13371453).\n");
        return 1;
        }
    }
    uint32_t *arr = (uint32_t *)malloc(len * sizeof(uint32_t));
    srandom(random_seed);
    uint32_t val = 0;
    uint32_t i;
    if (set_member(my_set, SHELL_SORT) == 1 && set_member(my_set, BATCHER_SORT) == 1){

        for (uint32_t i = 0; i < len; i++) {
            arr[i] = (uint32_t)(random() & ~((1 << 30) | (1 << 31)));
        }
        batcher_sort(test, arr, len);
        printf("Batcher Sort, %u elements, %lu move, %lu compares\n", len, test -> moves, test -> compares);

        if (ele > len){
            i = len;
        } else {
            i = ele;
        }
    for (uint32_t x = 0; x < i; x++) {
        if (x == 0) {
            val += 1;           
            printf("%13" PRIu32, arr[x]);
            continue;
        }
        if (val % 5 == 0) {
            printf("\n");
        }
        printf("%13" PRIu32, arr[x]);
        val += 1;
        if (x == len -1) {
            printf("\n");
            }
    }
    reset(test);
    srandom(random_seed);

    for (uint32_t i = 0; i < len; i++) {
            arr[i] = (uint32_t)(random() & ~((1 << 30) | (1 << 31)));
    }
    heap_sort(test, arr, len);
    printf("Heap Sort, %u elements, %lu move, %lu compares\n", len, test -> moves, test -> compares);

    val = 0;
    if (ele > len){
        i = len;
    } else {
        i = ele;
    }
    for (uint32_t x = 0; x < i; x++) {
        if (x == 0) {
            val += 1;
            printf("%13" PRIu32, arr[x]);
            continue;
        }
        if (val % 5 == 0) {
            printf("\n");
        }
        printf("%13" PRIu32, arr[x]);
        val += 1;
        if (x == len -1) {
            printf("\n");
        }
    }
    reset(test);
    srandom(random_seed);

    for (uint32_t i = 0; i < len; i++) {
            arr[i] = (uint32_t)(random() & ~((1 << 30) | (1 << 31)));
    }
    quick_sort(test, arr, len);
    printf("Quick Sort, %u elements, %lu move, %lu compares\n", len, test -> moves, test -> compares);
    val = 0;

    if (ele > len){
        i = len;
    } else {
        i = ele;
    }
    for (uint32_t x = 0; x < i; x++) {
        if (x == 0) {
            val += 1;
            printf("%13" PRIu32, arr[x]);
            continue;
        }
        if (val % 5 == 0) {
            printf("\n");
        }
        printf("%13" PRIu32, arr[x]);
        val += 1;
        if (x == len -1) {
            printf("\n");
        }
    }
    reset(test);
    srandom(random_seed);

    for (uint32_t i = 0; i < len; i++) {
             arr[i] = (uint32_t)(random() & ~((1 << 30) | (1 << 31)));
    }
    shell_sort(test, arr, len);
    printf("Shell Sort, %u elements, %lu move, %lu compares\n", len, test -> moves, test -> compares);
    val = 0;

    if (ele > len){
        i = len;
    } else {
        i = ele;
    }
    for (uint32_t x = 0; x < i; x++) {
        if (x == 0) {
            val += 1;
            printf("%13" PRIu32, arr[x]);
            continue;
        }
        if (val % 5 == 0) {
            printf("\n");
        }
        printf("%13" PRIu32, arr[x]);
        val += 1;
        if (x == len -1) {
            printf("\n");
        }
    }
    reset(test);
    srandom(random_seed);
    }

    else if (set_member(my_set, SHELL_SORT) == 1){
        for (uint32_t i = 0; i < len; i++) {
            arr[i] = (uint32_t)(random() & ~((1 << 30) | (1 << 31)));
        }
        shell_sort(test, arr, len);
        printf("Shell Sort, %u elements, %lu move, %lu compares\n", len, test -> moves, test -> compares);
        //print
        val = 0;
        if (ele > len){
            i = len;
        } else {
            i = ele;
        }
        for (uint32_t x = 0; x < i; x++) {
            if (x == 0) {
                val += 1;
                printf("%13" PRIu32, arr[x]);
                continue;
            }
            if (val % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, arr[x]);
            val += 1;
            if (x == len -1) {
                printf("\n");
            }
        }

    }

    else if (set_member(my_set, BATCHER_SORT) == 1) {
        for (uint32_t i = 0; i < len; i++) {
            arr[i] = (uint32_t)(random() & ~((1 << 30) | (1 << 31)));
        }
        batcher_sort(test, arr, len);
        printf("Batcher Sort, %u elements, %lu move, %lu compares\n", len, test -> moves, test -> compares);
        //print
        val = 0;

        if (ele > len){
            i = len;
        } else {
            i = ele;
        }
        for (uint32_t x = 0; x < i; x++) {
            if (x == 0) {
                val += 1;
                printf("%13" PRIu32, arr[x]);
                continue;
            }
            if (val % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, arr[x]);
            val += 1;
            if (x == len -1) {
                printf("\n");
            }
        }
    }

    else if (set_member(my_set, QUICK_SORT) == 1) {
        for (uint32_t i = 0; i < len; i++) {
            arr[i] = (uint32_t)(random() & ~((1 << 30) | (1 << 31)));
        }
        quick_sort(test, arr, len);
        printf("Quick Sort, %u elements, %lu move, %lu compares\n", len, test -> moves, test -> compares);
        //print
        val = 0;

        if (ele > len){
            i = len;
        } else {
            i = ele;
        }
        for (uint32_t x = 0; x < i; x++) {
            if (x == 0) {
                val += 1;
                printf("%13" PRIu32, arr[x]);
                continue;
            }
            if (val % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, arr[x]);
            val += 1;
            if (x == len -1) {
                printf("\n");
            }
        }
    }

    else if (set_member(my_set, HEAP_SORT) == 1) {
        for (uint32_t i = 0; i < len; i++) {
            arr[i] = (uint32_t)(random() & ~((1 << 30) | (1 << 31)));
        }
        heap_sort(test, arr, len);
        printf("\n");
        printf("Heap Sort, %u elements, %lu move, %lu compares\n", len, test -> moves, test -> compares);
        //print
        val = 0;

        if (ele > len){
            i = len;
        } else {
            i = ele;
        }
        for (uint32_t x = 0; x < i; x++) {
            if (x == 0) {
                val += 1;
                printf("%13" PRIu32, arr[x]);
                continue;
            }
            if (val % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, arr[x]);
            val += 1;
            if (x == len -1) {
                printf("\n");
            }
        }
    }
    return 0;      
}


