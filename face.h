#ifndef FACE_H
#define FACE_H

#include <stdio.h>
#include <stdlib.h>

/**
 * \struct Face
 * \brief Objet Face d'un graphe
 *
 * Face est un objet représentant une face d'un graphe
 * Il contient l'étiquetage de la face, le nombre d'étiquetage possible.
 */

typedef struct Face Face;
struct Face{
  int** label; /*!< Tableau 2*3 contenant la clé des 3 sommets de la face et le label correspondant*/
  int nblabel; /*!< Nombre de label possible */
  int colored; /*!< Booléen = 1 si la face est colorée et 0 sinon*/
};

/**
 * \fn int hash(int** tab, int key)
 * \brief Fonction de hashage qui recupère le label d'un sommet par sa clé.
 * \param tab Tableau de label à hasher
 * \param key Clé du sommet dont on recherche le label
 * \return Label du sommet "key"
 */
int hash(int** tab, int key);

/**
 * \fn Face* createFace(int a, int b, int c)
 * \brief Fonction de création d'une face. Associe un label à chaque sommet de la face.
 * \param a, b, c Trois sommets formant la face
 * \return La face créée
 */
Face* createFace(int a, int b, int c);


/**
 * \fn void printFace(Face* f)
 * \brief Fonction d'affichage d'une face
 * \param f La face à affichée
 */
void printFace(Face* f);

/**
 * \fn void switchLabel(Face* f)
 * \brief Fonction permettant de tourner le label dans une face
 * \param La face dont le label doit être tourner
 */
void switchLabel(Face* f);



#endif

  
