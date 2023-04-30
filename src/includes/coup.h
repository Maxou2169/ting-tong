#ifndef COUP_H
#define COUP_H

#include "joueur.h"
#include "balle.h"

/**
 * \brief La classe coup correspond au coup d'un joueur, que ce soit un coup droit ou un revers
 * Il suffit d'instancier cette classe pour pouvoir jouer un coup,
 * la classe décidera de quel côté il faut tirer
 * On considère que le joueur est droitier <==> le coup droit est tiré main droite
*/

class Coup
{
	private : 
		Joueur & joueur;
		Balle & balle;

		/**
		 * \brief Vérifie si le joueur peut effectuer son coup ou non
		*/
	
		bool peut_faire_coup();

		/**
		 * \brief Cette classe fait un coup
		 * Un coup est formé de la manière suivante : 
		 *  - selon la position du joueur et de la balle, on décide entre coup droit et revers
		 *  - on choisit ensuite aléatoirement un point ou la balle doit arriver (dans le coin supérieur droit si le joueur du bas fait un revers)
		 *  - on limite la hauteur de ce point d'arrivée selon si c'est un service ou non (un service doit forcément passer dans le carré de service [de hauteur 5])
		 *  - On met le vecteur directeur de la balle de façon à guider la balle vers ce point (point_arrivée - pos_balle)
		*/
		void faire_coup();
	   
	public :
		
		/**
		 * \brief Initialise et effectue un coup
		 * \param j : Un joueur
		 * \param b : Une balle
		*/
		
		Coup(Joueur & j, Balle &b);

		/**
		 * \brief Destructeur de la classe Coup
		*/

		~Coup();

		/**
		 * \brief Effectue un test des différentes fonctions membres de la classe
		*/

		bool test();
};


#endif