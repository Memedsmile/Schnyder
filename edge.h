#ifndef EDGE_H
#define EDGE_H

#include "face.h"

/**
 * \struct Edge
 * \brief Objet Arête/Arc
 *
 * Edge est un objet représentant une arête ou un arc d'un graphe.
 * Il contient les proprietés d'une arête, ainsi que les pointeurs vers les faces adjacentes à l'arête et l'arête copie si c'est une arête externe
 */
typedef struct Edge Edge;
struct Edge{
  int origin; /*!< Clé du sommet origine de l'arête*/
  int dest; /*!< Clé du sommet destination de l'arête*/
  int couleur; /*!<0 pour rouge, 1 pour bleu, 2 pour vert */
  int oriente;  /*!< booleen = 1 si l'arête est orienté, 0 sinon */
  Face** faces; /*!< Tableau des 2 faces adjacentes à l'arête*/
  Edge* copy; /*!< Arête copie si c'est une arête externe et NULL sinon*/
};

/**
 * \fn void afficheEdge(Edge* arc)
 * \brief Fonction permettant d'afficher une arête
 * \param L'arête à afficher
 */
void afficheEdge(Edge* arc);

/**
 * \fn int equalsEdge(Edge* arc1, Edge* arc2)
 * \brief Fonction permettant de verifier l'équivalence de 2 arêtes
 * \param arc1, arc2 Les 2 arcs à comparer
 * \return 1 si les 2 arètes sont égales et 0 sinon
 */
int equalsEdge(Edge* arc1, Edge* arc2);

/**
 * \fn void freeEdge(Edge* arc)
 * \brief Fonction permettant de detruire une arête
 * \param arc L'arête à détruire
 */
void freeEdge(Edge* arc);

/**
 * \fn int colorEdge(Edge* arc)
 * \brief Fonction permettant de calculer la couleur d'une arête
 * \param arc L'arête à colorer
 * \return L'entier correspondant à la couleur de l'arête ou -1 si l'arête n'est pas colorable
*/
int colorEdge(Edge* arc);







#endif
