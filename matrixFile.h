#ifndef SETMD_H
#define SETMD_H
#include "struct.h"

void setMatrixDimensions_Sudoku(Dance *d);
void setMatrixDimensions_SudokuFull(Dance *d);
void setMatrixDimensions_Sudoku2(Dance *d);
void setMatrixDimensions_NQueens(Dance *d);

void findMatrixFile(Dance *d);
void createMatrixFile(Dance *d, char *matrixFile);
char *getMatrixFileName(Dance *d, int *sorted_dim);

#endif