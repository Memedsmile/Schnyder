#ifndef FILE_H
#define FILE_H

#include "node.h"

/**
 * \struct File
 * \brief Objet File 
 *
 * File est un objet représentant une filede type FIFO contenant des Nodes
 * Il contient un pointeur sur un noeud et une file contenent les noeuds suivant
 */
typedef struct File File;
struct File{
  Node* noeud; /*!< Pointeur sur un noeud */
  File* next; /*!< File contenant les noeud suivant*/
};

/**
 * \fn void push(File** fifo, Node* noeud)
 * \brief Fonction permettant d'ajouter un noeud dans une file
 * \param fifo La file dans laquelle on ajoute un noeud
 * \param noeud Le noeud à ajouter
 */
void push(File** fifo, Node* noeud);

/**
 * \fn void pop(File** fifo)
 * \brief Fonction permettant de supprimer le premier noeud d'une file
 * \param fifo La file dans laquelle on supprimele premier noeud
 */
void pop(File** fifo);

/**
 * \fn void clear(File** fifo)
 * \brief Fonction permettant de vider un file
 * \param fifo La file à vider
 */
void clear(File** fifo);

/**
 * \fn int size(File* fifo)
 * \brief Fonction permettant de calculer la taille d'un file
 * \param fifo La file dont la taille est calculer
 * \return La taille de la file
 */
int size(File* fifo);

/**
 * \fn int empty(File* fifo)
 * \brief Fonction permettant de si une file est vide
 * \param fifo La file dont on vérifie si elle est vide
 * \return 1 si la file est vide et 0 sinon
 */
int empty(File* fifo);

/**
 * \fn Node* front(File* fifo)
 * \brief Fonction permettant de recuperer le premier noeud de la file
 * \param fifo La file dont on veut le premier noeud
 * \return Le premier noeud de la file
 */
Node* front(File* fifo);

/**
 * \fn Node* back(File* fifo)
 * \brief Fonction permettant de recuperer le dernier noeud de la file
 * \param fifo La file dont on veut le dernier noeud
 * \return Le dernier noeud de la file
 */
Node* back(File* fifo);


/**
 * \fn void printfile(File* fifo)
 * \brief Fonction permettant d'afficher une file
 * \param fifo La file à afficher
 */
void printfile(File* fifo);

#endif
