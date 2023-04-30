#ifndef BALLE_H
# define BALLE_H

# include "vec2.h"

/**
 * \brief Cette classe implémente une simple balle
 * 
 * On considère que les trajectoires de la balle sont rectilignes
*/
class Balle
{
	private:
		Vec2 pos = Vec2(0,0);
		float hauteur = 1;
		Vec2 traj = Vec2(0,0); /**< La trajectoire est en unités/seconde */
		
		Vec2 aterrisage = Vec2(0,0); /**< Une position d'aterissage en unités du plan*/
		float descente = 0.1; /**< Pour chaque unité du plan parcourue (projeté au sol), le nombre d'unités du plan descendues*/

	public:

		/**
		 * \brief Constructeur de la classe Balle
		*/
		Balle();

		/**
		 * \brief Constructeur de la classe Balle
		 * \param pos : Position de la balle
		 * \param traj: Trajectoire de la balle
		*/
		Balle(Vec2 pos, Vec2 traj);

		/**
		 * \brief Constructeur de classe Balle
		 * \param pos : Position de la balle
		 * \param traj: Trajectoire de la balle
		 * \param descente : Trajectoire de descente de la balle 
		*/
		Balle(Vec2 pos, Vec2 traj, float descente);

		/**
		 * \brief Constructeur de la classe Balle
		 * \param pos : Position de la balle
		 * \param traj : Trajectoire de la balle
		 * \param atter : Position d'atterrissage de la balle
		*/
		Balle(Vec2 pos, Vec2 traj, Vec2 atter);

		/**
		 * \brief Constructeur de la classe Balle
		 * \param pos : Position de la balle
		 * \param traj : Trajectoire de la balle
		 * \param descente : Trajectoire de descente de la balle
		 * \param atter : Position d'atterrissage de la balle
		*/
		Balle(Vec2 pos, Vec2 traj, Vec2 atter, float descente);

		/**
		 * \brief Destructeur de la classe Balle
		*/
		~Balle();

		/**
		 * \brief Retourne la position de la balle
		*/
		Vec2 get_pos() const;

		/**
		 * \brief Modifie la position de la balle
		 * \param pos : La nouvelle position
		*/
		void set_pos(Vec2 pos);

		/**
		 * \brief Retourne la trajectoire de la balle
		*/
		Vec2 get_traj() const;

		/**
		 * \brief Modifie la trajectoire de la balle
		 * \param pos : La nouvelle trajectoire
		*/
		void set_traj(Vec2 pos);

		/**
		 * \brief Retourne la hauteur de la balle
		*/
		float get_hauteur() const;

		/**
		 * \brief Modifie la hauteur de la balle
		 * \param hauteur : La nouvelle hauteur
		*/
		void set_hauteur(float hauteur);

		/**
		 * \brief Retourne true si la balle a rebondi
		*/
		bool a_rebondi() const;
		
		/**
		 * \brief Retourne la position d'atterrissage de la balle
		*/
		Vec2 get_aterissage() const;

		/**
		 * \brief Calcule où est-ce que la balle devrait atterir 
		*/
		void calcule_aterissage();

		/**
		 * \brief La fonction met a jour la balle en fonction du temps
		 * \param temps : Le temps
		*/
		void avancer_temps(float temps);

		/**
		 * \brief Effectue de nombreux tests pour la classe Balle
		*/
		bool test();
};

#endif
