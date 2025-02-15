#include "free.h"
#include "solTree.h"
#include "heuristic.h"
#include "hide.h"
#include "initHrowLayout_Sudoku2.h"

void freeDance(Dance *d)
{
   freeMatrix(d);

   free(d->sols);
   if(d->numSols > 0)
      freeTree(d->csol);

   if(d->problem == SUDOKU || d->problem == SUDOKU2 || d->problem == SGEN || d->problem == SUDOKU_O || d->problem == SGEN_O)
      freeHide(d);

   HEUR_FREE(d)

   if(d->problem == SUDOKU || d->problem == SUDOKU2 || d->problem == SGEN || d->problem == SUDOKU_O || d->problem == SGEN_O)
   {
      fclose(d->s->boardFile);
      free(d->s->grid);
      free(d->s);
   }

   free(d);
}

void freeMatrix(Dance *d)
{
   Doubly *col, *temp;

   for(col = d->root->right; col != d->root;)
   {
      freeColumn(col);
      temp = col;
      col = col->right;
      free(temp);
   }
   freeColumn(col);
   free(d->root);
}

void freeColumn(Doubly *col)
{
   Doubly *row, *temp;

   for(row = col->down; row != col;)
   {
      temp = row;
      row = row->down;
      free(temp);
   }
}

