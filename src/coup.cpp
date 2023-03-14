#include "includes/coup.h"
#include "includes/joueur.h"
#include "includes/balle.h"
#include "includes/vec2.h"

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
        (pos_balle_y < pos_joueur_y + MAX_Y)
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
