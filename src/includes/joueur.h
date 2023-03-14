#ifndef JOUEUR_H
#define JOUEUR_H

#include "coup.h"
#include "vec2.h"
#include <string>

using namespace std;

class Joueur
{
    private :
        string nom;
        Vec2 pos;
        Coup coup;
    
    public :
        /**
         * \brief Initialise un joueur avec les différents paramètres
         * \param n : Nom du joueur
         * \param p : Sa position
         * \param c : Le Coup du jour 
        */

        Joueur(string n, Vec2 p, Coup c);



        ~Joueur();

        /**
         * \brief Permet d'obtenir le nom d'un joueur
        */

        string get_nom() const;

        /**
         * \brief Permet d'obtenir la postion d'un joueur
        */

        Vec2 get_pos() const;

        /**
         * \brief Permet d'obtenir le coup d'un joueur (coup droit ou revers, puissance et précision)
        */

        Coup get_coup() const;

        /**
         * \brief Permet de modifier le nom d'un joueur
         * \param n : Le nouveau nom du joueur
        */

        void set_nom(string n);

        /**
         * \brief Permet de modifier la position d'un joueur
         * \param p : Un vecteur (x,y) qui représente la nouvelle position du joueur
        */

        void set_pos(Vec2 p);

        /**
         * \brief Modifie le coup d'un joueur
         * \param c : Son nouveau coup
        */

        void set_coup(Coup c);

        /**
         * \brief Permet d'effectuer le déplacement d'un joueur vers le haut de l'écran pour le joueur en bas de l'écran
         * et inversement pour le joueur en haut de l'écran
        */

        void haut_joueur();

        /**
         * \brief Permet d'effectuer le déplacement d'un joueur vers le bas de l'écran pour le joueur en bas de l'écran
         * et inversement pour le joueur en haut de l'écran
        */

        void bas_joueur();

        /**
         * \brief Permet d'effectuer le déplacement d'un joueur vers la gauche de l'écran pour le joueur en bas de l'écran
         * et inversement pour le joueur en haut de l'écran
        */

        void gauche_joueur();

        /**
         * \brief Permet d'effectuer le déplacement d'un joueur vers la droite de l'écran pour le joueur en bas de l'écran
         * et inversement pour le joueur en haut de l'écran
        */

        void droite_joueur();
        



};

#endif