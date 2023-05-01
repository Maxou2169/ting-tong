#ifndef AFFICHAGE_H
# define AFFICHAGE_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <string>
# include <map>
# include "terrain.h"
# include "joueur.h"

const float TERRAIN_X_TOTAL = 2.0* BORDER_X_SIZE;
const float TERRAIN_Y_TOTAL = 2.0* BORDER_Y_SIZE;

/**
 * \brief La classe qui gère les différents affichages de joueurs et du terrain
*/
class Affichage
{
	private:
		SDL_Window * sdl_window;
		SDL_Renderer * sdl_renderer;

		SDL_Texture * terrain_texture = nullptr;
		SDL_Texture* logo_texture = nullptr;
		SDL_Texture* j1_texture = nullptr;
		SDL_Texture* j2_texture = nullptr;

		TTF_Font * game_font;

		Terrain &terrain;

		// Une map nom => path vers image
		std::map<std::string, std::string> joueurs_config;
		// Une map nom => paire de path (terrain, logo)
		std::map<std::string, std::pair<std::string, std::string>> terrains_config;
		unsigned int x_size; /**< La largeur de la fenêtre*/
		unsigned int y_size; /**< La hauteur de la fenêtre*/

		float NET_HEIGHT = 0.914f;

		void sdl_init();
		void sdl_init_terrain_logo(std::string terrain_path, std::string logo_path);
		void sdl_init_players(std::string j1_path, std::string j2_path);
		void sdl_destroy();

		/**
		 * \brief Loads the config files to create the menus
		*/
		void load_config();

		/**
		 * \brief La fonction prends un joueur et le dessine dans la fenêtre
		 * \param j : Le joueur a dessiner
		 * 
		 * \note Les coordonnées du joueur sont en unités du terrain
		*/
		void draw_joueur(const Joueur & j);

		/**
		 * \brief La fonction prends une balle et la dessine dans la fenêtre
		 * \param b : La balle a dessiner
		 * 
		 * \note Les coordonnées du joueur sont en unités du terrain
		*/
		void draw_balle(const Balle & b);

		/**
		 * \brief Dessine le terrain
		*/
		void draw_terrain();

		/**
		 * \brief Affiche le score des joueurs dans un tableau
		*/
		void draw_score();

		/**
		 * \brief Cette fonction traduit des coordonnées du terrain en des coordonnées-écran
		 * \param v : Les coordonnées à traduire
		 * \param x_margin : L'espace total à laisser sur l'axe x autour du terrain
		 * \param y_margin : L'espace total à laisser sur l'axe y autour du terrain
		 * 
		 * \note Effectue un scale et une inversion (repère jeu orthonormé, SDL inverse en y)
		*/
		Vec2 get_screen_coords(const Vec2 & v, float x_margin = 0, float y_margin = 0);

		/**
		 * \brief Cette fonction est destinée à dessiner un cercle de centre (x, y) de rayon radius
		 * \param x : La coordonnée x du centre
		 * \param y : La coordonnée y du centre
		 * \param radius : Le rayon du cercle
		 * \param color : Le rayon du cercle
		 * 
		 * \note Si plusieurs fonctions de ce type existaient, il serait peut-être préférable de les déplacer dans un module utilitaire
		*/
		void draw_circle(int x, int y, int radius, SDL_Color color);
		
		/**
		 * \brief Change le terrain en fonction du choix effectué dans le menu
		 * \param terrain_path : Le nom du terrain choisit par l'utilisateur
		*/
		void cb_change_terrain(std::string terrain_path);

		/**
		 * \brief Change le format en fonction du choix effectué dans le menu
		 * \param nb_jeux : Le format choisit par l'utilisateur
		*/
		void cb_change_format(std::string nb_jeux);

		/**
		 * \brief Change le joueur 1 en fonction du choix effectué dans le menu
		 * \param nom_joueur : Le nom du joueur choisi par l'utilisateur
		 * \param num_joueur : Le numéro du joueur concerné (1 ou 2)
		 * \note Comportement non garanti si num_joueur != 1 OU 2
		*/
		void cb_change_joueur(std::string nom_joueur, int num_joueur);
		
		/**
		 * \brief Affichage du menu pour le choix du terrain
		*/
		void sous_affichage_menu_terrain();
		
		/**
		 * \brief Affichage du menu pour le choix du format
		*/
		void sous_affichage_menu_jeux();

		/**
		 * \brief Affichage des menus pour choisir le joueur 1 et 2
		*/
		void sous_affichage_menu_joueur();

		/**
		 * \brief Affiche l'entièreté des menus
		*/
		void affichage_menu();
		
		/**
		 * \brief Affiche le match
		*/
		void affichage_jeu();

		/**
		 * \brief Affiche le vainqueur du match
		*/
		void affichage_vainqueur();

	public:

		/**
		 * \brief Constructeur de la classe terrain
		 * \param window_size_x : Largeur de la fenêtre
		 * \param window_size_y : Hauteur de la fenêtre
		*/
		Affichage(
			Terrain &t, 
			unsigned int window_size_x = 800, 
			unsigned int window_size_y = 600 
		);

		/**
		 * \brief Destructeur de la classe Affichage
		*/
		~Affichage();

		/**
		 * \brief Affiche les elements du jeu
		*/
		void affichage();

		/**
		 * \brief Effectue des tests des différentes fonctions
		*/
		bool test();



};

#endif