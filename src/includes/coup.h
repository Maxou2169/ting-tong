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
		 * \brief Si le joueur peut faire un coup alors la fonction lui permet de le faire
		*/
		void faire_coup();

		/**
		 * \brief Cette fonction execute un coup droit
		 * Un coup droit fait partir la balle sur la gauche du joueur qui tire
		*/
		void coup_droit();
		/**
		 * \brief Cette fonction execute un coup droit
		 * Un coup droit fait partir la balle sur la gauche du joueur qui tire
		*/
		void revers();
	   
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