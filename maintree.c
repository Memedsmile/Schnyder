#include "tikz.h"
#include "tree.h"

char name[200] = "graph.tex";
char color[200] = "color.tex";
char random[200] = "rand.tex";
char colorand[200] = "schnyderand.tex";

int main(int argc, char *argv[]){

  puts("---------- Test Arbres ----------");
  
  char Key;
  Node* Arbre = NULL;

  addNode('A', &Arbre);
  addNode('B', &Arbre);
  addNode('C', &Arbre);
  addNode('D', &(Arbre->lc));
  addNode('E', &(Arbre->lc));
  addNode('F', &(Arbre->rc));
  addNode('G', &(Arbre->rc));
  addNode('H', &(Arbre->lc->lc));
  addNode('I', &(Arbre->lc->lc));
  addNode('J', &(Arbre->lc->rc));
  addNode('K', &(Arbre->lc->rc));
  addNode('L', &(Arbre->rc->lc));
  addNode('M', &(Arbre->rc->lc));
   
  puts("-------------------------------");
  /*
  printf("Arbre a %d sommets.\n", sizeTree(Arbre));

  printTree(Arbre);

  */
  
  /* puts("-------------------------------");

   printReverseTree(Arbre);

  puts("-------------------------------");

  Key = 'E';
  if(searchNode(Arbre, Key) == NULL) printf("La cle %c n'existe pas.\n", Key);
  else{
    printf("La cle %c existe.\n", Key);
    printTree(searchNode(Arbre, Key));
  }

  Key = 'Y';
  if(searchNode(Arbre, Key) == NULL) printf("La cle %c n'existe pas.\n", Key);
  else{
    printf("La cle %c existe.\n", Key);
    printTree(searchNode(Arbre, Key));
  }
   
  puts("-------------------------------");

  deleteTree(Arbre);
    
  puts("---------- Test Files ----------");

  File* fifo = NULL;

  push(&fifo, Arbre);
  push(&fifo, Arbre->lc);
  push(&fifo, Arbre->rc);
  push(&fifo, Arbre->lc->lc);
  push(&fifo, Arbre->lc->rc);

  printf("sizeof fifo = %d\n",size(fifo));
  printfile(fifo);

  printf("le premier élément de fifo est : %c\n Le dernier élément de fifo est : %c\n", front(fifo)->id, back(fifo)->id);
   
  pop(&fifo);
  
  printf("sizeof fifo = %d\n",size(fifo));
  printfile(fifo);
  
   printf("le premier élément de fifo est : %c\n Le dernier élément de fifo est : %c\n", front(fifo)->id, back(fifo)->id);

  if(empty(fifo))
    printf("fifo est vide\n");
  else printf("fifo contient %d éléments.\n", size(fifo));

  clear(&fifo);
  
  if(empty(fifo))
    printf("fifo est vide\n");
  else printf("fifo contient %d éléments.\n", size(fifo));

  puts("---------- Test Arbre de base ----------");

  
  /* 
  Node* abrbase = NULL;
  abrbase = treeBase(&abrbase);

  printTree(abrbase);

  File* field = NULL;
  enumfield(abrbase, &field);
  printf("Les feuilles de l'arbre sont : \n");
  printfile(field);
  
  Node* copy = NULL;

  copie(abrbase, &copy);

  printTree(copy);

  Node** trees = enumTree();

  for(int i=0 ; i < 66 ; i++){
    printTree(trees[i]);
  }
  

  Node* abrmin = treeMin();

  printTree(abrmin);
  
  int nbfield = 7;
  Node *** T = malloc(nbfield * sizeof(Node**));
  Node ** tabtree = enumTree(T, nbfield, 0, 0);
  printf("sizeof(T[%d]) = %d\n", nbfield, sizetab(tabtree));
   printTree(tabtree[2]);
  
  for(int i = 0 ; i < sizetab(tabtree) ; i++){
    printf("Arbre %d :\n",i); 
    printTree(tabtree[i]);
    printf("\n");
    }
  
  
  Node** tab = malloc(14 * sizeof(Node*));
  for(int i = 0 ; i < 13 ; i ++){
    tab[i]=searchNode(Arbre, 'A'+i);
  }
  tab[13] = NULL;

  int i = 0;

  printf("tab = %d\n", sizetab(tab));
  */

  //  Graph* T = triangulation(Arbre);

  // afficheGraph(T);

  //Graph** T = enumTriang(8);

  /* for(int i = 0 ; i < 132 ; i++){
    printf("triangulation %d :\n",i+1); 
    afficheGraph(T[i]);
    printf("\n");
    }
  */
  /*
  Node *** matricetree = malloc(7 * sizeof(Node**));
  Node ** tabtree = enumTree(matricetree, 7, 0, 0);
  int sizeT = sizetab(tabtree);
  printf("sizeT = %d\n", sizeT);
  Graph** tabtriang = malloc((sizeT+1)*sizeof(Graph*));
  tabtriang[sizeT] = NULL;
  File** field = malloc((sizeT+1)*sizeof(File*));
  field[sizeT] = NULL;
  Edge*** extedges = malloc((sizeT+1)*sizeof(Edge**));
  extedges[sizeT] = NULL;
  
  for(int i = 0 ; i < sizeT ; i++){
    field[i] = NULL;
    enumfield(tabtree[i], &field[i]);
    extedges[i] = extEdges(tabtree[i]);
    tabtriang[i] = malloc(sizeof(Graph));
    allocGraph(extedges[i], tabtriang[i], 8);
  
    tabtree[i]->link = tabtriang[i]->arcs[0][1];
    for(int j = 1 ; j < 7 ; j++){
      front(field[i])->link = tabtriang[i]->arcs[j][j+1];
      push(&field[i], front(field[i]));
      pop(&field[i]);      
    }
    front(field[i])->link = tabtriang[i]->arcs[7][0];
    push(&field[i], front(field[i]));
    pop(&field[i]);
    Node* tmp = NULL;
    while(size(field[i]) > 2){
      tmp = front(field[i]);
      pop(&field[i]);
      if(front(field[i])->parent == tmp->parent){
	tabtriang[i]->arcs[tmp->link->origin-1][front(field[i])->link->dest-1] = malloc(sizeof(Edge));
	tabtriang[i]->arcs[tmp->link->origin-1][front(field[i])->link->dest-1]->origin = tmp->link->origin;
       tabtriang[i]->arcs[tmp->link->origin-1][front(field[i])->link->dest-1]->dest = front(field[i])->link->dest;
       tabtriang[i]->arcs[tmp->link->origin-1][front(field[i])->link->dest-1]->oriente = 0;
       tabtriang[i]->arcs[tmp->link->origin-1][front(field[i])->link->dest-1]->couleur = -1;
       tabtriang[i]->arcs[front(field[i])->link->dest-1][tmp->link->origin-1] = tabtriang[i]->arcs[tmp->link->origin-1][front(field[i])->link->dest-1];

       tmp->parent->link = tabtriang[i]->arcs[tmp->link->origin-1][front(field[i])->link->dest-1];

       push(&field[i], tmp->parent);
       pop(&field[i]);
      }
      else{
	push(&field[i], tmp);
      }
    } 
  }
  */

  Graph** tabtriang = enumTriang(2);
   
  /*
  int i = 0;
  while(tabtriang[i] != NULL){
    for(int j = 0 ; j < 6 ; j++){
      printf("Face int %d :\n ", j);
      printFace(tabtriang[i]->faces[j]);
    }
    for(int j = 0 ; j < 8 ; j++){
      printf("Face ext %d :\n ", j);
      printFace(tabtriang[i]->faceext[j]);
    }
    coloring(tabtriang[i]);
    i++;
  }
  
  */
  int k = 0;
  
  FILE* desc = fopen(name,"w");  
  beginDocument(desc);
  enumGraph(desc, tabtriang);
  endDocument(desc);
  while(tabtriang[k] != NULL){
    printf("graph %d\n", k);
    updateEdge(tabtriang[k]);
    coloring(tabtriang[k], 0, 0);
    k++;
  }
  FILE* desc1 = fopen(color,"w");  
  beginDocument(desc1);
  enumGraph(desc1, tabtriang);
  endDocument(desc1);  
  
  
  /*   
  FILE* desc = fopen(name,"w");  
  beginDocument(desc);
  displayGraph(desc, tabtriang[k]);
  endDocument(desc);
  printf("graph %d\n", k);
    updateEdge(tabtriang[k]);
    for(int i = 0 ; i < tabtriang[k]->nbsom-2 ; i++){
    printf("face %d :\n", i);
    printFace(tabtriang[k]->faces[i]);
  }
  for(int i = 0 ; i < tabtriang[k]->nbsom ; i++){
    printf("face ext %d :\n", i);
    printFace(tabtriang[k]->faceext[i]);
  }
  coloring(tabtriang[k], 0, 0);
    
  FILE* desc1 = fopen(color,"w");  
  beginDocument(desc1);
  displayGraph(desc1, tabtriang[k]);
  endDocument(desc1);  
  */
  /*
  for(int i = 0 ; i < 132 ; i++){
    printf("triangulation % d : \n", i);
    for(int j = 0 ; j < 6 ; j++){
      printf("face %d : \n", j);
      printFace(tabtriang[i]->faces[j]);
    }
  }
  */
  /*
  Graph* G = tabtriang[0];
  afficheGraph(G);
  updateEdge(G);
  coloring(G);
  printf("apres update :\n");
  for(int i = 0 ; i < 6 ; i++){
    printf("face %d :\n", i);
    printFace(G->faces[i]);
  }
  for(int i = 0 ; i < 8 ; i++){
    printf("face ext %d :\n", i);
    printFace(G->faceext[i]);
  }

  */
  /*
  Node* T = treeMin();
  printf("ArbreMin :\n");
  printTree(T);
  printf("\n");
  randTree(T, 7, 2, 'D');
  printf("Arbre random :\n");
  printTree(T);
  printf("\n");  
  */

  Graph** randtriang = enumRand(7);
  // printf("titi\n");
  k = 0;
  
  FILE* desc2 = fopen(random,"w");  
  beginDocument(desc2);
  enumGraphrand(desc2, randtriang);
  endDocument(desc2);
  while(randtriang[k] != NULL){
    printf("graph rand %d\n", k);
    updateEdge(randtriang[k]);
    coloring(randtriang[k], 0, 0);
    k++;
  }
  FILE* desc3 = fopen(colorand,"w");  
  beginDocument(desc3);
  enumGraphrand(desc3, randtriang);
  endDocument(desc3);  
  

  
}
