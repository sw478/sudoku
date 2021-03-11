#ifndef SUDOKU_H
#define SUDOKU_H
#include "struct.h"

void checkConfig();
int runSudoku(Dance *d, int argc, char *argv[]);
int runSudoku2(Dance *d, int argc, char *argv[]);
int runNQueens(Dance *d, int argc, char *argv[]);
int runSudokuGen(Dance *d, int argc, char *argv[]);
int runSudokuFull(Dance *d, int argc, char *argv[]);

#endif
