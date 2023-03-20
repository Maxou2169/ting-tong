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
        Vec2 pos = Vec2(0,0);
        float hauteur = 1;
        Vec2 traj = Vec2(0,0); /**< La trajectoire est en unités/seconde */
        
        Vec2 aterrisage = Vec2(0,0); /**< Une position d'aterissage en unités du plan*/
        float descente = 0.1; /**< Pour chaque unité du plan parcourue (projeté au sol), le nombre d'unités du plan descendues*/

    public:
        Balle();
        Balle(Vec2 pos, Vec2 traj);
        Balle(Vec2 pos, Vec2 traj, float descente);
        Balle(Vec2 pos, Vec2 traj, Vec2 atter);
        Balle(Vec2 pos, Vec2 traj, Vec2 atter, float descente);
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
        */
        void avancer_temps(float temps);

        /**
         * \brief This function performs tests on the Balle class
         * \note This function might crash the program
        */
        bool test();
};

#endif
