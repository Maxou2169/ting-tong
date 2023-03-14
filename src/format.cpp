#include "includes/format.h"

Format::Format() : nb_jeux(TROIS_JEUX) {}
// TODO : Passer à un seul contructeur avec arguments par défauts
Format::Format(Jeux nb_jeux) : nb_jeux(nb_jeux) {}

Format::~Format() {}

Jeux Format::get_jeux() const
{
    return this->nb_jeux;
}

void Format::set_jeux(Jeux nb_jeux)
{
    this->nb_jeux = nb_jeux;
}
