#include "includes/terrain.h"
#include "includes/affichage.h"
#include "includes/balle.h"
#include "includes/joueur.h"
#include "includes/coup.h"

#include <chrono>
#include <SDL2/SDL.h>
#include <iostream>
#include <assert.h>

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

void Affichage::render_loop()
{
    SDL_Event events;
    bool quit = false;
    auto last_time = chrono::high_resolution_clock::now();
    while (!quit)
    {
        while (SDL_PollEvent(&events))
        { // Event loop
            if (events.type == SDL_QUIT)
                quit = true; // Si l'utilisateur a clique sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN)
            {
                const Uint8* state = SDL_GetKeyboardState(NULL);
                if (state[SDL_SCANCODE_ESCAPE])
                    quit = true;
                if (state[SDL_SCANCODE_W])
                    this->terrain.get_joueur_a().bas_joueur();
                if (state[SDL_SCANCODE_S])
                    this->terrain.get_joueur_a().haut_joueur();
                if (state[SDL_SCANCODE_A])
                    this->terrain.get_joueur_a().gauche_joueur();
                if (state[SDL_SCANCODE_D])
                    this->terrain.get_joueur_a().droite_joueur();
                if (state[SDL_SCANCODE_E])
                    Coup c(this->terrain.get_joueur_a(), this->terrain.get_balle());

                if (state[SDL_SCANCODE_O])
                    this->terrain.get_joueur_b().bas_joueur();
                if (state[SDL_SCANCODE_L])
                    this->terrain.get_joueur_b().haut_joueur();
                if (state[SDL_SCANCODE_K])
                    this->terrain.get_joueur_b().gauche_joueur();
                if (state[SDL_SCANCODE_SEMICOLON])
                    this->terrain.get_joueur_b().droite_joueur();
                if (state[SDL_SCANCODE_P])
                    Coup c(this->terrain.get_joueur_b(), this->terrain.get_balle());
            }
        }
        // Render at each frame
        SDL_SetRenderDrawColor(this->sdl_renderer, 100, 100, 100, 255);
        SDL_RenderClear(this->sdl_renderer);
        // Here we render
        SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255);

        auto now = chrono::high_resolution_clock::now();
        auto duration_between = chrono::duration_cast<chrono::microseconds>(now - last_time);
        this->terrain.get_balle().avancer_temps((double) duration_between.count() / 1000000.0);
        last_time = now; // Puts the current time into prev_frame_ts
        this->terrain.repousser();
        this->draw_balle(this->terrain.get_balle());
        this->draw_joueur(this->terrain.get_joueur_a());
        this->draw_joueur(this->terrain.get_joueur_b());

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(this->sdl_renderer);
    }
}

void Affichage::draw_joueur(const Joueur & j)
{
    /*
    SDL_Rect rect = {(int) j.get_pos().get_x(), (int) j.get_pos().get_y(), (int) j.get_pos().get_x() + 15, (int) j.get_pos().get_y() + 30};
    */
    Vec2 pos_proj = this->get_screen_coords(j.get_pos());
    SDL_Colour red = {255, 0, 0, 255};
    SDL_SetRenderDrawColor(this->sdl_renderer, 255,0,0,255);
    this->draw_circle(pos_proj.get_x(), pos_proj.get_y(), 10, red);
    //SDL_RenderDrawRect(this->sdl_renderer, &rect);
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

void Affichage::draw_balle(const Balle & b)
{
    Vec2 pos_proj = this->get_screen_coords(b.get_pos());
    SDL_Color yellow = {255,255,0, 255};
    this->draw_circle(
        pos_proj.get_x(),
        pos_proj.get_y(),
        10,
        yellow
    );
}

Vec2 Affichage::get_screen_coords(const Vec2 & v, float x_margin, float y_margin)
{
    float scale_x = (float) this->x_size / TERRAIN_X_TOTAL;
    float scale_y = (float) this->y_size / TERRAIN_Y_TOTAL;

    float origin_x = x_margin + (this->x_size - x_margin) / (float) 2;
    float origin_y = y_margin + (this->y_size - y_margin) / (float) 2;
    return Vec2(
        origin_x + (v.get_x() * scale_x),
        origin_y + (v.get_y() * scale_y)
    );
}

bool Affichage::test()
{
    Vec2 v(0,0);
    Vec2 v_proj = this->get_screen_coords(v, 0, 0);
    //assert(v_proj == Vec2(this->x_size / 2, this->y_size / 2));

    return (true);
}