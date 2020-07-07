#include "solTrie.h"
#include "dance.h"

void addLeaf(Dance *d)
{
   if(d->numSols >= d->solCap)
   {
      d->solCap *= 2;
      d->sols = realloc(d->sols, (d->solCap)*sizeof(SolTrie));
   }
   d->sols[d->numSols] = d->csol;
   d->numSols++;
}

SolTrie* initTrie(Doubly *row)
{
   SolTrie *new = malloc(sizeof(SolTrie));
   new->row = row;
   new->ichild = new->numSols = 0;
   new->cap = STARTING_CAP;
   new->child = malloc(new->cap*sizeof(SolTrie));
   new->minList = malloc(sizeof(Doubly*));
   new->minSize = 1;
   new->minIndex = 0;
   new->parent = new;

   return new;
}

void addChild(SolTrie *sol, SolTrie *new)
{
   if(sol->ichild >= sol->cap)
   {
      sol->cap *= 2;
      sol->child = realloc(sol->child, sol->cap*sizeof(SolTrie));
   }

   sol->child[sol->ichild] = new;
   sol->ichild++;

   new->parent = sol;
}

void incNumSols(SolTrie *sol)
{
   SolTrie *temp;
   for(temp = sol; temp->parent != temp; temp = temp->parent)
      temp->numSols++;
   temp->numSols++;
}

void freeSol(SolTrie *sol)
{
   int i;

   for(i = 0; i < sol->ichild; i++)
      freeSol(sol->child[i]);

   free(sol->minList);
   free(sol->child);
   free(sol);
}
