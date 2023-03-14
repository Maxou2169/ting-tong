#include "terrain.h"
#include "joueur.h"
#include "balle.h"

#include <iostream>

Terrain::Terrain(Joueur x, Joueur y, Balle b) : joueur_a(x), joueur_b(y), balle(b) {}

Terrain::~Terrain() {};

Joueur Terrain::get_joueur_a() const
{
    return this->joueur_a;
}

Joueur Terrain::get_joueur_b() const
{
    return this->joueur_b;
}

Balle Terrain::get_balle() const
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