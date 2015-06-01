#ifndef NODE_H
#define NODE_H

#include "edge.h"

/**
 * \struct Node
 * \brief Objet Noeud/Arbre
 *
 * Node est un objet représentant un arbre binaire recursivement.
 * Il contient les proprietés d'un noeud de l'arbre, ainsi que les pointeurs vers les noeuds fils et parent.
 */

typedef struct Node Node;
struct Node{
  char id; /*!< Nom du noeud (non unique) */
  int nbsom; /*!< Nombre de noeuds dans le sous arbre */
  Node* lc; /*!< Sous arbre fils gauche */
  Node* rc; /*!< Sous arbre fils droit */
  Node* parent; /*!< Noeud père */
  int depth; /*!< Profondeur du noeud */
  Edge* link; /*!< Arète du graphe liée au noeud */
};

/**
 * \fn void addNode(char childid, Node** parent)
 * \brief Fonction d'ajout d'un noeud dans un arbre
 * \param childid Nom du nouveau noeud
 * \param parent Pointeur vers le noeud auquel sera ajouté le nouveau noeud
 */
void addNode(char childid, Node** parent);

/**
 * \fn Node* searchNode(Node* tree, char id)
 * \brief Fonction de recherche d'un noeud par son nom
 * \param tree Pointeur sur la racine de l'arbre dans lequel la recherche s'effectue
 * \param id Nom du noeud rechercher.
 * \return Pointeur sur le noeud rechercher
 */
Node* searchNode(Node* tree, char id);

/**
 * \fn int sizeTree(Node* tree)
 * \brief Fonction de calcul de la taille d'un arbre
 * \param tree Pointeur sur la racine de l'arbre dans lequel la recherche s'effectue
 * \return Nombre de noeud dans l'arbre
 */
int sizeTree(Node* tree);

/**
 * \fn void deleteTree(Node* tree)
 * \brief Fonction de destruction de l'objet Node
 * \param tree Pointeur sur la racine de l'arbre à détruire
 */
void deleteTree(Node* tree);

/**
 * \fn void printTree(Node* tree)
 * \brief Fonction d'affichage de d'un arbre
 * \param tree Pointeur sur la racine de l'arbre à affiché
 */
void printTree(Node* tree);

/**
 * \fn int printTreeLevel(Node* tree, int d)
 * \brief Fonction d'affiche d'un étage de l'arbre
 * \param tree Pointeur sur la racine de l'arbre à afficher
 * \param d Profondeur de l'étage à afficher
 * \return Nombre de noeud dans l'étage de l'arbre
 */
int printTreeLevel(Node* tree, int d);

#endif


  
