#include "includes/joueur.h"

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
    this->pos.set_y(pos.get_y() + 1);
}

void Joueur::bas_joueur()
{
    this->pos.set_y(pos.get_y() - 1);
}

void Joueur::gauche_joueur()
{
    this->pos.set_x(pos.get_x() - 1);
}

void Joueur::droite_joueur()
{
    this->pos.set_x(pos.get_x() + 1);
}

