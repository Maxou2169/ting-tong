#include "includes/texte.h"
#include "includes/joueur.h"
#include "includes/balle.h"
#include "includes/terrain.h"
#include "includes/coup.h"

#include <iostream>
using namespace std;

Texte::Texte(Terrain &t): terrain(t) {}

Texte::~Texte() {}

void Texte::texte()
{
	char a;
	char b;
	bool quit = false;
	while(!quit)
	{
		cout<<"La position du joueur "<<this->terrain.get_joueur_a().get_nom()<<" est la suivante : ("
			<<this->terrain.get_joueur_a().get_pos().get_x()
			<<","<<this->terrain.get_joueur_a().get_pos().get_y()<<")"<<endl;

		cout<<"La position du joueur "<<this->terrain.get_joueur_b().get_nom()<<" est la suivante : ("
			<<this->terrain.get_joueur_b().get_pos().get_x()
			<<","<<this->terrain.get_joueur_b().get_pos().get_y()<<")"<<endl;
		
		cout << "La balle est à la position (" << this->terrain.get_balle().get_pos().get_x() << "," <<
			this->terrain.get_balle().get_pos().get_y() << ")" << endl;

		cout<<"Si vous voulez changer la position du joueur "<< this->terrain.get_joueur_a().get_nom()
			<<" veuillez suivre les instructions suivantes : "<<endl;
		cout<<"Pour faire bouger le joueur vers le haut, appuyez sur la touche z"<<endl;
		cout<<"Pour faire bouger le joueur vers le bas, appuyez sur la touche s"<<endl;
		cout<<"Pour faire bouger le joueur vers la gauche, appuyez sur la touche q"<<endl;
		cout<<"Pour faire bouger le joueur vers la droite, appuyez sur la touche d"<<endl;
		cout<<"Pour taper la balle, appuyez sur la touche e"<<endl;
		cout<<"Pour quitter l'animation, veuillez cliquer sur t, appuyez ailleurs pour ne rien faire"<<endl << "Quelle action?" << endl;
		
		cin >> a;

		cout<<"Si vous voulez changer la position du joueur "<< this->terrain.get_joueur_b().get_nom()
			<<" veuillez suivre les instructions suivantes : "<<endl;
		cout<<"Pour faire bouger le joueur vers le haut, appuyez sur la touche o"<<endl;
		cout<<"Pour faire bouger le joueur vers le bas, appuyez sur la touche l"<<endl;
		cout<<"Pour faire bouger le joueur vers la gauche, appuyez sur la touche k"<<endl;
		cout<<"Pour faire bouger le joueur vers la droite, appuyez sur la touche m"<<endl;
		cout<<"Pour taper la balle, appuyez sur la touche p"<<endl;
		cout<<"Pour quitter l'animation, veuillez cliquer sur t, appuyez ailleurs pour ne rien faire"<<endl << "Quelle action?" << endl;
		cin>>b;

		switch(a)
		{
			case 't' :
				quit = true;
				break;
			case 'z':
				this->terrain.get_joueur_a().haut_joueur();
				break;
			case 's':
				this->terrain.get_joueur_a().bas_joueur();
				break;
			case 'q':
				this->terrain.get_joueur_a().gauche_joueur();
				break;
			case 'd':
				this->terrain.get_joueur_a().droite_joueur();
				break;
			case 'e':
			{ // On doit utiliser un bloc car c "remonterait" dans les autres blocs car switch est bizarre
			// Le bloc limite la portée de la variable au bloc, et ne "contamine" pas le reste du switch
				Coup c = Coup(this->terrain.get_joueur_a(), this->terrain.get_balle());
				break;
			}
			default: break;
		}
		switch(b)
		{
			case 't' :
				quit = true;
				break;
			case 'o':
				this->terrain.get_joueur_b().haut_joueur();
				break;
			case 'l':
				this->terrain.get_joueur_b().bas_joueur();
				break;
			case 'k':
				this->terrain.get_joueur_b().gauche_joueur();
				break;
			case 'm':
				this->terrain.get_joueur_b().droite_joueur();
				break;
			case 'p':
			{
				Coup c(this->terrain.get_joueur_b(), this->terrain.get_balle());
				break;
			}
			default: break;
		}
		this->terrain.get_balle().avancer_temps(1.0);
	}
}