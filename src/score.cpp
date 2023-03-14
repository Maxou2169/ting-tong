#include "includes/score.h"

Score::Score() : points(ZERO), avantage(false), egalite(false), jeu(0) {}

Score::Score(Points p, bool av, bool e, int j) : points(p), avantage(av), egalite(e), jeu(j) {}

Score::~Score() {}

Score::Points Score::get_points() const
{
    return this->points;
}


bool Score::get_avantage() const
{
    return this->avantage;
}

bool Score::get_egalite() const
{
    return this->egalite;
}

int Score::get_jeu() const
{
    return this->jeu;
}

void Score::set_points(Points p)
{
    this->points = p;
}

void Score::set_avantage(bool av)
{
    this->avantage = av;
}

void Score::set_egalite(bool e)
{
    this->egalite = e;
}

void Score::set_jeu(int j)
{
    this->jeu = j;
}

void Score::gagner_points()
{
    switch(this->points)
    {
        case ZERO :
            this->points = QUINZE;
            break;
        case QUINZE :
            this->points = TRENTE;
            break;
        case TRENTE :
            this->points = QUARANTE;
            break;
        case QUARANTE :
            if(this->egalite == true) // 40-40 -> AV-40
            {
                this->avantage = true;
                this->egalite = false;
            }
            else if(avantage == true) // AV - 40 -> 0 - 0, jeu +1
            {
                this->points = ZERO;
                this->jeu++;
                this->avantage = false;
            }
            break;
    }
}
