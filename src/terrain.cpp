#include "includes/terrain.h"
#include "includes/joueur.h"
#include "includes/balle.h"

#include <iostream>

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

<<<<<<< src/terrain.cpp
bool Terrain::test()
{
    return (true);
=======
void Terrain::test()
{
    
>>>>>>> src/terrain.cpp
}