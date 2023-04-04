#include "includes/terrain.h"
#include "includes/joueur.h"
#include "includes/balle.h"

#include "assert.h"
#include <cstdlib>
#include <ctime>

#include <iostream>

using namespace std;

Terrain::Terrain(Joueur x, Joueur y, Balle b) : joueur_a(x), joueur_b(y), balle(b) {}

Terrain::~Terrain() {};

Joueur& Terrain::get_joueur_a()
{
    return this->joueur_a;
}

Joueur& Terrain::get_joueur_b()
{
    return this->joueur_b;
}

Balle& Terrain::get_balle()
{
    return this->balle;
}

void Terrain::set_joueur_a(Joueur j)
{
    this->joueur_a = j;
}

void Terrain::set_joueur_b(Joueur j)
{
    this->joueur_b = j;
}

void Terrain::set_balle(Balle b)
{
    this->balle = b;
}

void Terrain::repousser()
{
    float pos_x_joueur_a = joueur_a.get_pos().get_x();
    float pos_x_joueur_b = joueur_b.get_pos().get_x();

    float pos_y_joueur_a = joueur_a.get_pos().get_y();
    float pos_y_joueur_b = joueur_b.get_pos().get_y();

    // Cas des x
    
    if(pos_x_joueur_a > BORDER_X_SIZE) // Joueur trop à droite, on le bloque à droite
    {
        repousser_x_positif(joueur_a);
    }
    
    if(pos_x_joueur_a < -BORDER_X_SIZE) // Joueur trop à gauche, on le bloque à gauche
    {
        repousser_x_negatif(joueur_a);
    }
    
    if(pos_x_joueur_b > BORDER_X_SIZE) // Joueur trop à droite, on le bloque à droite
    {
        repousser_x_positif(joueur_b);
    }
    
    if(pos_x_joueur_b < -BORDER_X_SIZE) // Joueur trop à gauche, on le bloque à gauche
    {
        repousser_x_negatif(joueur_b);
    }

    // Cas des y
    
    if(pos_y_joueur_a > BORDER_Y_SIZE) // Joueur a trop en haut, on le bloque en haut
    {
        repousser_y_positif(joueur_a);
    }
    
    if (pos_y_joueur_b < -BORDER_Y_SIZE) // Joueur b trop en bas, on le bloque en bas
    {
        repousser_y_negatif(joueur_b);
    }
    
    if(pos_y_joueur_a <= 0) // Joueur a dans la partie du joueur b, on le remet dans sa moitié de terrain
    {
        repousser_filet_joueur_a();
    }
    
    if(pos_y_joueur_b >= 0) // Joueur b dans la partie du joueur a, on le remet dans sa moitié de terrain
    {
        repousser_filet_joueur_b();
    }
    
}

void Terrain::repousser_x_positif(Joueur &j)
{
    float pos_y = j.get_pos().get_y();

    Vec2 pos(BORDER_X_SIZE , pos_y);
    j.set_pos(pos);    
}

void Terrain::repousser_x_negatif(Joueur &j)
{
    float pos_y = j.get_pos().get_y();

    Vec2 pos(-BORDER_X_SIZE , pos_y);
    j.set_pos(pos);   
}

void Terrain::repousser_y_positif(Joueur &j)
{
    float pos_x = j.get_pos().get_x();

    Vec2 pos(pos_x , BORDER_Y_SIZE);
    j.set_pos(pos);    
}

void Terrain::repousser_y_negatif(Joueur &j)
{
    float pos_x = j.get_pos().get_x();

    Vec2 pos(pos_x , -BORDER_Y_SIZE);
    j.set_pos(pos);   
}

void Terrain::repousser_filet_joueur_a()
{
    float pos_x_joueur_a = joueur_a.get_pos().get_x();
    float pos_y_joueur_a = joueur_a.get_pos().get_y();
    
    Vec2 pos(pos_x_joueur_a , pos_y_joueur_a * -1.0);
    joueur_a.set_pos(pos);
}

void Terrain::repousser_filet_joueur_b()
{
    float pos_x_joueur_b = joueur_b.get_pos().get_x();
    float pos_y_joueur_b = joueur_b.get_pos().get_y();
    
    Vec2 pos(pos_x_joueur_b , pos_y_joueur_b * -1.0);
    joueur_b.set_pos(pos);
}

bool Terrain::joueur_a_gagne_point()
{
    //float pos_balle_x = balle.get_pos().get_x();
    float pos_balle_y = balle.get_pos().get_y();

    if(pos_balle_y <= BORDER_Y_SIZE * -1.0)
    {
        joueur_a.get_score().gagner_points();
        return true;
    }
    else
    {
        return false;
    }
}

bool Terrain::joueur_b_gagne_point()
{
    //float pos_balle_x = balle.get_pos().get_x();
    float pos_balle_y = balle.get_pos().get_y();

    if(pos_balle_y >= BORDER_Y_SIZE)
    {
        this->joueur_b.get_score().gagner_points();
        return true;
    }
    else
    {
        return false;
    }
}

void Terrain::service()
{
    if ((this->get_joueur_a().get_score().get_jeu() + this->get_joueur_b().get_score().get_jeu()) % 2)
    { // Joueur A (en haut) doit servir
        if (rand() % 2)
        { // Le joueur A sert à gauche, le joueur B est à droite
            Vec2 pos_a(-2.5, 8);
            this->get_joueur_a().set_pos(pos_a);
            this->get_joueur_b().set_pos(Vec2(2.5, -8));
            this->get_balle().set_pos(Vec2(
                pos_a.get_x() - 0.2,
                pos_a.get_y() - 0.2
            ));
        }
        else
        {
            Vec2 pos_a(2.5, 8);
            this->get_joueur_a().set_pos(pos_a);
            this->get_joueur_b().set_pos(Vec2(-2.5, -8));
            this->get_balle().set_pos(Vec2(
                pos_a.get_x() + 0.2,
                pos_a.get_y() - 0.2
            ));
        }
    }
    else 
    { // Joueur B doit servir
        if (rand() % 2)
        { // Le joueur A est à gauche, le joueur B sert à droite
            Vec2 pos_b(2.5, -8);
            this->get_joueur_a().set_pos(Vec2(-2.5, 8));
            this->get_joueur_b().set_pos(pos_b);
            this->get_balle().set_pos(Vec2(
                pos_b.get_x() + 0.2,
                pos_b.get_y() + 0.2
            ));
        }
        else
        {
            Vec2 pos_b(-2.5, -8);
            this->get_joueur_a().set_pos(Vec2(2.5, 8));
            this->get_joueur_b().set_pos(pos_b);
            this->get_balle().set_pos(Vec2(
                pos_b.get_x() - 0.2,
                pos_b.get_y() + 0.2
            ));
        }
    }
    this->get_balle().set_traj(Vec2(0,0));
    this->get_balle().set_hauteur(1);
}

void Terrain::maj_points_service()
{
    if (this->joueur_a_gagne_point() || this->joueur_b_gagne_point())
    {
        this->service();
    }
}

bool Terrain::test()
{
    Joueur j1("Nadal", Vec2(-6.0 , 12.0),Score());
    Joueur j2("Djokovic", Vec2(3.0 , 1.0),Score());
    
    Balle b;
    
    Terrain t(j1,j2,b);
    t.repousser();

    float new_pos_x_joueur_a = t.joueur_a.get_pos().get_x();
    float new_pos_x_joueur_b = t.joueur_b.get_pos().get_x();

    float new_pos_y_joueur_a = t.joueur_a.get_pos().get_y();
    float new_pos_y_joueur_b = t.joueur_b.get_pos().get_y();

    assert(new_pos_x_joueur_a == -5.0);
    assert(new_pos_y_joueur_a == 12.0);

    assert(new_pos_x_joueur_b == 3.0);
    assert(new_pos_y_joueur_b == -1.0);

    t.get_balle().set_pos(Vec2(-7.0,-17.0));
    assert(t.joueur_a_gagne_point() == true);
    assert(t.get_joueur_a().get_score().get_points() == QUINZE);

    return true;
}