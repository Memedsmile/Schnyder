#ifndef TREE_H
#define TREE_H

#include <time.h>

#include "node.h"
#include "file.h"


/**
 * \fn void copie(Node* tree, Node** cpy)
 * \brief Fonction de creation d'une copie d'un arbre
 * \param tree Pointeur sur l'arbre à copier
 * \param cpy arbre NULL, receptacle pour la copie
 */
void copie(Node* tree, Node** cpy);

/**
 * \fn Node* treeMin()
 * \brief Fonction d'un arbre minimum à trois sommets
 * \return L'arbre minimum à trois sommets
 */
Node* treeMin();

/**
 * \fn void enumfield(Node* tree, File** tabfield)
 * \brief Fonction qui liste les feuilles de l'arbre
 * \param tree Pointeur sur l'arbre
 * \param tabfield La file qui sert de receptacle aux feuilles
 */
void enumfield(Node* tree, File** tabfield);

/**
 * \fn int sizetab(Node** tab)
 * \brief Fonction qui calcule la taille d'un tableau de Node
 * \param tab Tableau de Node dont on calcule la taille
 * \return Taille du tableau
 */
int sizetab(Node** tab);

/**
 * \fn void addcopyTree(Node* child, Node** parent)
 * \brief Fonction qui calcule la taille d'un tableau de Node
 * \param tab Tableau de Node dont on calcule la taille
 * \return Taille du tableau
 */
void addcopyTree(Node* child, Node** parent);

/**
 * \fn void updatedepth(Node** tree)
 * \brief Fonction qui met à jour les profondeur des noeuds d'un arbre
 * \param tree L'arbre à mettre à jour
 */
void updatedepth(Node** tree);

/**
 * \fn Node** enumTree(Node*** T, int nbfield, int nbfact, int letter)
 * \brief Fonction qui enumère tout les arbre binaire à n feuilles
 * \param T Tableau de taille n qui contient des pointeur vers des tableaux d'arbres à i feuilles
 * \param nbfield = n le nombre de feuilles que doivent avoir les arbres
 * \param nbfact = i Le nombre de feuilles des arbres construit au passage i de la recursion(initialement 0)
 * \param letter caractère du nouveau noeud à crer(initialement NULL ou 0)
 */
Node** enumTree(Node*** T, int nbfield, int nbfact, int letter);

/**
 * \fn Node* randTree(Node* T, int nbfield, int nbfact, int letter)
 * \brief Fonction qui construit aléatoirement un arbre binaire à n feuilles
 * \param T un arbre binaire minimal à 2 feuilles
 * \param nbfield = n le nombre de feuilles que doit avoir l'arbre
 * \param nbfact = i Le nombre de feuilles de l'arbres construit au passage i de la recursion(initialement 2)
 * \param letter caractère du nouveau noeud à crer(initialement NULL ou 0)
 */
Node* randTree(Node* T, int nbfield, int nbfact, int letter);

#endif
