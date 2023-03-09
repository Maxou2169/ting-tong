#include "includes/format.h"

Format::Format() : un_jeu(false), trois_jeux(true), six_jeux(false) {}

Format::Format(bool un, bool trois, bool six) : un_jeu(un), trois_jeux(trois), six_jeux(six) {}

Format::~Format() {}

bool Format::get_un_jeu() const
{
    return this->un_jeu;
}

bool Format::get_trois_jeux() const
{
    return this->trois_jeux;
}

bool Format::get_six_jeux() const
{
    return this->six_jeux;
}

void Format::set_un_jeu(bool un)
{
    this->un_jeu = un;
}

void Format::set_trois_jeux(bool trois)
{
    this->trois_jeux = trois;
}

void Format::set_six_jeux(bool six)
{
    this->six_jeux = six;
}
