#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include "joueur.h"
#include "balle.h"

/**
 * \brief Une classe Terrain qui possède deux joueurs et une balle
*/

class Terrain
{
    private :
        Joueur joueur_a;
        Joueur joueur_b;
        Balle balle;
    
    public:

    /**
     * \brief Initialise un terrain avec deux joueur et une balle
     * \param x : Le joueur 1
     * \param y : Le joueur 2
     * \param b : La balle
    */
        Terrain(Joueur x, Joueur y, Balle b);

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
         * \brief Effectue un test des différentes fonctions membres de la classe
        */

        void test();




};


#endif
