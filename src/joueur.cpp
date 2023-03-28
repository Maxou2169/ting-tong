#include "includes/joueur.h"

#include "assert.h"

# define EPSILON 0.0001

Joueur::Joueur(string n, Vec2 p) : nom(n), pos(p) {}

Joueur::~Joueur() {}

string Joueur::get_nom() const
{
    return this->nom;
}

Vec2 Joueur::get_pos() const
{
    return this->pos;
}

void Joueur::set_nom(string n)
{
    this->nom=n;
}

void Joueur::set_pos(Vec2 p)
{
    this->pos=p;
}

void Joueur::haut_joueur()
{
    this->pos.set_y(pos.get_y() + 0.1);
}

void Joueur::bas_joueur()
{
    this->pos.set_y(pos.get_y() - 0.1);
}

void Joueur::gauche_joueur()
{
    this->pos.set_x(pos.get_x() - 0.1);
}

void Joueur::droite_joueur()
{
    this->pos.set_x(pos.get_x() + 0.1);
}

bool Joueur::test()
{
    Joueur j("Nadal", Vec2(50.0,50.0));
    float j_pos_x = j.get_pos().get_x();
    float j_pos_y = j.get_pos().get_y();
    
    assert(j.get_nom() == "Nadal");
    assert(j_pos_x == 50.0 && j_pos_y == 50.0);

    j.haut_joueur();
    assert((j.get_pos().get_y() - 50.1) < EPSILON);

    j.bas_joueur();
    assert((j.get_pos().get_y() - 50.0) < EPSILON);

    j.droite_joueur();
    assert((j.get_pos().get_x() - 50.1) < EPSILON);

    j.gauche_joueur();
    assert((j.get_pos().get_x() - 50) < EPSILON);

    j.set_pos(Vec2(25.0,25.0));
    assert(j.get_pos().get_x() == 25.0 && j.get_pos().get_y() == 25.0);
    return (true);
}