#include "includes/balle.h"
#include "includes/vec2.h"
#include <assert.h>

Balle::Balle() : pos(Vec2(0,0)), traj(Vec2(0,0)) {}
Balle::Balle(Vec2 pos, Vec2 traj) : pos(pos), traj(traj) {}
Balle::Balle(Vec2 pos, Vec2 traj, float descente) : pos(pos), traj(traj), descente(descente) {}
Balle::Balle(Vec2 pos, Vec2 traj, Vec2 atter) : pos(pos), traj(traj), aterrisage(atter) {}
Balle::Balle(Vec2 pos, Vec2 traj, Vec2 atter, float descente)
: pos(pos), traj(traj), aterrisage(atter), descente(descente) {}

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
#include <iostream>

using namespace std;

bool Balle::test(void)
{
	Balle b = Balle(); // Constructeur vide
	assert(b.get_pos().get_x() == 0 && b.get_pos().get_y() == 0);
	assert(b.get_traj().get_x() == 0 && b.get_traj().get_y() == 0);

	b.calcule_aterissage();
	assert(b.get_aterissage().get_x() == 0.0 && b.get_aterissage().get_y() == 0.0);

	b.set_traj(Vec2(1,2));
	b.calcule_aterissage();
	assert(b.get_aterissage().get_x() == 10 && b.get_aterissage().get_y() == 20);

	b.avancer_temps(3);
	assert(b.get_pos().get_x() == 3 && b.get_pos().get_y() == 6);

	return (true);
}
