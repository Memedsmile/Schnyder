#include "tikz.h"

void beginDocument(FILE *desc){
  perror("fopen");
  char document[1000]; 
  strcpy(document,"\n\\documentclass[]{article}\n\\usepackage[utf8]{inputenc}\n\\usepackage[usenames,dvipsnames]{xcolor}\n\\usepackage{fullpage}\n\\usepackage[upright]{fourier}\n\\usepackage{tkz-graph}\n\\usepackage{fancyhdr}\n\\usepackage{multicol}\n\\begin{document}\n\n");
  fprintf(desc,"%s",document);
  return;
}

void endDocument(FILE* desc){
  char document[20];
  strcpy(document,"\\end{document}\n");
  fprintf(desc,"%s",document);
  fclose(desc);
  return;
}

void beginTikz(FILE* desc){
  char document[1000];
  sprintf(document,"\\begin{tikzpicture}[scale=0.8]\n");
  fprintf(desc,"%s",document);
}
  
void endTikz(FILE* desc){
  char document[200];
  sprintf(document,"\\end{tikzpicture}\n");
  fprintf(desc,"%s",document);
}

void displayNode(FILE* desc, int nbsom){
  char document[800];
  double angle = 360/nbsom;
  int offset = 0;
  for(int i = 0 ; i < nbsom ; i++){
    sprintf(document + offset, "\\node (P%d) at (%d:%d) {};\n", i+1, 90+i*360/nbsom, 3);
    offset = strlen(document);
  }
  fprintf(desc,"%s",document);
}

void displayArcs(FILE* desc, Edge* arc){
  char document[1000];
  switch(arc->couleur){
  case 0 :
    sprintf(document, "\\draw[->,>=latex,red] (P%d) -- (P%d);\n", arc->origin, arc->dest);
    break;
  case 1 :
    sprintf(document, "\\draw[->,>=latex,blue] (P%d) -- (P%d);\n", arc->origin, arc->dest);
    break;
  case 2 :
    sprintf(document, "\\draw[->,>=latex,green] (P%d) -- (P%d);\n", arc->origin, arc->dest);
    break;
  default :
    sprintf(document, "\\draw (P%d) -- (P%d);\n", arc->origin, arc->dest);
    break;
    }
      
  fprintf(desc,"%s",document);  
}

void displayGraph(FILE* desc, Graph* G){
  beginTikz(desc);
  displayNode(desc, G->nbsom);
  for(int i = 0 ; i < G->nbsom ; i++){
    for(int j = 0 ; j < G->nbsom ; j++){
      if(G->arcs[i][j]){
	displayArcs(desc, G->arcs[i][j]);
      }
    }
  }
  endTikz(desc);
}

void enumGraph(FILE*desc, Graph** tabG){
  char document[1000];
  strcpy(document, "\\begin{multicols}{3}\n");
  fprintf(desc, "%s", document);
  int i = 0;
  while(tabG[i] != NULL){
    strcpy(document, "\\centering\n");
    fprintf(desc, "%s", document);
    displayGraph(desc, tabG[i]);
    strcpy(document, "\\\\[1cm]\n");
    fprintf(desc, "%s", document);
    i++;
  }
  strcpy(document, "\\end{multicols}\n");
  fprintf(desc, "%s", document);
}

void enumGraphrand(FILE*desc, Graph** tabG){
  char document[1000];
  strcpy(document, "\\begin{tabular}{ccc}\n");
  fprintf(desc, "%s", document);
  int i = 0;
  while(tabG[i] != NULL){
    displayGraph(desc, tabG[i]);
    i++;
    if(i%3 == 0){
      if(i == 6)
	 strcpy(document, "\\\\\n\\\\\n&\n");
      else
	strcpy(document, "\\\\\n\\\\\n");
    }
    else	
      strcpy(document, "&\n");
    fprintf(desc,"%s", document);
  }
  strcpy(document, "\\end{tabular}\n");
  fprintf(desc, "%s", document);
}
