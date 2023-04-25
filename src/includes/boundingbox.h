#ifndef BOUNDINGBOX_H
# define BOUNDINGBOX_H

/**
 * \brief Cette classe implémente l'équivalent d'une hitbox
*/
class BoundingBox
{
	public:
		int x, y, w, h;
		/**
		 * \brief Dit si un point appartient à la hitbox
		 * \param x: La coordonnée x du point à tester
		 * \param y: La coordonnée y du point à tester
		*/
		bool belong_to(int x, int y);

		/**
		 * \brief Crée une hitbox positionnée en (x, y) de taille w par h
		 * \param x : La coordonnée x du départ de la hitbox
		 * \param y : La coordonnée y du départ de la hitbox
		 * \param w : La width (largeur) de la hitbox
		 * \param h : La hauteur de la hitbox
		*/
		BoundingBox(int x, int y, int w, int h);
};

#endif