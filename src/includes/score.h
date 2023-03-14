#ifndef SCORE_H
#define SCORE_H

#include <iostream>

typedef enum Points 
{
    ZERO = 0,
    QUINZE = 15,
    TRENTE = 30, 
    QUARANTE = 40
} Points;

class Score
{
    private : 
        Points points;
        bool avantage;
        bool egalite; // une égalité est défini quand il y a 40 - 40
        int jeu;

    public :

    /**
     * \brief Créer un score nul
    */

    Score(); 

    /**
     * \brief Créer un score selon les paramètres
     * \param p : Les points
     * \param av : Le cas où il y a un avantage
     * \param e : Le cas où il y a une égalité
     * \param j : Les jeux
    */

    Score(Points p, bool av, bool e, int j);

    ~Score();

    /**
     * \brief Permet d'obtenir les points d'un score
    */

    Points get_points() const;

    /**
     * \brief Permet de savoir s'il y a avantage ou non
    */

    bool get_avantage() const;

    /**
     * \brief Permet de savoir s'il y a une égalité
    */

    bool get_egalite() const;

    /**
     * \brief Permet d'obtenir le nombre de jeu d'un score
    */

    int get_jeu() const;

    /**
     * \brief Modifie le point d'un score
     * \param p : Nouveau point
    */

    void set_points(Points p);

    /**
     * \brief Modifie le statut d'avantage
     * \param av : Nouveau statut d'avantage
    */

    void set_avantage(bool av);

    /**
     * \brief Modifie le statue d'égalité
     * \param e: Nouveau statut d'égalité
    */

    void set_egalite(bool e);

    /**
     * \brief Modifie le nombre de jeu
     * \param j : Le nouveau nombre de jeu
    */

    void set_jeu(int j);

    /**
     * \brief Fait gagner un point au score d'un joueur
     * \param p : Le score du joueur avant qu'il gagne le point
    */

    void gagner_points(Points p);
};

#endif
