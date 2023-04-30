#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>

/**
 * \enum Jeux
 * \brief Représente de façon textuelle les différents nombres de jeux possibles, 1,3 ou 6
*/
typedef enum Jeux {
	UN_JEU = 1,
	TROIS_JEUX = 3,
	SIX_JEUX = 6
} Jeux;


/**
 * \brief Une classe simple pour instancier une variable de type Jeux
*/
class Format
{
	private :
		Jeux nb_jeux;

	public :

		/**
		 * \brief Initalise un format de match à 1 jeu
		*/
		Format();

		/**
		 * \brief Initalise un format de match selon les paramètres. Le true sera donc le format de match pris en compte
		 * \param un : Booléen pour un match à un jeu
		 * \param trois : Booléen pour un match à trois jeux
		 * \param six : Booléen pour un match à six jeux
		*/
		Format(Jeux nb_jeux);

		/**
		 * \brief Desctructeur de la classe Format
		*/

		~Format();

		/**
		 * \brief Permet de savoir dans quel format de jeu on est
		 * \returns Le nombre de jeux, représenté par l'enum correspondante
		*/
		Jeux get_jeux() const;

		/**
		 * \brief Modifie le statut du format de match correspondant aux nombre de jeux
		 * \param nb_jeux : Le nombre de jeux (1,3,6), représenté par l'enum Jeux ou par un cast de types.
		*/
		void set_jeux(Jeux nb_jeux);

		/**
		 * \brief Effectue un test des différentes fonctions membres de la classe
		*/

		bool test();
};

#endif
