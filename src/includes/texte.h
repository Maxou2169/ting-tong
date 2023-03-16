#ifndef TEXTE_H
#define TEXTE_H

#include "joueur.h"
#include "balle.h"
#include "terrain.h"

class Texte
{
    private :
        Terrain &terrain;

    public :
        Texte(Terrain &t);

        ~Texte();

        void texte();
};

#endif