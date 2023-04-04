#include "includes/coup.h"
#include "includes/joueur.h"
#include "includes/balle.h"
#include "includes/vec2.h"
#include "includes/terrain.h"
#include "assert.h"

#include <cstdlib>
#include <ctime>

const float HITBOX_X = 5.0; //< La hitbox en coordonnées du Terrain
const float HITBOX_Y = 5.0;
const float COEFF_VITESSE = 1.1;

const float x = 3;
const float y = 3;
const Vec2 coup_droit_bas(-x,y);
const Vec2 revers_bas(x, y);
const Vec2 revers_haut(-x, -y);
const Vec2 coup_droit_haut(x, -y);

/**
 * \fn This function is a simple implementation of a python style randint
 * 
 * This function is mainly used in Coup::faire_coup()
*/
int randint(int a, int b)
{
    assert (a < b);
    return a + rand() % (b - a);
}

Coup::Coup(Joueur & j, Balle& b) : joueur(j), balle(b) 
{
    if (this->peut_faire_coup())
        this->faire_coup();
}

Coup::~Coup() {}

bool Coup::peut_faire_coup()
{
    float pos_joueur_x = this->joueur.get_pos().get_x();
    float pos_joueur_y = this->joueur.get_pos().get_y();

    float pos_balle_x = this->balle.get_pos().get_x();
    float pos_balle_y = this->balle.get_pos().get_y();

    return (
        (pos_balle_x >= pos_joueur_x - HITBOX_X) && 
        (pos_balle_x <= pos_joueur_x + HITBOX_X) && 
        (pos_balle_y >= pos_joueur_y - HITBOX_Y) && 
        (pos_balle_y <= pos_joueur_y + HITBOX_Y)
    ); // Simplifie un if (a == true) then true else false en (a)
}

void Coup::faire_coup()
{
    // On assume que l'on peut faire un coup
    float vitesse_actuelle = this->balle.get_traj().norm() == 0 ? 2 : this->balle.get_traj().norm();
    Vec2 new_traj;
    if (this->joueur.get_pos().get_y() > 0)
    { // C'est le joueur du haut
        std::cout << this->joueur.get_pos().get_y();
        if (this->balle.get_pos().get_x() > this->joueur.get_pos().get_x())
            // Alors la balle est à gauche du joueur - droite de l'écran, c'est un revers
            new_traj = Vec2(
                randint(-BORDER_X_SIZE, this->balle.get_pos().get_x()),
                randint(-BORDER_Y_SIZE, -1)
            );
        else
            new_traj = Vec2(
                randint(this->balle.get_pos().get_x(), BORDER_X_SIZE),
                randint(-BORDER_Y_SIZE, -1)
            );

    }
    else
    {
        if (this->balle.get_pos().get_x() > this->joueur.get_pos().get_x())
        {
        // Alors la balle est à droite, c'est un coup droit
            new_traj = Vec2(
                randint(-BORDER_X_SIZE, this->balle.get_pos().get_x()),
                randint(1, BORDER_Y_SIZE)
            );
        }
        else 
            new_traj = Vec2(
                randint(-BORDER_X_SIZE, this->balle.get_pos().get_x()),
                randint(1, BORDER_Y_SIZE)
            );
    }
    std::cout << std::flush;
    new_traj.normalise();
    new_traj *= vitesse_actuelle == 0 ? 3 : vitesse_actuelle *= 1.1;
    this->balle.set_traj(new_traj);
    this->balle.set_hauteur(1);
}

bool Coup::test()
{
    Joueur j1("Nadal", Vec2(0.0, 10.0), Score()); // AU dessus
    Joueur j2("Djokovic", Vec2(0.0, -10.0), Score()); // EN bas
    Balle b(Vec2(1.0, -9.0), Vec2(0.0, 0.0), 1.5); // Coup droit du joueur bas

    Coup c1(j1, b);
    // J1 est trop loin, il ne peut pas taper la balle
    assert(!c1.peut_faire_coup());
    assert(b.get_traj() == Vec2(0,0));

    Coup c2(j2, b);
    // J2 peut faire le coup et le fait
    assert(c2.peut_faire_coup());
    //assert(b.get_traj() == coup_droit_bas);
    return (true);
}
