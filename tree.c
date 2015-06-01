#include "tree.h"

void copie(Node* tree, Node** cpy){
  if(tree){
    if((*cpy) == NULL){
      addNode(tree->id, cpy);
      if(tree->lc){
	addNode(tree->lc->id, cpy);
	addNode(tree->rc->id, cpy);
	copie(tree->lc, &((*cpy)->lc));
	copie(tree->rc, &((*cpy)->rc));
      }
    }
    else{
      if(tree->lc){
	addNode(tree->lc->id, cpy);
	addNode(tree->rc->id, cpy);
	copie(tree->lc, &((*cpy)->lc));
	copie(tree->rc, &((*cpy)->rc));
      }
    }
  }
}
  
Node* treeMin(){
  Node* tree = NULL;
  addNode('A', &tree);
  addNode('B', &tree);
  addNode('C', &tree);
  return tree;
}

void enumfield(Node* tree, File** field){
  if(tree->lc == NULL && tree->rc == NULL)
    push(field, tree);
  else if(tree->lc == NULL)
    enumfield(tree->rc, field);
  else if(tree->rc == NULL)
    enumfield(tree->lc, field);
  else{
    enumfield(tree->lc, field);
    enumfield(tree->rc, field);
  } 
}

int sizetab(Node** tab){
  if(tab == NULL)
    return 0;
  else{
    int i = 0;
    while(tab[i] != NULL)
      i++;
    return i;
  }
}

void addcopyTree(Node* child, Node** parent){
  Node* copychild = NULL;
  copie(child, &copychild);

  if(*parent == NULL){
    *parent = copychild;
    copychild->parent = NULL;
    copychild->depth = 1;
  }
  else if((*parent)->lc == NULL){
    (*parent)->lc = copychild;
    copychild->parent = *parent;
    updatedepth(parent);
  }
  else if((*parent)->rc == NULL){
    (*parent)->rc = copychild;
    copychild->parent = *parent;
    updatedepth(parent);
  }
  else{
    printf("%c a déja 2 fils!\n",(*parent)->id);
  }
}

void updatedepth(Node** tree){
  if((*tree)->parent == NULL)
    (*tree)->depth = 1;
  else
    (*tree)->depth = ((*tree)->parent->depth) + 1;
  if((*tree)->lc != NULL)
    updatedepth(&((*tree)->lc));
  if((*tree)->rc != NULL)
    updatedepth(&((*tree)->rc));
}


Node** enumTree(Node*** T, int nbfield, int nbfact, int letter){
  if(nbfact == 0){
    T[nbfact] = malloc(2*sizeof(Node*));
    T[nbfact][0] = NULL;
    T[nbfact][1] = NULL;
    addNode('A'+letter, &T[nbfact][0]);
    letter++;
    return enumTree(T, nbfield, nbfact+1,letter);
  }
  else if(nbfact == nbfield){
    return T[nbfield-1];
  }
  else{  
    int sizeT = 0;
    for(int k = 1 ; k <= nbfact ; k++)
      sizeT += sizetab(T[k-1])*sizetab(T[nbfact-k]);
    T[nbfact] = malloc((sizeT+1) * sizeof(Node*));
    T[nbfact][sizeT]=NULL;
    int m = 0;
    int n = 0;
    int p = 1;
    for(int k = 0; k < sizeT ; k++){
      T[nbfact][k]=NULL;
      addNode('A'+letter, &T[nbfact][k]);
      addcopyTree(T[p-1][m], &T[nbfact][k]);
      addcopyTree(T[nbfact-p][n], &T[nbfact][k]);
      if(n == sizetab(T[nbfact-p])-1){
	if(m == sizetab(T[p-1])-1){
	  m = n = 0;
	  p++;
	}
	else{
	  m++;
	  n = 0;
	}
      }
      else n++;
    }
    letter++; 
    return enumTree(T, nbfield, nbfact+1, letter);
  }
}

Node* randTree(Node* T, int nbfield, int nbfact, int letter){
  int r;
  File* fifo = NULL;
  enumfield(T, &fifo);
  srand(time(NULL)); 
  while(!empty(fifo)){
    if(nbfact == nbfield)
      return T;
    r = rand() %2;
    if(r == 1){
      Node* field = front(fifo);
      addNode(letter, &field);
      addNode(letter+1, &field);
      letter += 2;
      nbfact++;
    }
    pop(&fifo);
  }
  return randTree(T, nbfield, nbfact, letter);
}
