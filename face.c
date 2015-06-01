#include "face.h"

int hash(int** tab, int key){
  int i = 0;
  while(i<3 && tab[0][i] != key){
    i++;
  }
  if(i==3)
    return -1;
  else return tab[1][i];
}

Face* createFace(int a, int b, int c){
  Face* f = malloc(sizeof(Face*));
  f->label = malloc(2 * sizeof(int*));

  f->label[0] = malloc(3 * sizeof(int));

  f->label[1] = malloc(3 * sizeof(int));

  f->label[0][0] = a;
  f->label[0][1] = b;
  f->label[0][2] = c;

  f->label[1][0] = 0;
  f->label[1][1] = 1;
  f->label[1][2] = 2;

  f->colored = 0;
  f->nblabel = 3;
 
  return f;
}

void printFace(Face* f){
  for(int i = 0 ; i < 3 ; i++){
    printf("%d : %d\n", f->label[0][i], f->label[1][i]);
  }
  printf("\n");
}

void switchLabel(Face* f){
  int aux = f->label[1][0];
  f->label[1][0] = f->label[1][1];
  f->label[1][1] = f->label[1][2];
  f->label[1][2] = aux;
}
    
