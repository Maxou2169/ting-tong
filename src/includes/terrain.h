#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include "joueur.h"
#include "balle.h"

class Terrain
{
    private :
        Joueur joueur_a;
        Joueur joueur_b;
        Balle balle;
    
    public:
        Terrain(Joueur x, Joueur y, Balle b);

        ~Terrain();

        Joueur get_joueur_a() const;

        Joueur get_joueur_b() const;

        Balle get_balle() const;

        void set_joueur_a(Joueur j);

        void set_joueur_b(Joueur j);

        void set_balle(Balle b);




};


#endif