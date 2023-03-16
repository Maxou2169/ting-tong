#include "includes/coup.h"
#include "includes/joueur.h"
#include "includes/balle.h"
#include "includes/vec2.h"

#include "assert.h"

const float MAX_X = 5.0;
const float MAX_Y = 5.0;


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
        (pos_balle_x > pos_joueur_x - MAX_X) && 
        (pos_balle_x < pos_joueur_x + MAX_X) && 
        (pos_balle_y > pos_joueur_y - MAX_Y) && 
        (pos_balle_y < pos_joueur_y + MAX_Y) &&
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
    // Calculer la position opposée de la balle
    float pos_balle_x = balle.get_pos().get_x();
    float pos_balle_y = balle.get_pos().get_y();
    Vec2 pos_opposee(-pos_balle_x, -pos_balle_y);
    // Modifier la trajectoire de la balle pour qu'elle se dirige vers la position opposée
    Vec2 nouvelle_traj = pos_opposee - balle.get_pos();
    balle.set_traj(nouvelle_traj);
}

void Coup::test()
{
    Joueur j1("Nadal", Vec2(145.0, 205.0));
    Joueur j2("Djokovic", Vec2(250.0, 50.0));
    Balle b(Vec2(150.0, 200.0), Vec2(0.0, 0.0), Vec2(0.0, 0.0));

    Coup c1(j1, b);
    Coup c2(j2, b);

    // Le joueur 1 peut faire un coup
    assert(c1.peut_faire_coup());
    // Le joueur 2 ne peut pas faire de coup car la balle est trop loin
    assert(!c2.peut_faire_coup());

    // Le joueur 1 effectue son coup
    c1.faire_coup();
    assert(b.get_pos().get_x() == -145.0 && b.get_pos().get_y() == -205.0);

    // Le joueur 1 ne peut pas faire de coup car la balle est trop loin
    c1.faire_coup();
    assert(b.get_pos().get_x() == -145.0 && b.get_pos().get_y() == -205.0);
}
