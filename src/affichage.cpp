#include "includes/terrain.h"
#include "includes/affichage.h"
#include "includes/balle.h"
#include "includes/joueur.h"

#include <SDL2/SDL.h>
#include <iostream>

Affichage::Affichage(Terrain &t, unsigned int x, unsigned int y)
    : terrain(t), x_size(x), y_size(y)
{
    this->sdl_init();
}

Affichage::~Affichage()
{
    this->sdl_destroy();
}

using namespace std;

void Affichage::sdl_init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "Error while initialising the SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    this->sdl_window = SDL_CreateWindow("Ting Tong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->x_size, this->y_size, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (this->sdl_window == NULL)
    {
        cerr << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1, SDL_RENDERER_ACCELERATED);
}

void Affichage::sdl_destroy()
{
    SDL_DestroyRenderer(this->sdl_renderer);
    SDL_DestroyWindow(this->sdl_window);
    SDL_Quit();
}

#include <iostream>

void Affichage::render_loop()
{
    SDL_Event events;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&events))
        { // Event loop
            if (events.type == SDL_QUIT)
                quit = true; // Si l'utilisateur a clique sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN)
            {
                switch (SDL_GetKeyFromScancode(events.key.keysym.scancode)) // Beacause Scancode are "physical" and mapped to qwerty, Keycode is mapping-dependant
                {
                    case SDLK_z:
                        this->terrain.get_joueur_a().haut_joueur();
                        break;
                    case SDLK_s:
                        this->terrain.get_joueur_a().bas_joueur();
                        break;
                    case SDLK_q:
                        this->terrain.get_joueur_a().gauche_joueur();
                        break;
                    case SDLK_d:
                        this->terrain.get_joueur_a().droite_joueur();
                        break;
                    case SDLK_UP:
                        this->terrain.get_joueur_b().haut_joueur();
                        break;
                    case SDLK_DOWN:
                        this->terrain.get_joueur_b().bas_joueur();
                        break;
                    case SDLK_LEFT:
                        this->terrain.get_joueur_b().gauche_joueur();
                        break;
                    case SDLK_RIGHT:
                        this->terrain.get_joueur_b().droite_joueur();
                        break;                      
                    default: break;
                }
                
            }
        }
        // Render at each frame
        SDL_SetRenderDrawColor(this->sdl_renderer, 100, 100, 100, 255);
        SDL_RenderClear(this->sdl_renderer);
        // Here we render
        SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255);

        this->draw_balle(this->terrain.get_balle());
        this->draw_joueur(this->terrain.get_joueur_a());
        this->draw_joueur(this->terrain.get_joueur_b());

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(this->sdl_renderer);
    }
}

void Affichage::draw_joueur(Joueur & j)
{
    SDL_Rect rect = {(int) j.get_pos().get_x(), (int) j.get_pos().get_y(), (int) j.get_pos().get_x() + 15, (int) j.get_pos().get_y() + 30};
    SDL_SetRenderDrawColor(this->sdl_renderer, 255,0,0,255);
    SDL_RenderDrawRect(this->sdl_renderer, &rect);
}

void Affichage::draw_circle(int x, int y, int radius, SDL_Color color)
{
    SDL_Renderer* renderer = this->sdl_renderer;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void Affichage::draw_balle(Balle & b)
{
    SDL_Color yellow = {255,255,0, 255};
    this->draw_circle(
        b.get_pos().get_x(),
        b.get_pos().get_y(),
        10,
        yellow
    );
}