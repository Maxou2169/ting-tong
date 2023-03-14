#include "includes/joueur.h"

Joueur::Joueur(string n, Vec2 p, Coup c) : nom(n), pos(p), coup(c) {}

Joueur::~Joueur() {}

string Joueur::get_nom() const
{
    return this->nom;
}

Vec2 Joueur::get_pos() const
{
    return this->pos;
}

Coup Joueur::get_coup() const
{
    return this->coup;
}

void Joueur::set_nom(string n)
{
    this->nom=n;
}

void Joueur::set_pos(Vec2 p)
{
    this->pos=p;
}

void Joueur::set_coup(Coup c)
{
    this->coup=c;
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

