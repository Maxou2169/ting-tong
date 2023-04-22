#ifndef VEC2_H
# define VEC2_H

/**
 * \brief This class implements a simple Vector in 2D.
 * 
 * This class implmenets arithmetics and representation of Vector/Point
*/

class Vec2
{
	private:
		float x;
		float y;
	
	public:
		Vec2(float x, float y);
		Vec2();
		~Vec2();

		/**
		 * \brief This function returns the x parameter of this 2D Vector
		*/
		float get_x() const;
		/**
		 * \brief This function sets the x parameter of this 2D Vector
		 * \param x : A value representing the x-coordinate of the point
		*/
		void set_x(float x);

		/**
		 * \brief  This function returns the y parameter of this 2D Vector
		*/
		float get_y() const;
		/**
		 * \brief This function sets the y coordinate of this Vector
		 * \param y : The y coordinate of this Vector
		*/
		void set_y(float y);

		/**
		 * \brief This function returns the norm of the vector
		 * \returns The norm of the vector
		*/
		float norm() const;

		/**
		 * \brief Normalise le vecteur
		*/
		void normalise();
		
		/**
		 * \brief This function adds a second vector and returns it
		 * 
		 * \returns A new Vec2
		*/
	   Vec2 operator+(Vec2 const& to_add) const;

		/**
		 * \brief This function removes a vector from another one
		 * \returns A new Vec2
		*/
	   Vec2 operator-(Vec2 const& to_add) const;

		/**
		 * \brief This function multiplies two vectors
		 * \returns A new Vec2
		*/
	   Vec2 operator*(Vec2 const& to_add) const;

		/**
		 * \brief This function implments the operation * between a scalar and a vector
		 * \returns A new vec2
		*/
		Vec2 operator*(const float f) const;

		/**
		 * \brief This function implments the operation *= between a scalar and a vector
		*/
		void operator*=(const float f);

		/**
		 * \brief This function implements the += operator on two Vec2, it adds separately the x and ys
		*/
		void operator+=(Vec2 const& to_add);

		/**
		 * \brief This function implements the -= operator on two Vec2, it modifies separately the xs and ys
		*/
		void operator -=(Vec2 const & to_add);

		/**
		 * \brief This function compares two vectors. Those vectors are equal if x1 = x2 and y1 = y2
		 * \returns A boolean, representing the (in)equality
		*/
		bool operator==(Vec2 const & to_compare) const;
		bool test();
};

#endif