#ifndef COUP_H
#define COUP_H

#include "joueur.h"
#include "balle.h"

/**
 * \brief La classe coup correspond au coup d'un joueur, que ce soit un coup droit ou un revers
*/

class Coup
{
    private : 
        Joueur & joueur;
        Balle & balle;

        /**
         * \brief Vérifie si le joueur peut effectuer son coup ou non
        */
    
        bool peut_faire_coup();

        /**
         * \brief Si le joueur peut faire un coup alors la fonction lui permet de le faire
        */

        void faire_coup();

        /**
         * \brief Initialise un coup
         * \param j : Un joueur
         * \param b : Une balle
        */
    public :
        
        Coup(Joueur & j, Balle &b);

        ~Coup();
};


#endif