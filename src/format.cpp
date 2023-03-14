#include "includes/format.h"

#include "assert.h"

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
    assert(nb_jeux == UN_JEU || nb_jeux == TROIS_JEUX || nb_jeux == SIX_JEUX);
    this->nb_jeux = nb_jeux;
}

void Format::test()
{
    Format format;
    assert(format.get_jeux() == TROIS_JEUX);

    format.set_jeux(SIX_JEUX);
    assert(format.get_jeux() == SIX_JEUX);

    format.set_jeux(TROIS_JEUX);
    assert(format.get_jeux() == TROIS_JEUX);

    format.set_jeux(UN_JEU);
    assert(format.get_jeux() == UN_JEU);

    format.set_jeux((Jeux)3); // cast d'un entier en enum
    assert(format.get_jeux() == TROIS_JEUX);
}