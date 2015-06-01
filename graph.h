#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include "tree.h"

/**
 * \struct Graph
 * \brief Objet Graphe
 *
 * Graph est un objet représentant un graphe par matrice d'adjacence
 * Il contient les proprietés d'un graphe, ainsi qu'une liste de faces internes et externes
 */
typedef struct Graph Graph;
struct Graph{
  int nbsom; /*!< Nombre de sommets du graphe*/
  Edge*** arcs; /*!< Matrice d'ajacence d'arête*/
  int genre; /*!< Genre du graphe*/
  Face** faces; /*!< Liste des faces internes*/
  Face** faceext; /*!< Liste des face externes*/
};

/**
 * \fn void allocGraph(Edge** edges, Graph* T, int _nbsom)
 * \brief Fonction de creation d'un graphe
 * \param edges tableau d'arêtes à inserer dans le graphe
 * \param T Graphe servant de receptacle au graphe créé (initialement NULL)
 * \param _nbsom Nombre de sommet du graphe à créer
 */
void allocGraph(Edge** edges, Graph* T, int genre);

/**
 * \fn void updateGraph(Edge* arcs, Graph* T)
 * \brief Fonction de mise à jour de l'orientation d'une arête
 * \param arcs Arête à orienté ou désorienté
 * \param T graphe contenant l'arête à orienté ou désorienté
 */
void updateGraph(Edge* arcs, Graph* T);

/**
 * \fn void afficheGraph(Graph* G)
 * \brief Fonction d'affichage du graphe dans le terminal
 * \param G Graphe à afficher
 */
void afficheGraph(Graph* G);

/**
 * \fn int equalsGraph(Graph G1, Graph G2)
 * \brief Fonction de verification d'équivalence de graphe
 * \param G1, G2 Les 2 graphes à comparer
 */
int equalsGraph(Graph G1, Graph G2);

/**
 * \fn void freeGraph(Graph* G)
 * \brief Fonction de destruction d'un graphe
 * \param G Le graphe à détruire
 */
void freeGraph(Graph* G);

/* Manipulation d'arêtes dans le graphe */

/**
 * \fn void retourner(Edge* arc, Graph* G)
 * \brief Fonction qui retourne un arc orienté 
 * \param arc arc à retourner
 * \param G Le graphe contenant l'arc à retourner
 */
void retourner(Edge* arc, Graph* G);

/**
 * \fn void orienter(Edge* arc, Graph* G)
 * \brief Fonction qui oriente une arête
 * \param arc arc à orienter
 * \param G Le graphe contenant l'arc à orienter
 */
void orienter(Edge* arc, Graph* G);

/* Création de triangulation */

/**
 * \fn Edge** extEdges(Node* tree)
 * \brief Fonction qui construit un tableau d'arête, à partir des feuilles d'un arbre, qui seront les arêtes externes du graphe
 * \param tree Arbre binaire qui va servir de base pour la triangulation
 */
Edge** extEdges(Node* tree);

//void NdEdge(Node* tree, Graph* T);

//void triangulate(File* field, Graph* T);

//Graph* triangulation(Node* tree);

/**
 * \fn Graph** enumTriang(int nbsom)
 * \brief Fonction qui énumère l'ensemble des triangulationsd'un polygone à n sommets dans un tableau
 * \param nbsom = n Le nombre de sommets du polygone à trianguler
 * \return Tableau de graphe triangulé à n sommet
 */
Graph** enumTriang(int nbsom);

/**
 * \fn void coloring(Graph* G, int i)
 * \brief Fonction qui colorie et oriente les arêtes d'un graphe triangulé
 * \param G Le graphe à colorer
 * \param i Numéro de la face coloré dans la recurtion (initialement 0)
 */
void coloring(Graph* G, int i, int k);

/**
 * \fn int coloriable(Face* f, Graph* G)
 * \brief Fonction qui verifie si une face est colorable en fonction du label qui lui est attribué
 * \param G Le graphe à colorer
 * \param f La face à vérifier
 * \return 1 si le label de f permet une coloration et 0 sinon
 */
int coloriable(Face* f, Graph* G);

/**
 * \fn int** voisins(Face* f, Graph* G)
 * \brief Fonction qui calcul les labels adjacents à la face f étudiée
 * \param G Le graphe à colorer
 * \param f La face étudiée
 * \return Un tableau contenant les labels des arêtes de f sur les faces adjacentes à f 
 */
int** voisins(Face* f, Graph* g);

/**
 * \fn int bloquer(Face* f, Graph* G)
 * \brief Fonction qui vérifie si la face f est bloquée
 * \param G Le graphe à colorer
 * \param f La face étudiée
 * \return 1 si il n'existe pas de label pour f permettant le coloriage de f 
 */
int bloquer(Face* f, Graph* g);

/**
 * \fn void colorier(Face* f, Graph* g)
 * \brief Fonction qui colorie une face f si son label le permet
 * \param G Le graphe à colorer
 * \param f La face à colorier
 */
void colorier(Face* f, Graph* g);

/**
 * \fn Face** listVoisins(Face* f, Graph* g)
 * \brief Fonction qui liste les trois faces voisines de f
 * \param G Le graphe à colorer
 * \param f La face étudiée
 * \return Tableau de 3 faces voisines de f
 */
Face** listVoisins(Face* f, Graph* g);

/**
 * \fn int voisinExt(Face* f, Graph* g)
 * \brief Fonction qui calcule le nombre de faces voisines "externes"
 * \param G Le graphe à colorer
 * \param f La face étudiée
 * \return Le nombre de faces voisines "externes" {0,1,2}
 */
int voisinExt(Face* f, Graph* g);

/**
 * \fn int faceext(Face* f, Graph* g)
 * \brief Fonction qui verifiesi la face f est une face "externes"
 * \param G Le graphe à colorer
 * \param f La face étudiée
 * \return 1 si f est une face externe et 0 sinon
 */
int faceext(Face* f, Graph* g);


/**
 * \fn void switchvoisext(Face* f, Graph* g)
 * \brief Fonction qui 
 * \param G Le graphe à colorer
 * \param f La face étudiée
 */
int switchvoisext(Face* f, Graph* g);

void switchback(Face* f, Graph* g);
/**
 * \fn Face* choixVoisin(Face* f, Graph* g)
 * \brief Fonction qui choisit une face voisine interne avec le moins de voisines externe possible
 * \param G Le graphe à colorer
 * \param f La face étudiée
 * \return La face voisine ayant le moins de voisines externes
 */
Face* choixVoisin(Face* f, Graph* g);

Face* choixvoisext(Face* f, Graph* G);

/**
 * \fn int countlabel(Face* f, Graph* g)
 * \brief Fonction qui calcule le nombre de label permettant une coloration d'une face f donnée
 * \param G Le graphe à colorer
 * \param f La face étudiée
 * \return Le nombre de label possible pour f
 */
int countlabel(Face* f, Graph* g);

/**
 * \fn void orienter(Edge* arc, Graph* G)
 * \brief Fonction qui oriente une arête en fonction de ses labels
 * \param G Le graphe à colorer
 * \param arc L'arête à orienter
 */
void orienter(Edge* arc, Graph* G);

/**
 * \fn void updateEdge(Graph* G)
 * \brief Fonction qui met à jour les labels des arêtes externes du graphe G en verifiant les arêtes copiées
 * \param G Le graphe à colorer
 */
void updateEdge(Graph* G);

Graph* triangulation(Node* tree, int genre, Edge** extedges);

Graph** enumRand(int genre);

#endif
