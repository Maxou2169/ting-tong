#ifndef VEC3_H
# define VEC3_H

/**
 * \brief This class implements a simple Vector in 3D.
 * 
 * This class implmenets arithmetics and representation of Vector/Point
*/

class Vec3
{
    private:
        float x;
        float y;
        float z;
    
    public:
        Vec3(float x, float y, float z);
        Vec3();
        ~Vec3();

        /**
         * \brief This function returns the x parameter of this 3D Vector
        */
        float get_x() const;
        /**
         * \brief This function sets the x parameter of this 3D Vector
         * \param x : A value representing the x-coordinate of the point
        */
        void set_x(float x);

        /**
         * \brief  This function returns the y parameter of this 3D Vector
        */
        float get_y() const;
        /**
         * \brief This function sets the y coordinate of this Vector
         * \param y : The y coordinate of this Vector
        */
        void set_y(float y);

        /**
         * \brief  This function returns the z parameter of this 3D Vector
        */
        float get_z() const;
        /**
         * \brief This function sets the z coordinate of this Vector
         * \param y : The z coordinate of this Vector
        */
        void set_z(float y);

        /**
         * \brief This function returns the norm of the vector
         * \returns The norm of the vector
        */
        float norm() const;

        /**
         * \brief This function adds a second vector and returns it
         * 
         * \returns A new Vec3
        */
       Vec3 operator+(Vec3 const& to_add) const;

        /**
         * \brief This function removes a vector from another one
         * \returns A new Vec3
        */
       Vec3 operator-(Vec3 const& to_add) const;

        /**
         * \brief This function implments the operation * between a scalar and a vector
         * \returns A new Vec3
        */
        Vec3 operator*(const float f) const;

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