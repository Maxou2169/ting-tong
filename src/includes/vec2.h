#ifndef VEC2_H
# define VEC2_H

/**
 * \brief Classe implémentant un vecteur 2D
 * 
 * This class implmenets arithmetics and representation of Vector/Point
*/

class Vec2
{
	private:
		float x;
		float y;
	
	public:
	
	/**
	 * \brief Initialise un vecteur 2D
	 * \param x : Abscisse
	 * \param y : Ordonnée
	*/
	Vec2(float x, float y);

	/**
	 * \brief Constructeur de la classe Vec2D
	*/
	Vec2();

	/**
	 * \brief Destructeur de la classe Vec2D
	*/
	~Vec2();

	/**
	 * \brief Cette fonction renvoie la coordonnée x de ce vecteur 2D
	*/
	float get_x() const;
	/**
	 * \brief Cette fonction définit la coordonnée x de ce vecteur 2D
	 * \param x : Une valeur représentant la coordonnée x du point
	*/
	void set_x(float x);

	/**
	 * \brief Cette fonction renvoie la coordonnée y de ce vecteur 2D
	*/
	float get_y() const;
	/**
	 * \brief Cette fonction définit la coordonnée y de ce vecteur 2D
	 * \param y : La coordonnée y de ce vecteur
	*/
	void set_y(float y);

	/**
	 * \brief Cette fonction renvoie la norme du vecteur
	 * \returns La norme du vecteur
	*/
	float norm() const;

	/**
	 * \brief Cette fonction normalise le vecteur
	*/
	void normalise();
	
	/**
	 * \brief Cette fonction ajoute un second vecteur et le renvoie
	 * 
	 * \returns Un nouveau Vec2
	*/
   Vec2 operator+(Vec2 const& to_add) const;

	/**
	 * \brief Cette fonction soustrait un vecteur à un autre
	 * \returns Un nouveau Vec2
	*/
   Vec2 operator-(Vec2 const& to_add) const;

	/**
	 * \brief Cette fonction multiplie deux vecteurs
	 * \returns Un nouveau Vec2
	*/
   Vec2 operator*(Vec2 const& to_add) const;

	/**
	 * \brief Cette fonction implémente l'opération * entre un scalaire et un vecteur
	 * \returns Un nouveau Vec2
	*/
	Vec2 operator*(const float f) const;

	/**
	 * \brief Cette fonction implémente l'opération *= entre un scalaire et un vecteur
	*/
	void operator*=(const float f);

	/**
	 * \brief Cette fonction implémente l'opérateur += sur deux Vec2, elle ajoute séparément les xs et ys
	*/
	void operator+=(Vec2 const& to_add);

	/**
	 * \brief Cette fonction implémente l'opérateur -= sur deux Vec2, elle modifie séparément les xs et ys
	*/
	void operator -=(Vec2 const & to_add);

	/**
	 * \brief Cette fonction compare deux vecteurs. Ces vecteurs sont égaux si x1 = x2 et y1 = y2
	 * \returns Un booléen, représentant l'(in)égalité
	*/
	bool operator==(Vec2 const & to_compare) const;
	bool test();

};

#endif