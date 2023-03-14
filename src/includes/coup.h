#ifndef COUP_H
#define COUP_H

#include "joueur.h"
#include "balle.h"

class Coup
{
    private : 
        Joueur & joueur;
        Balle & balle;
    
        bool peut_faire_coup();

        void faire_coup();
    public :
        
        Coup(Joueur & j, Balle &b);

        ~Coup();
};


#endif