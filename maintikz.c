#include <stdio.h>
#include <stdlib.h>
#include "tikz.h"

char name[200] = "graph.tex";

int main(int argc, char *argv[]){

  int nbedge = 13;
  Edge** edges = malloc((nbedge+1)*(sizeof (Edge*)));

  Edge* A = malloc(sizeof(Edge));
  A->origin = 1;
  A->dest = 2;
  A->couleur = -1;
  A->oriente = 0;
  edges[0] = A;

  Edge* B = malloc(sizeof(Edge));
  B->origin = 2;
  B->dest = 6;
  B->couleur = -1;
  B->oriente = 0;
  edges[1] = B;
  
  Edge* C = malloc(sizeof(Edge));
  C->origin = 1;
  C->dest = 6;
  C->couleur = -1;
  C->oriente = 0;
  edges[2] = C;
  
  Edge* D = malloc(sizeof(Edge));
  D->origin = 2;
  D->dest = 4;
  D->couleur = -1;
  D->oriente = 0;
  edges[3] = D;

  Edge* E = malloc(sizeof(Edge));
  E->origin = 4;
  E->dest = 6;
  E->couleur = -1;
  E->oriente = 0;
  edges[4] = E;

  Edge* F = malloc(sizeof(Edge));
  F->origin = 6;
  F->dest = 8;
  F->couleur = -1;
  F->oriente = 0;
  edges[5] = F;

  Edge* G = malloc(sizeof(Edge));
  G->origin = 1;
  G->dest = 8;
  G->couleur = -1;
  G->oriente = 0;
  edges[6] = G;

  Edge* H = malloc(sizeof(Edge));
  H->origin = 2;
  H->dest = 3;
  H->couleur = -1;
  H->oriente = 0;
  edges[7] = H;

  Edge* I = malloc(sizeof(Edge));
  I->origin = 3;
  I->dest = 4;
  I->couleur = -1;
  I->oriente = 0;
  edges[8] = I;

  Edge* J = malloc(sizeof(Edge));
  J->origin = 4;
  J->dest = 5;
  J->couleur = -1;
  J->oriente = 0;
  edges[9] = J;

  Edge* K = malloc(sizeof(Edge));
  K->origin = 6;
  K->dest = 5;
  K->couleur = -1;
  K->oriente = 0;
  edges[10] = K;
  
  Edge* L = malloc(sizeof(Edge));
  L->origin = 6;
  L->dest = 7;
  L->couleur = -1;
  L->oriente = 0;
  edges[11] = L;

  Edge* M = malloc(sizeof(Edge));
  M->origin = 7;
  M->dest = 8;
  M->couleur = -1;
  M->oriente = 0;
  edges[12] = M;
  edges[13] = NULL;


  Graph* T = malloc(sizeof(Graph));
  allocGraph(edges, T, 8);

  Graph** tabT = enumTriang(8);    
  
  FILE* desc = fopen(name,"w");
  beginDocument(desc);
  enumGraph(desc, tabT);
  endDocument(desc);
}
