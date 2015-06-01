#include "file.h"

void push(File** fifo, Node* noeud){
  File* newelt = malloc(sizeof(File));
    if (newelt != NULL){
        newelt->next = NULL;
        newelt->noeud = noeud;
        if (*fifo == NULL){
            *fifo = newelt;
        }
        else{
            File *filetmp = *fifo;
            while (filetmp->next != NULL){
                filetmp = filetmp->next;
            }
            filetmp->next = newelt;
        }
    }
}

void pop(File** fifo){
  if (*fifo != NULL){
    File *filetmp = (*fifo)->next;
    free(*fifo);
    *fifo = filetmp;
  }
}

void clear(File** fifo){
  while(*fifo != NULL)
    pop(fifo);
}

int size(File* fifo){
  if(fifo == NULL)
    return 0;
  int _size = 1;
  File* filetmp = fifo;
  while(filetmp->next != NULL){
    _size++;
    filetmp = filetmp->next;
  }
  return _size;
}

int empty(File* fifo){
  if(size(fifo) == 0)
    return 1;
  else return 0;
}

Node* front(File* fifo){
  if(fifo == NULL)
    return NULL;
  else return fifo->noeud;
}

Node* back(File* fifo){
  if(fifo == NULL)
    return NULL;
  else{
    File* filetmp = fifo;
    while(filetmp->next != NULL){
      filetmp = filetmp->next;
    }
    return filetmp->noeud;
  }
}

void printfile(File* fifo){
  if(fifo == NULL){
    printf("\n");
  }
  else{
    printf("%c \t", fifo->noeud->id);
    printfile(fifo->next);
  }
}
