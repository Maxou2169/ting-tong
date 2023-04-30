#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include "joueur.h"
#include "balle.h"
#include "format.h"

const float BORDER_X_SIZE = 5.0;
const float BORDER_Y_SIZE = 15.0;

/**
 * \brief Le terrain représente la partie de tennis. Elle a 2 joueurs, une balle et un format
*/
class Terrain
{
	private :
		Joueur joueur_a;
		Joueur joueur_b;
		Balle balle;
		Format format;


		/**
		 * \brief Repousse le joueur allant trop à droite
		*/

		void repousser_x_positif(Joueur &j);

		/**
		 * \brief Repousse le joueur allant trop à gauche
		*/

		void repousser_x_negatif(Joueur &j);

		/**
		 * \brief Repousse le joueur allant trop haut
		*/

		void repousser_y_positif(Joueur &j);

		/**
		 * \brief Repousse le joueur allant trop bas
		*/

		void repousser_y_negatif(Joueur &j);

		/**
		 * \brief Repousse le joueur du haut par rapport au filet
		*/

		void repousser_filet_joueur_a();

		/**
		 * \brief Repousse le joueur du bas par rapport au filet
		*/

		void repousser_filet_joueur_b();
	
	public:
		/**
		 * \brief Initialise un terrain avec deux joueur et une balle
		 * \param x : Le joueur 1
		 * \param y : Le joueur 2
		 * \param b : La balle
		*/
		Terrain(Joueur x, Joueur y, Balle b, Format f);

		/**
		 * \brief Desctructeur de la classe Terrain
		*/

		~Terrain();

		/**
		 * \brief Retourne le joueur a
		*/
		Joueur & get_joueur_a();

		/**
		 * \brief Retourne le joueur b
		*/
		Joueur & get_joueur_b();

		/**
		 * \brief Retourne la balle du terrain
		*/
		Balle & get_balle();

		/**
		 * \brief Retourne le format du match
		*/

		Format get_format();

		/**
		 * \brief Modifie le joueur a par le joueur j
		 * \param j : Le nouveau joueur
		*/
		void set_joueur_a(Joueur j);

		/**
		 * \brief Modifie le joueur b par le joueur j
		 * \param j : Le nouveau joueur
		*/
		void set_joueur_b(Joueur j);

		/**
		 * \brief Modifie la balle par la balle b
		 * \param b : La nouvelle balle
		*/
		void set_balle(Balle b);

		/**
		 * \brief Modifie le format par le format f
		 * \param f : Le nouveau format
		*/
		void set_format(Format f);

		/**
		 * \brief Cette fonction teste que le terrain soit bien défini et que celui-ci fonctionne
		*/
		bool test();

		/**
		 * \brief Cette fonction vérifie la position des joueurs, et les "repousse" si nécessaire
		*/
		void repousser();

		/**
		 * \brief Cette fonction permet de retourner vraie dans le cas où le joueur a a gagné le point
		 * \note Cette fonction mets AUSSI à jour le score sans intervention de l'utilisateur
		*/

		bool joueur_a_gagne_point();

		/**
		 * \brief Cette fonction permet de retourner vraie dans le cas où le joueur b a gagné le point
		 * \note Cette fonction mets AUSSI à jour le score sans intervention de l'utilisateur
		*/

		bool joueur_b_gagne_point();

		/**
		 * \brief Cette fonction place la balle au bon endroit pour faire un service sur un des deux joueurs
		 * 
		 * Cette fonction choisit aléatoirement un des deux joueurs et le fait servir.
		 * Un service est une balle placée un peu en haut à droite du joueur
		 * Les joueurs sont replacés dans leurs carrés de service
		*/
		void service();

		/**
		 * \brief Cette fonction vérifie si un des joueurs vient de gagner un point et remet un service
		*/
		void maj_points_service();

		/**
		 * \brief Cette fonction renvoie true si le service doit être à droite
		*/

		bool service_a_droite();
};


#endif
