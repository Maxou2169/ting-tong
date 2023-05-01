#ifndef TEXTE_H
#define TEXTE_H

#include "joueur.h"
#include "balle.h"
#include "terrain.h"

/**
 * \class Texte
 * \brief Cette classe présente une version intermediaire du jeu en mode texte
*/

class Texte
{
	private:
		Terrain &terrain;

	public:

		/**
		 * \brief Constructeur de la classe Texte
		 * \param t : Le terrain
		*/
		Texte(Terrain &t);

		/**
		 * \brief Destructeur de la classe Texte
		*/
		~Texte();

		/**
		 * \brief Permet l'affichage textuel
		*/
		void texte();
};

#endif