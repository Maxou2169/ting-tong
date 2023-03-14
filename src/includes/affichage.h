#ifndef WINDOW_H
# define WINDOW_H

# include <SDL2/SDL.h>
# include "terrain.h"
# include "joueur.h"
/**
 * \brief La classe qui gère les différents affichages de joueurs et du terrain
*/
class Affichage
{
    private:
        SDL_Window * sdl_window;
        SDL_Renderer * sdl_renderer;

        Terrain &terrain;

        unsigned int x_size;
        unsigned int y_size;

        void sdl_init();
        void sdl_destroy();

        void draw_joueur(Joueur &j);
        void draw_balle(Balle &b);

        // Those functions are really close to the SDL and would merit a separate module in the utils/
        /**
         * \brief This function is meant to draw a circle of center (x, y) of radius radius
         * \param x : The x-coordinate of the center
         * \param y : The y-coordinate of the center
         * \param radius : The radius of the circle
         * \param color : A SDL_Color of the circle
        */
        void draw_circle(int x, int y, int radius, SDL_Color color);

    public:
        Affichage(Terrain &t, unsigned int window_size_x = 800, unsigned int window_size_y = 600);
        ~Affichage();

        void render_loop();
};

#endif