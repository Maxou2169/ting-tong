#include "includes/coup.h"

Coup::Coup() : coup_droit(false), revers(false), puissance(0.0), precision(0.0) {}

Coup::Coup(bool c, bool r, float puis, float prec) :
    coup_droit(coup_droit), revers(revers), puissance(puis), precision(prec) {}

Coup::~Coup() {}

bool Coup::getCoupDroit() const
{
    return this->coup_droit;
}

bool Coup::getRevers() const
{
    return this->revers;
}

float Coup::getPuissance() const
{
    return this->puissance;
}

float Coup::getPrecision() const
{
    return this->precision;
}

void Coup::setCoupDroit(bool c)
{
    this->coup_droit = c;
}

void Coup::setRevers(bool r)
{
    this->revers = r;
}

void Coup::setPuissance(float p)
{
    this->puissance = p;
}

void Coup::setPrecision(float p)
{
    this->precision = p;
}

void Coup::AugmenterDiminuerPuissance(float p)
{
    this->puissance *= p;
}

void Coup::AugmenterDiminuerPrecision(float p)
{
    this->precision *= p;
}
