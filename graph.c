#include "graph.h"

void allocGraph(Edge** edges, Graph* T,int genre){
  T->genre = genre;
  T->nbsom = 4*genre;
  T->arcs = malloc((T->nbsom) * sizeof(Edge**));
  T->faceext = malloc((T->nbsom) * sizeof(Face*));
  for(int i = 0; i < T->nbsom ; i++){
    T->arcs[i] = malloc((T->nbsom) * sizeof(Edge*));
  }
  int i = 0;
  while(edges[i] != NULL){
    T->arcs[edges[i]->origin-1][edges[i]->dest-1] = edges[i];
    T->faceext[i] = edges[i]->faces[0];
    if(edges[i]->oriente == 0){
      T->arcs[edges[i]->dest-1][edges[i]->origin-1] = edges[i];
    }
    i++;
  }
}


void updateGraph(Edge* arc, Graph* T){
  if(!T->arcs[arc->origin-1][arc->dest-1] || !equalsEdge(T->arcs[arc->origin-1][arc->dest-1],arc)){
    if(!arc->oriente){
      T->arcs[arc->origin-1][arc->dest-1] = arc;
      T->arcs[arc->dest-1][arc->origin-1] = arc; 
    }
    else{
    	T->arcs[arc->origin-1][arc->dest-1] = arc;
    	T->arcs[arc->dest-1][arc->origin-1] = NULL;
    }
  }
  else if(T->arcs[arc->origin-1][arc->dest-1]){
     if(!arc->oriente){
      T->arcs[arc->origin-1][arc->dest-1] = arc;
      T->arcs[arc->dest-1][arc->origin-1] = arc; 
    }
    else{
    	T->arcs[arc->origin-1][arc->dest-1] = arc;
    	T->arcs[arc->dest-1][arc->origin-1] = NULL;
    }
  }
}

void afficheGraph(Graph* G){
  int i,j;
  for(i = 0 ; i < G->nbsom ; i++){
    for(j = 0 ; j < G->nbsom ; j++){
      if(G->arcs[i][j]){
	afficheEdge(G->arcs[i][j]);
	printf("\t");
      }
      else printf("x -- x\t");
    }
    printf("\n");
  }
}

 
int equalsGraph(Graph G1, Graph G2){
  int t = 1;
  if((G1.nbsom != G2.nbsom)||(G1.genre != G2.genre)){
    return 0;
  }
  for(int i = 0 ; i < G1.nbsom ; i++){
    for(int j = 0 ; j < G1.nbsom ; j++){
      if(!equalsEdge(G1.arcs[i][j], G2.arcs[i][j])){
	  return 0;
      } 
    }
  }
  return 1;
}

void freeGraph(Graph* G){
  for(int i = 0 ; i < G->nbsom ; i++){
    free(G->arcs[i]);
  }
  free(G->arcs);
}

/* Manipulation d'arêtes dans le graphe */

void retourner(Edge* arc, Graph *G){
  int aux = arc->origin;
  arc->origin = arc->dest;
  arc->dest = aux;
  updateGraph(arc, G);
}


/* Création de triangulation */

Edge** extEdges(Node* tree){
  File* field = NULL;
  enumfield(tree, &field);

  Edge** extedges = malloc((size(field)+2)*sizeof(Edge*));

  for(int i = 0 ; i < size(field) ; i++){
    extedges[i] = malloc(sizeof(Edge));
    extedges[i]->faces = malloc(2 * sizeof(Face*));
    extedges[i]->origin = i+1;
    extedges[i]->dest = i+2;
    extedges[i]->couleur = -1;
    extedges[i]->oriente = 0;
    extedges[i]->faces[0] = createFace(i+1, i+2, sizeTree(tree));
    extedges[i]->faces[1] = NULL;
  }
  extedges[size(field)] = malloc(sizeof(Edge));
  extedges[size(field)]->origin = size(field)+1;
  extedges[size(field)]->dest = 1;
  extedges[size(field)]->couleur = -1;
  extedges[size(field)]->oriente = 0;

  extedges[size(field)]->faces = malloc(2 * sizeof(Face*));
  extedges[size(field)]->faces[0] = createFace(size(field)+1, 1, sizeTree(tree));
  extedges[size(field)]->faces[1] = NULL;

  extedges[size(field)+1] = NULL;

  for(int i = 0 ; i <= size(field) ; i++){
    if(extedges[i]->copy == NULL){
      extedges[i]->copy = extedges[i+2];
      extedges[i+2]->copy = extedges[i];
    }
  }
  return extedges;
}

void NdEdge(Node* tree, Graph* T){

  File* field = NULL;
  enumfield(tree, &field);

  tree->link = T->arcs[0][1];
  for(int i = 1 ; i < T->nbsom -1 ; i++){
    front(field)->link = T->arcs[i][i+1];
    pop(&field);
  }
  front(field)->link = T->arcs[T->nbsom -1][0];
  pop(&field);
}

Graph** enumTriang(int genre){
  int nbsom = genre * 4;

  Node *** matricetree = malloc((nbsom-1) * sizeof(Node**));
  Node ** tabtree = enumTree(matricetree, nbsom-1, 0, 0);
  int sizeT = sizetab(tabtree);
  Graph** tabtriang = malloc((sizeT+1)*sizeof(Graph*));
  tabtriang[sizeT] = NULL;
  Edge*** extedges = malloc((sizeT+1)*sizeof(Edge**));
  extedges[sizeT] = NULL;
  for(int i = 0 ; i < sizeT ; i++){
    tabtriang[i] = triangulation(tabtree[i], genre, extedges[i]);
  }
 
  return tabtriang;
}
  
void coloring(Graph* G, int i, int k){
  if(i < G->nbsom-2){
    //printf("face %d : %d, K = %d\n", i, countlabel(G->faces[i], G), k);
    /*for(int i = 0 ; i < 6 ; i++){
      printf("face %d :\n", i);
      printFace(G->faces[i]);
    }
    for(int i = 0 ; i < 8 ; i++){
      printf("face ext %d :\n", i);
      printFace(G->faceext[i]);
      }*/
    if(coloriable(G->faces[i], G)){
      //printf("color %d\n",i);
      colorier(G->faces[i], G);
      coloring(G, i+1, k);
    }
    else if(bloquer(G->faces[i], G)){
      //printf("block %d\n",i);
      
      if(i == G->nbsom-3){
	Face* vois = choixvoisext(G->faces[i], G);
	//printf("vois : %d - %d\n",countlabel(vois,G), coloriable(vois, G));
	//printFace(vois);
	if((countlabel(vois,G) == 1 && !coloriable(vois, G))||(countlabel(vois,G) == 2)){
	  //printf("switch vois :\n");
	  //printFace(vois);
	  do{
	    switchLabel(vois);
	  }while(!coloriable(vois, G));
	  colorier(vois,G);
	  updateEdge(G);
	}
	else{
	  i = k;
	  Face* vois = choixVoisin(G->faces[i],G);
	  //printf("voisinchoisi :\n");
	  //printFace(vois);
	  switchLabel(vois);
	  //printf("voisinup :\n");
	  //printFace(vois);
	}
	coloring(G, i, k);
      }
      else{
	k = i;
	//printf("titi\n");
	Face* vois = choixVoisin(G->faces[i],G);
	//printf("voisinchoisi :\n");
	//printFace(vois);
	switchLabel(vois);
	//printf("voisinup :\n");
	//printFace(vois);
	if(faceext(vois, G)){
	  //printf("vois est externe\n");
	  Edge* arcvois = G->arcs[vois->label[0][0]-1][vois->label[0][1]-1];
	  while(hash(arcvois->faces[0]->label, arcvois->origin) != hash(arcvois->copy->faces[1]->label, arcvois->copy->dest))
	    switchLabel(G->arcs[vois->label[0][0]-1][vois->label[0][1]-1]->copy->faces[1]);
	}
      }
	updateEdge(G);
	coloring(G, i, k);
      }
    else{
      //printf("switch %d\n",i);
      switchLabel(G->faces[i]);
      //printFace(G->faces[i]);
      updateEdge(G);
      coloring(G, i, k);
    }
  }
}


int countlabel(Face* f, Graph* g){
  int labaround[6];
  int j = 0, k = 0;
  Edge* arc = NULL;
  for(int  i = 0 ; i < 3 ; i++){
    j = (i+1)%3;
    //printf("i = %d , j = %d\t", i, j);
    arc = g->arcs[f->label[0][i]-1][f->label[0][j]-1];
    //afficheEdge(arc);
    //printf("\n");
    if(arc->faces[0] == f){
      //printf("face 1 : %d -- %d\n k = ",f->label[0][i],f->label[0][j]);
      labaround[k] = hash(arc->faces[1]->label, f->label[0][i]);
      labaround[k+1] = hash(arc->faces[1]->label, f->label[0][j]);
      k = k+2;
    }
    else{
      //printf("face 0 : %d -- %d\n",f->label[0][i],f->label[0][j]);
      labaround[k] = hash(arc->faces[0]->label, f->label[0][i]);
      labaround[k+1] = hash(arc->faces[0]->label, f->label[0][j]);
      k = k+2;
    }
  }
  /*printf("labaround : ");
  for(int m = 0 ; m < 6 ; m++){
    printf("%d \t", labaround[m]);
  }
  printf("\n");
  */
  if(((labaround[0] == labaround[2]) && (labaround[2] == labaround[4])) || ((labaround[0] == labaround[5] && (labaround[2] == labaround[1]) && (labaround[3] == labaround[4]))))
    return 0;
  if((labaround[0] != labaround[2]) && (labaround[2] == labaround[4]) && (labaround[0] == labaround[4]))
    return 2;
  return 1;
}


int coloriable(Face* f, Graph* g){
  if ((colorEdge(g->arcs[f->label[0][0]-1][f->label[0][1]-1]) != -1) && (colorEdge(g->arcs[f->label[0][1]-1][f->label[0][2]-1]) != -1) && (colorEdge(g->arcs[f->label[0][2]-1][f->label[0][0]-1]) != -1)){
    return 1;
  }
  else{
    return 0;
  }
}

int** voisins(Face* f, Graph* g){
  int** vois = malloc(3 * sizeof(int*));
  int j;
  Edge* tmp;
  for(int i = 0 ; i < 3 ; i++){
    vois[i] = malloc(2 * sizeof(int));
    j = (i+1)%3;
    tmp = g->arcs[f->label[0][i]-1][f->label[0][j]-1];
    if(tmp->faces[0] == f){
      vois[i][0] = hash(tmp->faces[1]->label, f->label[0][i]);
      vois[i][1] = hash(tmp->faces[1]->label, f->label[0][j]);
    }
    else{
      vois[i][0] = hash(tmp->faces[0]->label, f->label[0][i]);
      vois[i][1] = hash(tmp->faces[0]->label, f->label[0][j]);
    }
  }
  return vois;
}

int bloquer(Face* f, Graph* g){
  if(countlabel(f, g) == 0)
    return 1;
  else return 0;
}

void colorier(Face* f, Graph* g){
  if(coloriable(f, g)){
    g->arcs[f->label[0][0]-1][f->label[0][1]-1]->couleur = colorEdge(g->arcs[f->label[0][0]-1][f->label[0][1]-1]);
    orienter(g->arcs[f->label[0][0]-1][f->label[0][1]-1], g);
    if(faceext(g->arcs[f->label[0][0]-1][f->label[0][1]-1]->faces[0], g) == 1){
      g->arcs[f->label[0][0]-1][f->label[0][1]-1]->copy->couleur = colorEdge(g->arcs[f->label[0][0]-1][f->label[0][1]-1]->copy);
      orienter(g->arcs[f->label[0][0]-1][f->label[0][1]-1]->copy,g);
    }
    g->arcs[f->label[0][1]-1][f->label[0][2]-1]->couleur = colorEdge(g->arcs[f->label[0][1]-1][f->label[0][2]-1]);
    orienter(g->arcs[f->label[0][1]-1][f->label[0][2]-1], g);
    if(faceext(g->arcs[f->label[0][1]-1][f->label[0][2]-1]->faces[0], g) == 1){
      g->arcs[f->label[0][1]-1][f->label[0][2]-1]->copy->couleur = colorEdge(g->arcs[f->label[0][1]-1][f->label[0][2]-1]->copy);
      orienter(g->arcs[f->label[0][1]-1][f->label[0][2]-1]->copy,g);
    }
    g->arcs[f->label[0][2]-1][f->label[0][0]-1]->couleur = colorEdge(g->arcs[f->label[0][2]-1][f->label[0][0]-1]);
    orienter(g->arcs[f->label[0][2]-1][f->label[0][0]-1], g);
    if(faceext(g->arcs[f->label[0][2]-1][f->label[0][0]-1]->faces[0], g) == 1){
      g->arcs[f->label[0][2]-1][f->label[0][0]-1]->copy->couleur = colorEdge(g->arcs[f->label[0][2]-1][f->label[0][0]-1]->copy);
      orienter(g->arcs[f->label[0][2]-1][f->label[0][0]-1]->copy,g);
    }

    f->colored = 1;
  }
  
}

Face** listVoisins(Face* f, Graph* g){
  Face** vois = malloc(3 * sizeof(Face*));
  int j;
  Edge* tmp;
  for(int i = 0 ; i < 3 ; i++){
    vois[i] = malloc(sizeof(Face));
    j = (i+1)%3;
    tmp = g->arcs[f->label[0][i]-1][f->label[0][j]-1];
    if(tmp->faces[0] == f)
      vois[i] = tmp->faces[1];
    else
      vois[i] = tmp->faces[0];
  }
  return vois;
}

int voisinExt(Face* f, Graph* g){
  Face** vois = listVoisins(f, g);
  int nbext = 0;
  int j = 0;
  for(int i = 0 ; i < 3 ; i++){
    while(j <= g->nbsom){
      if(vois[i] == g->faceext[j]){
	nbext++;
	j = g->nbsom;
      }
      j++;
    }
    j = 0;
  }
  return nbext;
}

int faceext(Face* f, Graph* g){
  for(int i = 0; i < 3 ; i++){
    if(f-> label[0][i] > g->nbsom)
      return 1;
  }
  return 0;
}

Face* choixvoisext(Face* f, Graph* G){
  int i = 0, j = 1;
  Edge* arc = NULL;
  int labelA, labelB;
  while(i < 3){
    j = (i+1)%3;
    arc = G->arcs[f->label[0][i]-1][f->label[0][j]-1];
    labelA = hash(arc->faces[0]->label, arc->origin);
    labelB = hash(arc->faces[1]->label, arc->dest);
    if(labelA == labelB){
      return arc->copy->faces[1];
    }
    else i++;
  }
}

int switchvoisext(Face* f, Graph* G){
  int i = 0, j = 1;
  Edge* arc = NULL;
  int labelA, labelB;
  while(i < 3){
    j = (i+1)%3;
    arc = G->arcs[f->label[0][i]-1][f->label[0][j]-1];
    labelA = hash(arc->faces[0]->label, arc->origin);
    labelB = hash(arc->faces[1]->label, arc->dest);
    if(labelA == labelB){
      if(bloquer(arc->copy->faces[1], G))
	return 0;
      else
	while(!coloriable(arc->copy->faces[1], G))
	  switchLabel(arc->copy->faces[1]);
	colorier(arc->copy->faces[1], G);
	return 1;
    }
    else i++;
  }
}

void switchback(Face* f, Graph* G){
  int i = 0, j = 1;
  Edge* arc = NULL;
  int labelA, labelB;
  Face* back = NULL;
  while(i < 3){
    j = (i+1)%3;
    arc = G->arcs[f->label[0][i]-1][f->label[0][j]-1];
    labelA = hash(arc->faces[0]->label, arc->origin);
    labelB = hash(arc->faces[1]->label, arc->dest);
    //printf("%d -- %d\n", f->label[0][i], f->label[0][j]);
    if(labelA == labelB){
	if(arc->faces[0] == f)
	  back = arc->faces[1];
	else back = arc->faces[0];
	//	printf("back :\n");
	//printFace(back);
	if(bloquer(back, G))
	  switchback(back, G);
	else{
	  while(!coloriable(f, G) && !coloriable(back, G))
	    switchLabel(back);
	}
    }
    else i++;
  }
}

Face* choixVoisin(Face* f, Graph* g){
  Face** vois = listVoisins(f, g);
  Face* voisin = vois[0];
  int nbext;
  if(faceext(voisin, g) == 1)
    nbext = 3;
  else nbext = voisinExt(voisin, g);

  for(int i = 1 ; i < 3 ; i++){

    if(vois[i]->colored < voisin->colored){
      if(faceext(vois[i], g)){
	voisin = vois[i];
	nbext = 3;
      }
      else{
	voisin = vois[i];
	nbext = voisinExt(vois[i], g);
      }
    } 
    else if(faceext(vois[i], g) == 0 && voisinExt(vois[i], g) < nbext){
      voisin = vois[i];
      nbext = voisinExt(vois[i], g);
    }
  }

  return voisin;
}

void orienter(Edge* arc, Graph* G){
  if(hash(arc->faces[0]->label, arc->origin) == hash(arc->faces[1]->label, arc->origin)){
    int aux = arc->origin;
    arc->origin = arc->dest;
    arc->dest = aux;
  }
  arc->oriente = 1;
}

void updateEdge(Graph* G){
  for(int i = 0 ; i < G->nbsom ; i++){
    int j = (i+1)%(G->nbsom);
    while(!((hash(G->arcs[i][j]->faces[0]->label, G->arcs[i][j]->origin) == hash(G->arcs[i][j]->copy->faces[1]->label, G->arcs[i][j]->copy->dest)) && (hash(G->arcs[i][j]->faces[0]->label, G->arcs[i][j]->dest) == hash(G->arcs[i][j]->copy->faces[1]->label, G->arcs[i][j]->copy->origin))) && !((hash(G->arcs[i][j]->faces[0]->label, G->arcs[i][j]->origin) == hash(G->arcs[i][j]->copy->faces[1]->label, G->arcs[i][j]->copy->origin)) && (hash(G->arcs[i][j]->faces[0]->label, G->arcs[i][j]->dest) == hash(G->arcs[i][j]->copy->faces[1]->label, G->arcs[i][j]->copy->dest)))){
      switchLabel(G->arcs[i][j]->faces[0]);
    }
  }
}


Graph** enumRand(int genre){
  Node** tabtree = malloc((genre+1) * sizeof(Node*));
  for(int i = 1 ; i <= genre ; i++){
    tabtree[i-1] = treeMin();
    tabtree[i-1] = randTree(tabtree[i-1], (i*4)-1, 2, 'D');
  }
  
  tabtree[genre] = NULL;
  Graph** tabtriang = malloc((genre+1)*sizeof(Graph*));
  tabtriang[genre] = NULL;
  Edge*** extedges = malloc((genre+1)*sizeof(Edge**));
  extedges[genre] = NULL;
  for(int i = 0 ; i < genre ; i++){
    tabtriang[i] = triangulation(tabtree[i], i+1, extedges[i]);
  }

   return tabtriang;
}

Graph* triangulation(Node* tree, int genre, Edge** extedges){
  int k = 0;
  int nbsom = genre * 4;
  File* field = NULL;
  enumfield(tree, &field);
  extedges = extEdges(tree);
  Graph* graph = malloc(sizeof(graph));
  graph->faces = malloc((nbsom-2) * sizeof(Face*));
  allocGraph(extedges, graph, genre);
  tree->link = graph->arcs[0][1];
  for(int j = 1 ; j < nbsom-1 ; j++){
    front(field)->link = graph->arcs[j][j+1];
    push(&field, front(field));
    pop(&field);      
  }
  front(field)->link = graph->arcs[nbsom-1][0];
  push(&field, front(field));
  pop(&field);

  Node* tmp = NULL;
  while(size(field) > 2){
    tmp = front(field);
    pop(&field);
    if(front(field)->parent == tmp->parent){
      graph->arcs[tmp->link->origin-1][front(field)->link->dest-1] = malloc(sizeof(Edge));
      graph->arcs[tmp->link->origin-1][front(field)->link->dest-1]->origin = tmp->link->origin;
      graph->arcs[tmp->link->origin-1][front(field)->link->dest-1]->dest = front(field)->link->dest;
      graph->arcs[tmp->link->origin-1][front(field)->link->dest-1]->oriente = 0;
      graph->arcs[tmp->link->origin-1][front(field)->link->dest-1]->couleur = -1;
      graph->arcs[front(field)->link->dest-1][tmp->link->origin-1] = graph->arcs[tmp->link->origin-1][front(field)->link->dest-1];

      tmp->parent->link = graph->arcs[tmp->link->origin-1][front(field)->link->dest-1];
      
      graph->faces[k] = createFace(tmp->parent->link->dest, front(field)->link->origin, tmp->link->origin);
      tmp->parent->link->faces = malloc(2* sizeof(Face*));
      tmp->parent->link->faces[0] = graph->faces[k];
      graph->arcs[tmp->link->origin-1][front(field)->link->dest-1]->faces[1] = NULL;
      tmp->link->faces[1] = graph->faces[k];
      front(field)->link->faces[1] = graph->faces[k];
      
      k++;

      push(&field, tmp->parent);
      pop(&field);

    }
    else{
      push(&field, tmp);
    }
  }
  tmp = front(field);
  pop(&field);

  int a,b,c;
  if(tmp->link->origin < tmp->link->dest){
    a = tmp->link->dest;
  }
  else{
    a = tmp->link->origin;
  }
  
  graph->faces[k] = createFace(tmp->parent->link->origin, a, tmp->parent->link->dest);
  
  tmp->link->faces[1] = graph->faces[k];
  tmp->parent->link->faces[1] = graph->faces[k];
  front(field)->link->faces[1] = graph->faces[k];

  return graph;

}
