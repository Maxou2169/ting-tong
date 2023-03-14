#include "includes/balle.h"
#include "includes/vec2.h"

Balle::Balle() : pos(Vec2(0.0,0.0)), traj(Vec2(0.0,0.0)), aterrisage(Vec2(0.0,0.0)) {}
Balle::Balle(Vec2 pos, Vec2 traj, Vec2 atter) : pos(pos), traj(traj), aterrisage(atter) {}
Balle::~Balle() {}

Vec2 Balle::get_pos() const
{
    return this->pos;
}

void Balle::set_pos(Vec2 p)
{
    this->pos = p;
}

Vec2 Balle::get_traj() const 
{
    return this->traj;
}

void Balle::set_traj(Vec2 t)
{
    this->traj = t;
}

float Balle::get_hauteur() const
{
    return this->hauteur;
}

void Balle::set_hauteur(float hauteur)
{
    this->hauteur = hauteur;
}
Vec2 Balle::get_aterissage() const
{
    return this->aterrisage;
}

void Balle::calcule_aterissage()
{
    this->aterrisage = pos + traj * (this->hauteur / this->descente);
}
bool Balle::a_rebondi() const
{
    return (hauteur <= 0);
}

void Balle::avancer_temps(float t)
{
    this->pos += this->traj * t;
    this->hauteur -= this->descente * t;
}