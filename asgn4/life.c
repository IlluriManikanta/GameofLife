#include "universe.h"

#include <inttypes.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#define DELAY   50000
#define OPTIONS "tsn:i:o:h"

int main(int argc, char **argv) {
    //Setting vars
    bool toroidal = false;
    bool silent = false;
    uint32_t generations = 100;
    FILE *in_file = stdin;
    FILE *out_file = stdout;

    //Will initiate the switch cases
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': toroidal = true; break;
        case 's': silent = true; break;
        case 'n': generations = atoi(optarg); break;
        case 'i': in_file = fopen(optarg, "r"); break;
        case 'o': out_file = fopen(optarg, "w"); break;
        case 'h':
            printf("SYNOPSIS\n");
            printf("    Conway's Game of Life\n");
            printf("\nUSAGE\n");
            printf("    ./life tsn:i:o:h\n");
            printf("\nOPTIONS\n");
            printf("    -t             Create your universe as a toroidal\n");
            printf("    -s             Silent - do not use animate the evolution\n");
            printf("    -n {number}    Number of generations [default: 100]\n");
            printf("    -i {file}      Input file [default: stdin]\n");
            printf("    -o {file}      Output file [default: stdout]\n");
            return EXIT_SUCCESS;
        default:
            printf("SYNOPSIS\n");
            printf("    Conway's Game of Life\n");
            printf("\nUSAGE\n");
            printf("    ./life tsn:i:o:h\n");
            printf("\nOPTIONS\n");
            printf("    -t             Create your universe as a toroidal\n");
            printf("    -s             Silent - do not use animate the evolution\n");
            printf("    -n {number}    Number of generations [default: 100]\n");
            printf("    -i {file}      Input file [default: stdin]\n");
            printf("    -o {file}      Output file [default: stdout]\n");
            return EXIT_FAILURE;
        }
    }

    //Checks if in_file is empty
    if (in_file == NULL) {
        printf("***Cannot Open File***\n");
        return 1;
    }

    //Checks if the input is a number and if the count is not equal to 2 because you need two numbers from file
    uint32_t rows, cols;
    if (fscanf(in_file, "%" SCNu32 " %" SCNu32, &rows, &cols) != 2) {
        printf("***Incorrect Data***\n");
        return 1;
    }

    //Creating the Universes
    Universe *uni_A = uv_create(rows, cols, toroidal);
    if (!uni_A) {
        fprintf(stderr, "***Error Allocating Memory***\n");
        fclose(in_file);
        fclose(out_file);
        uv_delete(uni_A);
        return EXIT_FAILURE;
    }

    Universe *uni_B = uv_create(rows, cols, toroidal);
    if (!uni_B) {
        fprintf(stderr, "***Error Allocating Memory***\n");
        fclose(in_file);
        fclose(out_file);
        uv_delete(uni_A);
        uv_delete(uni_B);
        return EXIT_FAILURE;
    }

    //Checks if the Universe if getting populated-
    if (!uv_populate(uni_A, in_file)) {
        printf("***Cannot Populate File***\n");
    }

    //Making the screen for curses
    if (!silent) {

        initscr();
        curs_set(false);
    }
    //Iterates through the generations while gen is less than 100 generations
    uint32_t gen = 0;
    while (gen < generations) {
        uint32_t uni_rows = uv_rows((gen % 2 ? uni_A : uni_B));
        uint32_t uni_cols = uv_cols((gen % 2 ? uni_A : uni_B));
        //Checks if case s was triggered
        if (!silent) {
            clear();
            //Iterates through cells using a nested loop and prints
            for (uint32_t row = 0; row < uni_rows; row++) {
                for (uint32_t col = 0; col < uni_cols; col++) {
                    if (uv_get_cell(uni_A, row, col)) {
                        mvaddch(row, col, 'o');
                    }
                }
            }
            if (!silent) {
                refresh();
                usleep(DELAY);
            }
        }
        //Iterates through the cells and places them in a swapped universe
        for (uint32_t row = 0; row < uni_rows; row++) {
            for (uint32_t col = 0; col < uni_cols; col++) {
                uint32_t live = uv_census(uni_A, row, col);

                if (uv_get_cell(uni_A, row, col)) {
                    if (live < 2 || live > 3) {

                        uv_dead_cell(uni_B, row, col);

                    } else {
                        uv_live_cell(uni_B, row, col);
                    }

                } else {
                    if (live != 3) {
                        uv_dead_cell(uni_B, row, col);

                    } else {

                        uv_live_cell(uni_B, row, col);
                    }
                }
            }
        }
        Universe *temp = uni_A;
        uni_A = uni_B;
        uni_B = temp;
        gen++;
    }

    endwin();
    uv_print(uni_A, out_file);

    //Closes files if they have data in them and deletes the universes
    if (in_file != NULL) {
        fclose(in_file);
    }
    if (out_file != NULL) {
        fclose(out_file);
    }
    uv_delete(uni_A);
    uv_delete(uni_B);
}
