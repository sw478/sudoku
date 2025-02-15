#include "auxil.h"
#include "error.h"

#define PRINT_MEM_DOUBLY(doubly) { printf("drow: %3d dcol: %3d mem: %p\n", (doubly)->drow, (doubly)->dcol, ((void*)(doubly))); }

/* this file contains functions useful for debugging and displaying data */

void printMatrix(Dance *d)
{
   int pcol = 0, irow, nrow;
   Doubly *xcol, *hrow;

   for(hrow = d->root->down; hrow != d->root; hrow = hrow->down)
   {
      nrow = hrow->dcol - d->cmax;
      if(nrow == 0)
         continue;
      printf("%4d: ", hrow->drow);
      pcol = 0;
      irow = 0;
      xcol = hrow->right;
      for(; irow < nrow; xcol = xcol->right, irow++, pcol++)
      {
         for(; pcol < xcol->dcol; pcol++, printf("."));
         printf("X");
      }
      for(; pcol < d->cmax; pcol++, printf("."));
      printf("\n");
   }
   printf("\n");
}

void printSingleSol_Matrix(Dance *d, SolTree *sol)
{
   SolTree *cur;
   Doubly *xcol, *xrow;
   int pcol, irow, nrow;

   for(cur = sol; cur->parent != cur; cur = cur->parent)
   {
      xrow = cur->row;
      nrow = xrow->dcol - d->cmax;
      if(nrow == 0)
         continue;
      printf("%4d: ", xrow->drow);
      pcol = 0;
      irow = 0;
      xcol = xrow->right;
      for(; irow < nrow; xcol = xcol->right, irow++, pcol++)
      {
         for(; pcol < xcol->dcol; pcol++, printf("."));
         printf("X");
      }
      for(; pcol < d->cmax; pcol++, printf("."));
      printf("\n");
   }
   printf("\n");
}

void printSolutions_Sudoku(Dance *d)
{
   int i;

   printf("\n%d solutions found\n", d->numSols);
   if(d->numSols != 1)
      return;

   for(i = 0; i < d->numSols; i++)
   {
      printf("\nsol %d: \n", i + 1);
      //printSingleSol_Matrix(d, d->sols[i]); /* prints rows of matrices */
      printSingleSol_Sudoku(d, d->sols[i]); /* prints the solution as a sudoku grid */
   }
   printf("\n");
}

void printSingleSol_Sudoku(Dance *d, SolTree *sol)
{
   SolTree *cur;
   int drow, num, igrid, xy = d->s->xy, *grid;
   grid = calloc(d->cmax, sizeof(int));

   for(cur = sol; cur->parent != cur; cur = cur->parent)
   {
      drow = cur->row->drow;
      num = drow % xy;
      igrid = drow / xy;
      grid[igrid] = num + 1;
   }
   printSudokuBoard(d, grid);
   free(grid);
}

void printSudokuBoard(Dance *d, int *grid)
{
   int x = d->s->x, y = d->s->y;
   int row, col, xy = x*y;

   for(row = 0; row < xy; row++)
   {
      if(row % y == 0)
         printf("\n");
      for(col = 0; col < xy; col++)
      {
         if(col % x == 0)
            printf(" ");
         if(grid[row*xy + col] != 0)
            printf(" %2d", grid[row*xy + col]);
         else
            printf(" __");
      }
      printf("\n");
   }
   printf("\n");
}

/*
   prints numbers based on whether or not
   d->hideList[igrid]->filled == 1
*/
void printSudokuBoard_Gen(Dance *d)
{
   int x = d->s->x, y = d->s->y;
   int row, col, xy = x*y, igrid;

   for(row = 0; row < xy; row++)
   {
      if(row % y == 0)
         printf("\n");
      for(col = 0; col < xy; col++)
      {
         igrid = row*xy + col;
         if(col % x == 0)
            printf(" ");
         if(d->hideList[igrid]->filled)
            printf(" %2d", d->hideList[igrid]->num);
         else
            printf(" __");
      }
      printf("\n");
   }
   printf("\n");
}

void printSolutions_Sudoku2(Dance *d)
{
   int i;

   printf("\n%d solutions found\n", d->numSols);
   if(d->numSols != 1)
      return;
   
   for(i = 0; i < d->numSols; i++)
   {
      printf("\nsol %d: \n", i + 1);
      //printSingleSol_Matrix(d, d->sols[i]);
      printSingleSol_Sudoku2(d, d->sols[i]);
   }
   printf("\n");
}

void printSingleSol_Sudoku2(Dance *d, SolTree *sol)
{
   SolTree *cur;
   int num, igrid, xy = d->s->xy, *grid;
   Doubly *hrow, *xrow;

   grid = calloc(d->cmax, sizeof(int));

   for(cur = sol; cur->parent != cur; cur = cur->parent)
   {
      hrow = cur->row;
      num = hrow->drow % xy;

      for(xrow = hrow->right->right; xrow != hrow; xrow = xrow->right)
      {
         igrid = xrow->dcol - xy;
         grid[igrid] = num + 1;
      }
   }
   printSudokuBoard(d, grid);
   free(grid);
}

void printSolutions_NQueens(Dance *d)
{
   int i, maxPrint = 2;
   
   printf("\n%d solutions found\n", d->numSols);
   
   printf("printing first %d solutions\n", maxPrint);

   for(i = 0; i < maxPrint && i < d->numSols; i++)
   {
      printf("\nsol %d: \n", i + 1);
      //printSingleSol_Matrix(d, d->sols[i]);
      printSingleSol_NQueens(d, d->sols[i]);
   }
   printf("\n");
}

void printSingleSol_NQueens(Dance *d, SolTree *sol)
{
   SolTree *cur;
   Doubly *hrow;
   int n = d->nq, n2 = n*n, *board, pos;

   if(!sol->row)
      return;
   board = calloc(n2, sizeof(int));

   for(cur = sol; cur->parent != cur; cur = cur->parent)
   {
      hrow = cur->row;
      pos = hrow->drow;
      board[pos] = 1;
   }
   printBoard_NQueens(d, board);
   free(board);
}

void printBoard_NQueens(Dance *d, int *board)
{
   int n = d->nq, n2 = n*n, pos;
   
   for(pos = 0; pos < n2; pos++)
   {
      if(pos % n == 0)
         printf("\n");

      if(board[pos] == 1)
         printf(" X");
      else
         printf(" _");
   }
   printf("\n");
}

void printDistribution_NQueens(Dance *d)
{
   int i;
   SolTree *cur;
   Doubly *hrow;
   int n = d->nq, n2 = n*n, *board, pos, numSols = d->numSols;
   float percent;
   board = calloc(n2, sizeof(int));

   printf("printing distribution of queens on %d-queens board\n", n);

   for(i = 0; i < numSols; i++)
   {
      for(cur = d->sols[i]; cur->parent != cur; cur = cur->parent)
      {
         hrow = cur->row;
         pos = hrow->drow;
         board[pos]++;
      }
   }

   for(pos = 0; pos < n2; pos++)
   {
      if(pos % n == 0)
         printf("\n\n");
      percent = (float)board[pos] / numSols;
      printf(" %1.3f", percent);
   }
   printf("\n");

   free(board);
}

void printHeur(Dance *d)
{
   Heur *head = d->heurRoot, *heur;
   Doubly *hcol;

   printf("heuristics: \n");

   if(head->next != head)
   {
      printf("r: ");
      for(heur = head->next; heur != head; heur = heur->next)
      {
         hcol = ((Doubly*)heur->hcol);
         printf("%d ", hcol->dcol);
      }
      printf("\n");
   }

   for(head = d->heurRoot->hnext; head != d->heurRoot; head = head->hnext)
   {
      if(head->next == head)
         continue;
      printf("%d: ", head->num);
      for(heur = head->next; heur != head; heur = heur->next)
      {
         hcol = ((Doubly*)heur->hcol);
         if(hcol->drow - d->rmax == heur->num)
            heurNumError();
         printf("%d ", hcol->dcol);
      }
      printf("\n");
   }
   printf("\n");
}

void checkMatrix(Dance *d)
{
   Doubly *hcol, *hrow, *doub;
   for(hcol = d->root->right; hcol != d->root; hcol = hcol->right)
   {
      if(!(hcol->left->right == hcol && hcol->right->left == hcol))
         checkDoublyError(hcol->drow, hcol->dcol);
      for(doub = hcol->down; doub != hcol; doub = doub->down)
         checkDoubly(doub);
   }
   for(hrow = d->root->down; hrow != d->root; hrow = hrow->down)
   {
      if(!(hrow->up->down == hrow && hrow->down->up == hrow))
         checkDoublyError(hrow->drow, hrow->dcol);
   }
}

void checkDoubly(Doubly *doub)
{
   if(!(doub->left->right == doub &&
         doub->right->left == doub &&
         doub->up->down == doub &&
         doub->down->up == doub))
      checkDoublyError(doub->drow, doub->dcol);
}

void printMatrixDoublyMemory(Dance *d)
{
   Doubly *hcol, *hrow, *doub;

   PRINT_MEM_DOUBLY(d->root)
   for(hcol = d->root->right; hcol != d->root; hcol = hcol->right)
   {
      PRINT_MEM_DOUBLY(hcol)
      for(doub = hcol->down; doub != hcol; doub = doub->down)
         PRINT_MEM_DOUBLY(doub)
   }
   for(hrow = d->root->down; hrow != d->root; hrow = hrow->down)
      PRINT_MEM_DOUBLY(hrow)
}