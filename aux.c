#include "aux.h"

void printBoard(int *grid, int x, int y)
{
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

void printMatrix(Dance *d)
{
   int pcol = 0, irow, nrow;
   Doubly *xcol, *xrow;

   printColHeaders(d);

   for(xrow = d->root->down; xrow != d->root; xrow = xrow->down)
   {
      nrow = xrow->dcol - d->cmax;
      if(nrow == 0)
         continue;
      printf("%3d: ", xrow->drow);
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

void printColHeaders(Dance *d)
{
   int pcol = 0;
   Doubly *xcol;

   printf("     ");
   for(pcol = 0; pcol < d->cmax; printf("%d", pcol % 10), pcol++);
   printf("\nX's: ");
   pcol = 0;
   for(xcol = d->root->right; xcol != d->root; xcol = xcol->right, pcol++)
   {
      for(; pcol < xcol->dcol; pcol++, printf("0"));
      printf("%d", xcol->drow - d->rmax);
   }
   for(; pcol < d->cmax; pcol++, printf("0"));
   printf("\n");
}

void printSolutions(Dance *d)
{
   int i;

   for(i = 0; i < d->numSols; i++)
   {
      printf("\n\nsol %d: ", i + 1);
      printSingleSol2(d, d->sols[i]);
   }
   printf("\n\n");
}

void printSingleSol(Dance *d, SolTrie *sol)
{
   SolTrie *cur;
   Doubly *xcol;
   int pcol, irow;
   if(sol == d->solRoot)
      return;

   printColHeaders(d);
   for(cur = sol; cur->parent != cur; cur = cur->parent)
   {
      printf("%3d: ", cur->row->drow);
      pcol = 0;
      irow = 0;
      xcol = cur->row->right;
      for(; pcol < cur->row->left->dcol; xcol = xcol->right, irow++, pcol++)
      {
         for(; pcol < xcol->dcol; pcol++, printf("."));
         printf("X");
      }
      for(; pcol < d->cmax; pcol++, printf("."));
      printf("\n");
   }
   printf("\n");
}

void printSingleSol2(Dance *d, SolTrie *sol)
{
   SolTrie *cur;
   int drow, num, igrid, xy = d->x*d->y, *grid;
   if(!sol->row)
      return;
   grid = calloc(d->cmax, sizeof(int));

   for(cur = sol; cur->parent != cur; cur = cur->parent)
   {
      drow = cur->row->drow;
      num = drow % xy;
      igrid = drow / xy;
      grid[igrid] = num + 1;
   }
   printBoard(grid, d->x, d->y);
   free(grid);
}

void printHeur(Dance *d)
{
   Heur *head = d->heurRoot, *heur;
   Doubly *hcol;

   printf("heuristics: \n");

   printf("r: ");
   for(heur = head->next; heur != head; heur = heur->next)
   {
      hcol = ((Doubly*)heur->hcol);
      printf("%d ", hcol->dcol);
   }
   printf("\n");

   for(head = d->heurRoot->hnext; head != d->heurRoot; head = head->hnext)
   {
      printf("%d: ", head->num);
      for(heur = head->next; heur != head; heur = heur->next)
      {
         hcol = ((Doubly*)heur->hcol);
         printf("%d ", hcol->dcol);
      }
      printf("\n");
   }
   printf("\n");
}

int saveSolution(Dance *d, Sudoku *s)
{
   SolTrie *cur;
   int num, igrid, rowNum;

   if(d->numSols > 1)
   {
      printf("\n%lu solutions found\n", d->numSols);
      return d->numSols;
   }
   else if(d->numSols == 0)
      return 0;

   for(cur = d->sols[0]; cur->parent != cur; cur = cur->parent)
   {
      rowNum = cur->row->drow;
      num = rowNum % s->xy;
      igrid = rowNum / s->xy;
      s->grid[igrid] = num + 1;
   }

   return 0;
}

void checkMatrix(Dance *d)
{
   Doubly *hcol, *hrow, *doub;
   for(hcol = d->root->right; hcol != d->root; hcol = hcol->right)
   {
      assert(hcol->left->right == hcol);
      assert(hcol->right->left == hcol);
      for(doub = hcol->down; doub != hcol; doub = doub->down)
         checkDoubly(doub);
   }
   for(hrow = d->root->down; hrow != d->root; hrow = hrow->down)
   {
      assert(hrow->up->down == hrow);
      assert(hrow->down->up == hrow);
   }
}

void checkDoubly(Doubly *doub)
{
   assert(doub->left->right == doub);
   assert(doub->right->left == doub);
   assert(doub->up->down == doub);
   assert(doub->down->up == doub);
}
