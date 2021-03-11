#include "matrixFile.h"

/* call after sudoku board is initialized */
void setMatrixDimensions_Sudoku(Dance *d)
{
   d->rmax = d->s->xy*d->s->gridSize;
   d->cmax = 4*d->s->gridSize;
}

void setMatrixDimensions_SudokuFull(Dance *d)
{
   d->rmax = d->s->xy*d->s->gridSize;
   d->cmax = 5*d->s->gridSize;
}

/* call after sudoku board is initialized */
void setMatrixDimensions_Sudoku2(Dance *d)
{
   int x, y, xy, xf, yf, xfy, yfx;
   int fact[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

   x = d->s->x;
   y = d->s->y;
   xy = x*y;
   xf = fact[x];
   yf = fact[y];
   xfy = (int)(pow(xf, y));
   yfx = (int)(pow(yf, x));
   d->rmax = xy * (xfy*yfx);
   d->cmax = xy + xy*xy;
   printf("rmax: %d\n", d->rmax);
   printf("cmax: %d\n", d->cmax);
}

void setMatrixDimensions_NQueens(Dance *d)
{
   int n = d->nq, ndiag;

   ndiag = 4 * n - 6;
   d->rmax = n*n;
   d->cmax = 2*n + ndiag;
   printf("rmax: %d\n", d->rmax);
   printf("cmax: %d\n", d->cmax);
}

/*
   open matrixFile based on dimensions
   create matrixFile if it doesn't exist yet
*/
void findMatrixFile(Dance *d)
{
   char *matrixFile = malloc(BUFSIZE*sizeof(char));

   switch(d->problem)
   {
      case SUDOKU:
      case SGEN: sprintf(matrixFile, "dance/ds1_%dx%d.txt", d->s->y, d->s->x); break;
      case SUDOKU2: sprintf(matrixFile, "dance/ds2_%dx%d.txt", d->s->y, d->s->x); break;
      case NQUEENS: sprintf(matrixFile, "dance/dq_%d.txt", d->nq); break;
      case SUDOKU_O:
      case SGEN_O: sprintf(matrixFile, "dance/dso_%dx%d.txt", d->s->y, d->s->x); break;
   }

   // check if file doesn't exist
   if((access(matrixFile, F_OK) != 0))
      createMatrixFile(d, matrixFile);

   d->matrixFile = fopen(matrixFile, "r+");
   assert(d->matrixFile);
   free(matrixFile);
}

/*
   run the python program to create the matrixFile
*/
void createMatrixFile(Dance *d, char *matrixFile)
{
   char *command = malloc(BUFSIZE*sizeof(char));
   char *buf = malloc(BUFSIZE*sizeof(char));

   sprintf(command, "python matrixFileCreator.py");
   sprintf(buf, " %s %d", matrixFile, d->problem);
   strcat(command, buf);
   switch(d->problem)
   {
      case SUDOKU:
      case SGEN:
      case SUDOKU2:
      case SUDOKU_O:
      case SGEN_O: sprintf(buf, " %d %d", d->s->y, d->s->x); break;
      case NQUEENS: sprintf(buf, " %d", d->nq); break;
   }
   strcat(command, buf);
   printf("command: %s\n", command);

   system(command);

   free(command);
}