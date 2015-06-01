#include "edge.h"

void afficheEdge(Edge* arc){

  if(arc->oriente == 1){
    printf("%d %d> %d", arc->origin, arc->couleur, arc->dest);
  }
  else {
    //printf("titi\n");
    printf("%d -- %d", arc->origin, arc->dest);
    //    printf("\nwinnie\n");
  }
}

int equalsEdge(Edge* arc1, Edge* arc2){
  
  if((arc1->origin != arc2->origin)||(arc1->dest != arc2->dest)||(arc1->couleur != arc2->couleur)||(arc1->oriente != arc2->oriente)||(arc1->faces[0] != arc2->faces[0])||(arc1->faces[1] != arc2->faces[1])){
    
    return 0;
  }
  return 1;
}

void freeEdge(Edge* arc){
  free(arc->faces);
}

int colorEdge(Edge* arc){
  if(hash(arc->faces[0]->label, arc->origin) == hash(arc->faces[1]->label, arc->origin))
    return hash(arc->faces[0]->label, arc->origin);
  else if(hash(arc->faces[0]->label, arc->dest) == hash(arc->faces[1]->label, arc->dest))
    return hash(arc->faces[0]->label, arc->dest);
  else return -1;
}

