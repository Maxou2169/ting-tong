#ifndef BALLE_H
# define BALLE_H

# include "vec2.h"

/**
 * \brief Cette classe implémente une simple balle
 * \author Ethan PEGEOT <ethan.pegeot@etu.univ-lyon1.fr>
 * 
 * On considère que les trajectoires de la balle sont rectilignes
*/
class Balle
{
    private:
        Vec2 pos;
        float hauteur;
        Vec2 traj; /**< La trajectoire est en unités/seconde */
        
        Vec2 aterrisage; /**< Une position d'aterissage en unités du plan*/
        float descente; /**< Le nombre d'unités du plan descendues pour chaque seconde*/

    public:
        Balle(Vec2 pos, Vec2 traj);
        ~Balle();

        Vec2 get_pos() const;
        void set_pos(Vec2 pos);

        Vec2 get_traj() const;
        void set_traj(Vec2 pos);

        float get_vitesse() const;
        void set_vitesse(float v);

        float get_hauteur() const;
        void set_hauteur(float hauteur);

        bool a_rebondi() const;

        Vec2 get_aterissage() const;

        /**
         * \brief Calcule ou est-ce que la balle devrait atterir 
        */
        void calcule_aterissage();

        /**
         * \brief This function updates the position and speed of the ball according to where it is
         * \param temps : Temps est en secondes, le temps écoulé depuis la dernière m-à-j
        */
        void avancer_temps(float temps);

        /**
         * This function executes regression tests from the class, it uses assert() to check if the tests are valid
         * \note The program may crash if those tests fails
        */
        bool test();
};

#endif