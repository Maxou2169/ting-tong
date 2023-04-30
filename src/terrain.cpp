#include "includes/terrain.h"
#include "includes/joueur.h"
#include "includes/balle.h"

#include "assert.h"
#include <cstdlib>
#include <ctime>

#include <iostream>

using namespace std;

Terrain::Terrain(Joueur x, Joueur y, Balle b, Format f) : joueur_a(x), joueur_b(y), balle(b), format(f) {}

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

Format Terrain::get_format()
{
	return this->format;
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

void Terrain::set_format(Format f)
{
	this->format = f;
}

void Terrain::repousser()
{
	float pos_x_joueur_a = joueur_a.get_pos().get_x();
	float pos_x_joueur_b = joueur_b.get_pos().get_x();

	float pos_y_joueur_a = joueur_a.get_pos().get_y();
	float pos_y_joueur_b = joueur_b.get_pos().get_y();

	// Cas des x
	
	if(pos_x_joueur_a > BORDER_X_SIZE) // Joueur trop à droite, on le bloque à droite
	{
		repousser_x_positif(joueur_a);
	}
	
	if(pos_x_joueur_a < -BORDER_X_SIZE) // Joueur trop à gauche, on le bloque à gauche
	{
		repousser_x_negatif(joueur_a);
	}
	
	if(pos_x_joueur_b > BORDER_X_SIZE) // Joueur trop à droite, on le bloque à droite
	{
		repousser_x_positif(joueur_b);
	}
	
	if(pos_x_joueur_b < -BORDER_X_SIZE) // Joueur trop à gauche, on le bloque à gauche
	{
		repousser_x_negatif(joueur_b);
	}

	// Cas des y
	
	if(pos_y_joueur_a > BORDER_Y_SIZE) // Joueur a trop en haut, on le bloque en haut
	{
		repousser_y_positif(joueur_a);
	}
	
	if (pos_y_joueur_b < -BORDER_Y_SIZE) // Joueur b trop en bas, on le bloque en bas
	{
		repousser_y_negatif(joueur_b);
	}
	
	if(pos_y_joueur_a <= 0) // Joueur a dans la partie du joueur b, on le remet dans sa moitié de terrain
	{
		repousser_filet_joueur_a();
	}
	
	if(pos_y_joueur_b >= 0) // Joueur b dans la partie du joueur a, on le remet dans sa moitié de terrain
	{
		repousser_filet_joueur_b();
	}
	
}

void Terrain::repousser_x_positif(Joueur &j)
{
	float pos_y = j.get_pos().get_y();

	Vec2 pos(BORDER_X_SIZE , pos_y);
	j.set_pos(pos);	
}

void Terrain::repousser_x_negatif(Joueur &j)
{
	float pos_y = j.get_pos().get_y();

	Vec2 pos(-BORDER_X_SIZE , pos_y);
	j.set_pos(pos);   
}

void Terrain::repousser_y_positif(Joueur &j)
{
	float pos_x = j.get_pos().get_x();

	Vec2 pos(pos_x , BORDER_Y_SIZE);
	j.set_pos(pos);	
}

void Terrain::repousser_y_negatif(Joueur &j)
{
	float pos_x = j.get_pos().get_x();

	Vec2 pos(pos_x , -BORDER_Y_SIZE);
	j.set_pos(pos);   
}

void Terrain::repousser_filet_joueur_a()
{
	float pos_x_joueur_a = joueur_a.get_pos().get_x();
	float pos_y_joueur_a = joueur_a.get_pos().get_y();
	
	Vec2 pos(pos_x_joueur_a , pos_y_joueur_a * -1.0);
	joueur_a.set_pos(pos);
}

void Terrain::repousser_filet_joueur_b()
{
	float pos_x_joueur_b = joueur_b.get_pos().get_x();
	float pos_y_joueur_b = joueur_b.get_pos().get_y();
	
	Vec2 pos(pos_x_joueur_b , pos_y_joueur_b * -1.0);
	joueur_b.set_pos(pos);
}

bool Terrain::joueur_a_gagne_point()
{
	//float pos_balle_x = balle.get_pos().get_x();
	float pos_balle_y = balle.get_pos().get_y();

	if(pos_balle_y <= BORDER_Y_SIZE * -1.0)
	{
		int jA = joueur_a.get_score().get_jeu();
		int jB = joueur_b.get_score().get_jeu();
		int j_next = jA + 1;

		if(joueur_a.get_score().get_points() == TRENTE
		&& joueur_b.get_score().get_points() == QUARANTE) // 30-40 -> 40-40 = EGALITE
		{
			Score a(QUARANTE,false,true,jA);
			Score b(QUARANTE,false,true,jB);

			joueur_a.set_score(a);
			joueur_b.set_score(b);
		}

		else if(joueur_a.get_score().get_points() == QUARANTE
		&& joueur_a.get_score().get_avantage() == false
		&& joueur_a.get_score().get_egalite() == true
		&& joueur_b.get_score().get_points() == QUARANTE
		&& joueur_b.get_score().get_avantage() == false
		&& joueur_b.get_score().get_egalite() == true) // 40-40 -> AV-40
		{
			Score sA = Score(QUARANTE,true,false,jA);
			Score sB = Score(QUARANTE,false,false,jB);
			joueur_a.set_score(sA);
			joueur_b.set_score(sB);
		}

		else if(joueur_a.get_score().get_points() == QUARANTE
		&& joueur_a.get_score().get_avantage() == false
		&& joueur_a.get_score().get_egalite() == false
		&& joueur_b.get_score().get_points() == QUARANTE
		&& joueur_b.get_score().get_avantage() == true
		&& joueur_b.get_score().get_egalite() == false) // 40-AV -> 40-40 = EGALITE
		{
			Score sA = Score(QUARANTE,false,true,jA);
			Score sB = Score(QUARANTE,false,true,jB);

			joueur_a.set_score(sA);
			joueur_b.set_score(sB);
		}
		else
		{
			joueur_a.get_score().gagner_points();

			int j_bis = joueur_a.get_score().get_jeu();
			if(j_next == j_bis)
			{
				Score s(ZERO,false,false,joueur_b.get_score().get_jeu());
				joueur_b.set_score(s);
			}
		}		   
		return true;
	}
	else
	{
		return false;
	}
}


bool Terrain::joueur_b_gagne_point()
{
	float pos_balle_y = balle.get_pos().get_y();

	if(pos_balle_y >= BORDER_Y_SIZE)
	{
		int jA = joueur_a.get_score().get_jeu();
		int jB = joueur_b.get_score().get_jeu();
		int j_next = jB + 1;

		if(joueur_b.get_score().get_points() == TRENTE
		&& joueur_a.get_score().get_points() == QUARANTE) // 40-30 -> 40-40 = EGALITE
		{
			Score a(QUARANTE,false,true,jA);
			Score b(QUARANTE,false,true,jB);

			joueur_a.set_score(a);
			joueur_b.set_score(b);
		}

		else if(joueur_a.get_score().get_points() == QUARANTE
		&& joueur_a.get_score().get_avantage() == false
		&& joueur_a.get_score().get_egalite() == true
		&& joueur_b.get_score().get_points() == QUARANTE
		&& joueur_b.get_score().get_avantage() == false
		&& joueur_b.get_score().get_egalite() == true) // 40-40 -> 40-AV
		{
			Score sA = Score(QUARANTE,false,false,jA);
			Score sB = Score(QUARANTE,true,false,jB);
			joueur_a.set_score(sA);
			joueur_b.set_score(sB);
		}

		else if(joueur_a.get_score().get_points() == QUARANTE
		&& joueur_a.get_score().get_avantage() == true
		&& joueur_a.get_score().get_egalite() == false
		&& joueur_b.get_score().get_points() == QUARANTE
		&& joueur_b.get_score().get_avantage() == false
		&& joueur_b.get_score().get_egalite() == false) // AV-40 -> 40-40 = EGALITE
		{
			Score sA = Score(QUARANTE,false,true,jA);
			Score sB = Score(QUARANTE,false,true,jB);
			joueur_a.set_score(sA);
			joueur_b.set_score(sB);
		}
		else
		{
			joueur_b.get_score().gagner_points();

			int j_bis = joueur_b.get_score().get_jeu();
			if(j_next == j_bis)
			{
				Score s(ZERO,false,false,joueur_a.get_score().get_jeu());
				joueur_a.set_score(s);
			}
		}		   
		return true;
	}
	else
	{
		return false;
	}
}

bool Terrain::service_a_droite()
{
    Score scoreA = this->get_joueur_a().get_score();
    Score scoreB = this->get_joueur_b().get_score();

    // On utilise un switch pour gérer les différents cas de score
    switch (scoreA.get_points()) {
        case 0:
            if (scoreB.get_points() == 0 || scoreB.get_points() == 30) 
			{
                return true;
            }
            break;
        case 15:
            if (scoreB.get_points() == 15 || scoreB.get_points() == 40) 
			{
                return true;
            }
            break;
        case 30:
            if (scoreB.get_points() == 30 || scoreB.get_points() == 0) 
			{
                return true;
            }
            break;
        case 40:
            if ((scoreB.get_points() == 40 && scoreB.get_avantage() == false && scoreA.get_avantage() == false) || scoreB.get_points() == 15) 
			{
                return true;
            }
            break;
    }

    return false; // Dans tous les autres cas, on doit servir à gauche
}



void Terrain::service()
{
	if ((this->get_joueur_a().get_score().get_jeu() + this->get_joueur_b().get_score().get_jeu()) % 2)
	{ // Joueur A (en haut) doit servir
		if (service_a_droite())
		{ // Le joueur A sert à gauche, le joueur B est à droite
			Vec2 pos_a(-1.5, 13);
			this->get_joueur_a().set_pos(pos_a);
			this->get_joueur_b().set_pos(Vec2(3.0, -11));
			this->get_balle().set_pos(Vec2(
				pos_a.get_x() - 0.5,
				pos_a.get_y() - 0.2
			));
		}
		else
		{
			Vec2 pos_a(1.5, 13);
			this->get_joueur_a().set_pos(pos_a);
			this->get_joueur_b().set_pos(Vec2(-3.0, -11));
			this->get_balle().set_pos(Vec2(
				pos_a.get_x() + 0.5,
				pos_a.get_y() - 0.2
			));
		}
	}
	else 
	{ // Joueur B doit servir
		if (service_a_droite())
		{ // Le joueur A est à gauche, le joueur B sert à droite
			Vec2 pos_b(1.5, -13);
			this->get_joueur_a().set_pos(Vec2(-3.0, 11));
			this->get_joueur_b().set_pos(pos_b);
			this->get_balle().set_pos(Vec2(
				pos_b.get_x() + 0.5,
				pos_b.get_y() + 0.2
			));
		}
		else
		{
			Vec2 pos_b(-1.5, -13);
			this->get_joueur_a().set_pos(Vec2(3.0, 11));
			this->get_joueur_b().set_pos(pos_b);
			this->get_balle().set_pos(Vec2(
				pos_b.get_x() - 0.5,
				pos_b.get_y() + 0.2
			));
		}
	}
	this->get_balle().set_traj(Vec2(0,0));
	this->get_balle().set_hauteur(1);
}

void Terrain::maj_points_service()
{
	if (this->joueur_a_gagne_point() || this->joueur_b_gagne_point())
		this->service();
}

bool Terrain::test()
{
	Joueur j1("Nadal", Vec2(-6.0 , 12.0),Score());
	Joueur j2("Djokovic", Vec2(3.0 , 1.0),Score());
	
	Balle b;
	Format f;
	
	Terrain t(j1,j2,b,f);
	t.repousser();

	float new_pos_x_joueur_a = t.joueur_a.get_pos().get_x();
	float new_pos_x_joueur_b = t.joueur_b.get_pos().get_x();

	float new_pos_y_joueur_a = t.joueur_a.get_pos().get_y();
	float new_pos_y_joueur_b = t.joueur_b.get_pos().get_y();

	assert(new_pos_x_joueur_a == -5.0);
	assert(new_pos_y_joueur_a == 12.0);

	assert(new_pos_x_joueur_b == 3.0);
	assert(new_pos_y_joueur_b == -1.0);

	t.get_balle().set_pos(Vec2(-7.0,-17.0));
	assert(t.joueur_a_gagne_point() == true);
	assert(t.get_joueur_a().get_score().get_points() == QUINZE);

	Score sA(QUARANTE,true,false,0);
	Score sB(QUARANTE,false,false,0);

	t.get_joueur_a().set_score(sA);
	t.get_joueur_b().set_score(sB);

	if(t.joueur_b_gagne_point() == true)
	{
		assert(t.get_joueur_a().get_score().get_avantage() == false);
		assert(t.get_joueur_a().get_score().get_egalite() == true);

		assert(t.get_joueur_b().get_score().get_avantage() == false);
		assert(t.get_joueur_b().get_score().get_egalite() == true);
	}

	t.get_joueur_a().set_score(sB);
	t.get_joueur_b().set_score(sA);

	if(t.joueur_a_gagne_point() == true)
	{
		assert(t.get_joueur_a().get_score().get_avantage() == false);
		assert(t.get_joueur_a().get_score().get_egalite() == true);

		assert(t.get_joueur_b().get_score().get_avantage() == false);
		assert(t.get_joueur_b().get_score().get_egalite() == true);
	}
	

	return true;
}