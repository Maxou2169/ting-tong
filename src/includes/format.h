#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>

class Format
{
    private :
        bool un_jeu;
        bool trois_jeux;
        bool six_jeux;

    public :

        /**
         * \brief Initalise un format de match à trois jeu
        */

        Format();

        /**
         * \brief Initalise un format de match selon les paramètres. Le true sera donc le format de match pris en compte
         * \param un : Booléen pour un match à un jeu
         * \param trois : Booléen pour un match à trois jeux
         * \param six : Booléen pour un match à six jeux
        */

        Format(bool un, bool trois, bool six);

        ~Format();

        /**
         * \brief Permet de savoir si on est dans un format de match à un jeu
        */

        bool get_un_jeu() const;

        /**
         * \brief Permet de savoir si on est dans un format de match à trois jeux
        */

        bool get_trois_jeux() const;

        /**
         * \brief Permet de savoir si on est dans un format de match à six jeux
        */

        bool get_six_jeux() const;

        /**
         * \brief Modifie le statut du format de match correspondant à un jeu
        */

        void set_un_jeu(bool un);

        /**
         * \brief Modifie le statut du format de match correspondant à trois jeux
        */

        void set_trois_jeux(bool trois);

        /**
         * \brief Modifie le statut du format de match correspondant à six jeux
        */

        void set_six_jeux(bool six);



};

#endif