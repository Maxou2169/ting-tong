#include "includes/score.h"

#include "assert.h"

Score::Score() : points(ZERO), avantage(false), egalite(false), jeu(0) {}

Score::Score(Points p, bool av, bool e, int j) : points(p), avantage(av), egalite(e), jeu(j) {}

Score::~Score() {}

Points Score::get_points() const
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
    assert(points == ZERO || points == QUINZE || points == TRENTE || points == QUARANTE);
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

bool Score::test()
{
    // Création d'un score nul
    Score score;
    assert(score.get_points() == ZERO);
    assert(score.get_avantage() == false);
    assert(score.get_egalite() == false);
    assert(score.get_jeu() == 0);

    // Gagner le premier point du match
    score.gagner_points();
    assert(score.get_points() == QUINZE);
    assert(score.get_avantage() == false);
    assert(score.get_egalite() == false);
    assert(score.get_jeu() == 0);

    // Modification des valeurs du score
    score.set_points(QUARANTE);
    score.set_avantage(true);
    assert(score.get_points() == QUARANTE);
    assert(score.get_avantage() == true);

    // Gagner des points
    score.gagner_points();
    assert(score.get_points() == ZERO);
    assert(score.get_avantage() == false);
    assert(score.get_jeu() == 1);

    score.set_points(QUARANTE);
    score.set_egalite(true);
    score.gagner_points();
    assert(score.get_points() == QUARANTE);
    assert(score.get_avantage() == true);
    assert(score.get_egalite() == false);

    score.set_points(QUARANTE);
    score.set_avantage(true);
    score.gagner_points();
    assert(score.get_points() == ZERO);
    assert(score.get_avantage() == false);
    assert(score.get_jeu() == 2);

    return (true);
}

