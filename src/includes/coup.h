#ifndef COUP_H
#define COUP_H

class Coup
{
    private : 
        bool coup_droit;
        bool revers;
        float puissance;
        float precision;

    public :
        /**
         * \brief Initialise un coup de puissance et de précision nulle
        */
        
        Coup();
        
        /**
         * \brief Initialise un coup avec les différents paramètres
         * \param c correspond à un booléen désignant le coup droit
         * \param r le revers, 
         * \param puiss un réel pour la puissance 
         * \param prec un réel pour la précision
        */

        Coup(bool c, bool r, float puis, float prec);

        /**
         * \brief Supprime un coup
        */

        ~Coup();

        /**
         * \brief Retourne le booléen correspond au coup droit
        */

        bool getCoupDroit();
        
        /**
         * \brief Retourne le booléen correspond au revers
        */

        bool getRevers();

        /**
         * \brief Retourne un réel correspondant à la puissance
        */

        float getPuissance();

        /**
         * Retourne un réel correspondant à la précision
        */

        float getPrecision();

        /**
         * \brief Modifie un coup droit
         * \param c est le nouveau coup droit
        */

        void setCoupDroit(bool c);

        /**
         * \brief Modifie un revers
         * \param r est le nouveau revers
        */

        void setRevers(bool r);

        /**
         * \brief Modifie la puissance d'un coup
         * \param p est la nouvelle puissance
        */

        void setPuissance(float p);

        /**
         * \brief Modifie la précision d'un coup
         * \param p est la nouvelle précision
        */

        void setPrecision(float p);

        /**
         * \brief Fait évoluer la puissance en fonction d'un réel p
         * \param p un réel qui est entre 0 et 1 0 étant un coup nulle et 1 étant le coup le plus fort
        */

        void AugmenterDiminuerPuissance(float p);

        /**
         * \brief Fait évoluer la précision en fonction d'un réel p
         * \param p un réel qui est entre 0 et 1 0 étant un coup d'une precision nulle et 1 étant la précision la plus forte
        */

        void AugmenterDiminuerPrecision(float p);


};


#endif