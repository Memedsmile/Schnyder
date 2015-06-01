#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char *argv[]){
  
  /* Création d'arêtes */
  int nbedge = 7;
  Edge** edges = malloc((nbedge+1)*(sizeof (Edge*)));
  Edge A, B, C, D, E, F, G;
  A.origin = 1;
  A.dest = 2;
  A.couleur = 0;
  A.oriente = 0;
  edges[0] = &A;

  B.origin = 2;
  B.dest = 3;
  B.couleur = 0;
  B.oriente = 0;
  edges[1] = &B;

  C.origin = 1;
  C.dest = 3;
  C.couleur = 0;
  C.oriente = 0;
  edges[2] = &C;

  D.origin = 1;
  D.dest = 5;
  D.couleur = 0;
  D.oriente = 0;
  edges[3] = &D;

  E.origin = 3;
  E.dest = 5;
  E.couleur = 0;
  E.oriente = 0;
  edges[4] = &E;

  F.origin = 3;
  F.dest = 4;
  F.couleur = 0;
  F.oriente = 0;
  edges[5] = &F;

  G.origin = 4;
  G.dest = 5;
  G.couleur = 2;
  G.oriente = 1;
  edges[6] = &G;
  edges[7] = NULL;
 
  /* Création du graphe */


  Graph* T = malloc(sizeof(Graph));
  allocGraph(edges, T, 7);

  /* Test des fonctions */
 
  afficheGraph(T);
  printf("\n\n");
  retourner(&G, T);
  afficheEdge(&G);
  printf("\n");
  afficheGraph(T);
  printf("\n");
  retourner(&G, T);
  afficheEdge(&G);
  printf("\n");
  afficheGraph(T);
  printf("\n");

  return 0;
}
