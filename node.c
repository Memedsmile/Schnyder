#include "node.h"
#include "file.h"

void addNode(char childid, Node** parent){
  Node* child = malloc(sizeof(Node));
  child->id = childid;
  child->lc = NULL;
  child->rc = NULL;
  if(*parent == NULL){
    *parent = child;
    child->parent = NULL;
    child->depth = 1;
  }
  else if((*parent)->lc == NULL){
    (*parent)->nbsom++;
    (*parent)->lc = child;
    child->parent = *parent;
    child->depth = (*parent)->depth+1;
  }
  else if((*parent)->rc == NULL){
    (*parent)->nbsom++;
    (*parent)->rc = child;
    child->parent = *parent;
    child->depth = (*parent)->depth+1;
  }
  else{
    printf("%c a déja 2 fils!\n",(*parent)->id);
  }
}

Node* searchNode(Node* tree, char id){
  if(tree == NULL) return NULL;
  if(id == tree->id) return tree;
  if(searchNode(tree->lc, id) == NULL) return searchNode(tree->rc, id);
  return searchNode(tree->lc, id);
}

void deleteTree(Node* tree){
    if(tree == NULL) exit;
    if(tree->lc)  deleteTree(tree->lc);
    if(tree->rc) deleteTree(tree->rc);
    if(tree->parent) free(tree->parent);
    free(tree);
}

int printTreeLevel(Node* tree, int d){
  File* f = NULL;
  Node* nodetmp = NULL;
  int nbaf = 0;
  push(&f, tree);

  while(!empty(f)){
    nodetmp = front(f);
    if(nodetmp->depth == d){
      printf("%c \t", nodetmp->id);
      nbaf++;
    }
    if(nodetmp->lc)
      push(&f, nodetmp->lc);
    if(nodetmp->rc)
      push(&f, nodetmp->rc);
    pop(&f);
  }
  return nbaf;
}

 
void printTree(Node* tree){
  int nbaf = 0;
  int d = 1;
  while(nbaf < sizeTree(tree)){

    nbaf += printTreeLevel(tree, d);

    d++;
    printf("\n");
  }
}

int sizeTree(Node* tree){
  if(tree == NULL)
    return 0;
  else return (1 + sizeTree(tree->lc) + sizeTree(tree->rc));
}
