#ifndef WINDOW_H
# define WINDOW_H

# include <SDL2/SDL.h>
# include <string>
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

        SDL_Texture * terrain_texture;

        SDL_Texture* logoTexture;

        Terrain &terrain;

        unsigned int x_size;
        unsigned int y_size;

        float NET_HEIGHT = 0.914f;

        void sdl_init(std::string terrain_path);
        void sdl_destroy();

        /**
         * \brief This function takes a Joueur and draws it on the SDL_Window
         * \param j : The Joueur to draw
         * 
         * \note Les coordonnées du joueur sont en unités du terrain
        */
        void draw_joueur(const Joueur & j);

        /**
         * \brief This function takes a Balle and draws it on the SDL_Window
         * \param b : The Balle to draw
         * 
         * \note Les coordonnées du joueur sont en unités du terrain
        */
        void draw_balle(const Balle & b);

        /**
         * \brief This displays the terrain texture
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
         * \brief This function is meant to draw a circle of center (x, y) of radius radius
         * \param x : The x-coordinate of the center
         * \param y : The y-coordinate of the center
         * \param radius : The radius of the circle
         * \param color : A SDL_Color of the circle
         * 
         * \note If there was multiple functions of this kind, we might want to switch them to a utils module
        */
        void draw_circle(int x, int y, int radius, SDL_Color color);

        void affichage_menu();
        /**
         * \brief This function draws inside the SDL Window and handles the events
         * \note This function is "blocking"
        */
        void affichage_jeu();
        void affichage_vainqueur();

    public:
        Affichage(Terrain &t, 
            unsigned int window_size_x = 800, 
            unsigned int window_size_y = 600, 
            std::string terrain_texture = "data/terrain_RG.png"
        );
        ~Affichage();

        void affichage();

        /**
         * \brief Effectue des tests des différentes fonctions
        */
        bool test();
};

#endif