#include "includes/coup.h"
#include "includes/joueur.h"
#include "includes/balle.h"
#include "includes/vec2.h"

#include "assert.h"

const float MAX_X = 5.0;
const float MAX_Y = 5.0;
const float COEFF_VITESSE = 1.1;

const float x = 3;
const float y = 3;
const Vec2 starting_coup_droit_bas(-x,y);
const Vec2 starting_revers_bas(x, y);
const Vec2 starting_revers_haut(-x, -y);
const Vec2 starting_coup_droit_haut(x, -y);



Coup::Coup(Joueur & j, Balle& b) : joueur(j), balle(b) 
{
    if (this->peut_faire_coup())
        this->faire_coup();
}

Coup::~Coup() {}

bool Coup::peut_faire_coup()
{
    float pos_joueur_x = joueur.get_pos().get_x();
    float pos_joueur_y = joueur.get_pos().get_y();

    float pos_balle_x = balle.get_pos().get_x();
    float pos_balle_y = balle.get_pos().get_y();

    if(
        (pos_balle_x >= pos_joueur_x - MAX_X) && 
        (pos_balle_x <= pos_joueur_x + MAX_X) && 
        (pos_balle_y >= pos_joueur_y - MAX_Y) && 
        (pos_balle_y <= pos_joueur_y + MAX_Y) &&
        (pos_balle_y > 0.0) //Vérifie que la balle n'est pas au sol
    )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Coup::faire_coup()
{
    // On assume que l'on peut faire un coup
    if (this->balle.get_pos().get_x() > this->joueur.get_pos().get_x())
        // Alors la balle est à droite, c'est un coup-droit
        this->coup_droit();
    else 
        this->revers();
}

void Coup::coup_droit()
{
    if (this->balle.get_traj() == Vec2(0,0))
    { // Service
        if (this->joueur.get_pos().get_y() > 0)
            // Alors c'est le joueur du dessus, qui sert en bas
            balle.set_traj(starting_coup_droit_haut); // Faire *-1 passe d'un joueur à l'autre
        else
            balle.set_traj(starting_coup_droit_bas); // Faire *-1 passe d'un joueur à l'autre
        return;
    }
    Vec2 symetrique_traj(this->balle.get_traj().get_x(), - this->balle.get_traj().get_y());
    symetrique_traj *= COEFF_VITESSE; // à  chaque coup, la balle va x% plus vite
    balle.set_traj(symetrique_traj);
}

void Coup::revers()
{
    if (this->balle.get_traj() == Vec2(0,0))
    { // Service
        if (this->joueur.get_pos().get_y() > 0)
            // Alors c'est le joueur du dessus, qui sert en bas
            balle.set_traj(starting_revers_haut); // Faire *-1 passe d'un joueur à l'autre
        else
            balle.set_traj(starting_revers_bas); // Faire *-1 passe d'un joueur à l'autre
        return;
    }
        
    // On laisse le reste du coup 
    Vec2 symetrique_traj(this->balle.get_traj().get_x(), - this->balle.get_traj().get_y());
    symetrique_traj *= COEFF_VITESSE;
    balle.set_traj(symetrique_traj * -1); // Car le vecteur allait toujours vers nous
}

bool Coup::test()
{
    Joueur j1("Nadal", Vec2(145.0, 205.0));
    Joueur j2("Djokovic", Vec2(250.0, 50.0));
    Balle b(Vec2(148.0, 202.0), Vec2(0.0, 0.0));

    Coup c1(j1, b);
    Coup c2(j2, b);

    // Le joueur 1 peut faire un coup
    assert(c1.peut_faire_coup());
    // Le joueur 2 ne peut pas faire de coup car la balle est trop loin
    assert(!c2.peut_faire_coup());

    // Le joueur 1 effectue son coup
    c1.faire_coup();
    assert(b.get_traj() == Vec2());

    // Le joueur 1 ne peut pas faire de coup car la balle est trop loin
    c1.faire_coup();
    assert(b.get_traj().get_x() == -296.0 && b.get_traj().get_y() == -404.0);
    return (true);
}
