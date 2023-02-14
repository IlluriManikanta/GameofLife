#include "universe.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};
//Function to create universe
Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    Universe *u = (Universe *) malloc(sizeof(Universe));
    u->rows = rows;
    u->cols = cols;
    u->toroidal = toroidal;
    u->grid = (bool **) calloc(rows, sizeof(bool *));
    uint32_t i = 0;
    //While loop that checks if i < rows
    while (i < rows) {
        if (i > rows) {
            break;
        } else {
            //Allocating memory
            u->grid[i] = (bool *) calloc(cols, sizeof(bool));
        }
        //Increase counter
        i++;
    }
    return u;
}

//Deletes through free() and will set to NULL
void uv_delete(Universe *u) {
    for (uint32_t i = 0; i < u->rows; i++) {
        free(u->grid[i]);
    }
    free(u->grid);
    free(u);
    u = NULL;
}

//Will return rows
uint32_t uv_rows(Universe *u) {
    return u->rows;
}

//Will return cols
uint32_t uv_cols(Universe *u) {
    return u->cols;
}

//Will make cell live by seeting to true
void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    if ((r < u->rows && c < u->cols)) {
        u->grid[r][c] = true;
    } else {
        return;
    }
}

//Will make cell live by seeting to false
void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    if (r < u->rows && c < u->cols) {
        u->grid[r][c] = false;
    } else {
        return;
    }
}

//Will get cells
bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    if (r > u->rows || c > u->cols) {
        return false;
    } else {
        return u->grid[r][c];
    }
}

//will populate using fscanf
bool uv_populate(Universe *u, FILE *infile) {
    while (!feof(infile)) {
        uint32_t r;
        uint32_t c;
        if (fscanf(infile, "%" SCNu32 " %" SCNu32, &r, &c) != 2 && (r > u->rows || c > u->cols)) {
            return false;
        } else {
            uv_live_cell(u, r, c);
        }
    }
    return true;
}

//Will count the number of live members in the neighborhood
uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
    uint32_t counter = 0;

    uint32_t move[8][2] = {
        { -1, -1 },
        { -1, 0 },
        { -1, 1 },
        { 0, -1 },
        { 0, 1 },
        { 1, -1 },
        { 1, 0 },
        { 1, 1 },
    };

    for (uint32_t i = 0; i < 8; i++) {
        uint32_t row_move = move[i][0];
        uint32_t row = r + row_move;

        uint32_t col_move = move[i][1];
        uint32_t col = c + col_move;

        if (u->toroidal) {
            row = (row + u->rows) % u->rows;
            col = (col + u->cols) % u->cols;
        }
        if (row >= 0 && col >= 0 && row < u->rows && col < u->cols) {
            if (u->grid[row][col]) {

                counter += 1;
            } else {
                counter += 0;
            }
        }
    }
    return counter;
}

//Will print the "o" and the "." for life and dead respectively.
void uv_print(Universe *u, FILE *outfile) {
    for (uint32_t x = 0; x < u->cols; x++) {
        for (uint32_t y = 0; y < u->rows; y++) {
            if (u->grid[x][y]) {
                fprintf(outfile, "o");
            } else {
                fprintf(outfile, ".");
            }
        }
        fprintf(outfile, "\n");
    }
}
