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
         * \returns Nothing, the class is just modified
        */
        void operator*=(const float f);

        /**
         * \brief This function follows our standards and performs tests
         * \returns true if all the test went good, false/assert exception if not
        */
        bool test();
};

#endif