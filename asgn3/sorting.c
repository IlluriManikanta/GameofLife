#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "p:r:n:asbqHh"

Stats *stats;

const uint32_t heap = 1, quick = 2, shell = 3, batcher = 4, print = 5;

void print_number_of_elements(uint32_t *arr, uint32_t n_elements, uint32_t number_to_print) {
    uint32_t counter = 0;

    uint32_t value = number_to_print > n_elements ? n_elements : number_to_print;

    for (uint32_t i = 0; i < value; i++) {
        if (i == 0) {
            printf("%13" PRIu32, arr[i]);

            counter++;

            continue;
        }
        if (counter % 5 == 0) {

            printf("\n");
        }
        printf("%13" PRIu32, arr[i]);

        counter++;

        if (i == value - 1) {
            printf("\n");
        }
    }
}

void usage() {
    fprintf(stderr, "SYNOPSIS\n");
    fprintf(stderr, "   A collection of comparison-based sorting algorithms.\n\n");
    fprintf(stderr, "USAGE\n");
    fprintf(stderr, "   ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
    fprintf(stderr, "OPTIONS\n");
    fprintf(stderr, "   -H              Display program help and usage.\n");
    fprintf(stderr, "   -a              Enable all sorts.\n");
    fprintf(stderr, "   -s              Enable Shell Sort.\n");
    fprintf(stderr, "   -b              Enable Batcher Sort.\n");
    fprintf(stderr, "   -h              Enable Heap Sort.\n");
    fprintf(stderr, "   -q              Enable Quick Sort.\n");
    fprintf(stderr, "   -n length       Specify number of array elements (default: 100).\n");
    fprintf(stderr, "   -p elements     Specify number of elements to print (default: 100).\n");
    fprintf(stderr, "   -r seed         Specify random seed (default: 13371453).\n");
}

int main(int argc, char **argv) {
    Stats *statstics = (Stats *) malloc(sizeof(Stats));

    Set my_set = set_empty();

    int opt = 0;

    uint64_t seed = 13371453;

    srandom(seed);

    uint32_t n_elements = 100;

    uint32_t number_of_elements_to_print;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt)

        {
        case 'a':
            my_set = set_insert(my_set, heap);
            my_set = set_insert(my_set, shell);
            my_set = set_insert(my_set, quick);
            my_set = set_insert(my_set, batcher);
            break;

        case 's': my_set = set_insert(my_set, shell); break;

        case 'b': my_set = set_insert(my_set, batcher); break;

        case 'q': my_set = set_insert(my_set, quick); break;

        case 'h': my_set = set_insert(my_set, heap); break;

        case 'r':
            seed = atoi(optarg);

            srandom(seed);

            break;

        case 'n': n_elements = strtol(optarg, NULL, 10); break;

        case 'p': number_of_elements_to_print = strtol(optarg, NULL, 10); break;

        case 'H': usage(); exit(0);
        default: usage(); exit(1);
        }
    }

    uint32_t *arr = (uint32_t *) malloc(n_elements * sizeof(uint32_t));

    srandom(seed);

    if (set_member(my_set, shell)) {
        srandom(seed);

        for (uint32_t i = 0; i < n_elements; i++)

        {
            arr[i] = (uint32_t) (random() & (0x3FFFFFFF));
        }
        shell_sort(statstics, arr, n_elements);

        printf("Shell sort, %u elements, %lu moves, %lu compares\n", n_elements, statstics->moves,
            statstics->compares);

        print_number_of_elements(arr, n_elements, number_of_elements_to_print);

        reset(statstics);
    }

    if (set_member(my_set, batcher)) {
        srandom(seed);

        for (uint32_t i = 0; i < n_elements; i++)

        {
            arr[i] = (uint32_t) (random() & (0x3FFFFFFF));
        }
        batcher_sort(statstics, arr, n_elements);

        printf("Batcher Sort, %u elements, %lu moves, %lu compares\n", n_elements, statstics->moves,
            statstics->compares);

        print_number_of_elements(arr, n_elements, number_of_elements_to_print);

        reset(statstics);
    }

    if (set_member(my_set, heap)) {
        srandom(seed);

        for (uint32_t i = 0; i < n_elements; i++)

        {
            arr[i] = (uint32_t) (random() & (0x3FFFFFFF));
        }
        heap_sort(statstics, arr, n_elements);

        printf("Heap Sort, %u elements, %lu moves, %lu compares\n", n_elements, statstics->moves,
            statstics->compares);

        print_number_of_elements(arr, n_elements, number_of_elements_to_print);

        reset(statstics);
    }

    if (set_member(my_set, quick)) {
        srandom(seed);

        for (uint32_t i = 0; i < n_elements; i++)

        {
            arr[i] = (uint32_t) (random() & (0x3FFFFFFF));
        }
        quick_sort(statstics, arr, n_elements);

        printf("Quick Sort, %u elements, %lu moves, %lu compares\n", n_elements, statstics->moves,
            statstics->compares);

        print_number_of_elements(arr, n_elements, number_of_elements_to_print);

        reset(statstics);
    }

    free(arr);

    free(statstics);

    return 0;
}
