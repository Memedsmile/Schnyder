#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

void beginDocument(FILE *desc);
void endDocument(FILE* desc);
void beginTikz(FILE* desc);
void endTikz(FILE* desc);
void displayNode(FILE* desc, int nbsom);
void displayArcs(FILE* desc, Edge* arc);
void displayGraph(FILE* desc, Graph* G);
void enumGraph(FILE*desc,Graph** tabG);
