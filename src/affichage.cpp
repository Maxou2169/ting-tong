#include "includes/terrain.h"
#include "includes/affichage.h"
#include "includes/balle.h"
#include "includes/joueur.h"
#include "includes/coup.h"

#include <chrono>
#include <SDL2/SDL.h>	
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <assert.h>
#include <string>

Affichage::Affichage(Terrain &t, unsigned int x, unsigned int y, std::string terrain_texture)
    : terrain(t), x_size(x), y_size(y)
{
    this->sdl_init(terrain_texture);
}

Affichage::~Affichage()
{
    this->sdl_destroy();
}

using namespace std;

void Affichage::sdl_init(std::string terrain_path)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "Error while initialising the SDL : " << SDL_GetError() << endl;
        SDL_Quit();exit(1);
    }

    this->sdl_window = SDL_CreateWindow("Ting Tong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->x_size, this->y_size, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (this->sdl_window == NULL)
    {
        cerr << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();exit(1);
    }
    
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cerr << "SDL_m_image could not initialize! SDL_m_image Error: " << IMG_GetError() << endl;
        SDL_Quit();exit(1);
    }
    
    if(TTF_Init() !=0)
    {
        cerr << "Erreur lors de la creation de l'écriture : " << SDL_GetError() << endl;
        TTF_Quit();
        exit(100);
    }
    this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface * image_surface = IMG_Load(terrain_path.data());
    if (image_surface == nullptr)
    {
        cout << "Error: cannot load " << terrain_path << endl;
        exit(1);
    }

    SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(image_surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(image_surface);
    image_surface = surfaceCorrectPixelFormat;

    terrain_texture = SDL_CreateTextureFromSurface(this->sdl_renderer, surfaceCorrectPixelFormat);
    if (terrain_texture == nullptr)
    {
        cout << "Error: problem to create the texture of " << terrain_path << endl;
        exit(1);
    }
    SDL_FreeSurface(surfaceCorrectPixelFormat);
}

void Affichage::sdl_destroy()
{
    SDL_DestroyRenderer(this->sdl_renderer);
    SDL_DestroyWindow(this->sdl_window);
    SDL_DestroyTexture(this->terrain_texture);
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
                    this->terrain.get_joueur_b().haut_joueur();
                if (state[SDL_SCANCODE_S])
                    this->terrain.get_joueur_b().bas_joueur();
                if (state[SDL_SCANCODE_A])
                    this->terrain.get_joueur_b().gauche_joueur();
                if (state[SDL_SCANCODE_D])
                    this->terrain.get_joueur_b().droite_joueur();
                if (state[SDL_SCANCODE_E])
                    Coup c(this->terrain.get_joueur_b(), this->terrain.get_balle());

                if (state[SDL_SCANCODE_O])
                    this->terrain.get_joueur_a().haut_joueur();
                if (state[SDL_SCANCODE_L])
                    this->terrain.get_joueur_a().bas_joueur();
                if (state[SDL_SCANCODE_K])
                    this->terrain.get_joueur_a().gauche_joueur();
                if (state[SDL_SCANCODE_SEMICOLON])
                    this->terrain.get_joueur_a().droite_joueur();
                if (state[SDL_SCANCODE_P])
                    Coup c(this->terrain.get_joueur_a(), this->terrain.get_balle());
            }
        }

        auto now = chrono::high_resolution_clock::now();
        auto duration_between = chrono::duration_cast<chrono::microseconds>(now - last_time);
        this->terrain.get_balle().avancer_temps((double) duration_between.count() / 1000000.0);
        last_time = now; // Puts the current time into prev_frame_ts

        this->terrain.maj_points_service();
        this->terrain.repousser();

        // Render at each frame
        SDL_SetRenderDrawColor(this->sdl_renderer, 100, 100, 100, 255);
        SDL_RenderClear(this->sdl_renderer);
        // Here we render
        SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255);

        this->draw_terrain();
        this->draw_balle(this->terrain.get_balle());
        this->draw_joueur(this->terrain.get_joueur_a());
        this->draw_joueur(this->terrain.get_joueur_b());
        this->draw_score();

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
    float scale = (float) this->y_size / TERRAIN_Y_TOTAL;

    float origin_x = x_margin + (this->x_size - x_margin) / (float) 2;
    float origin_y = y_margin + (this->y_size - y_margin) / (float) 2;
    return Vec2(
        origin_x + (v.get_x() * scale),
        origin_y - (v.get_y() * scale)
    );
}
void Affichage::draw_score()
{
    
    TTF_Font* Sans = TTF_OpenFont("data/arial.ttf", 24);
    SDL_Color White = {0, 0, 0, 0};

    // Create a surface containing the player's name
    SDL_Surface* nameSurface = TTF_RenderText_Solid(Sans, this->terrain.get_joueur_b().get_nom().c_str(), White);
    SDL_Texture * nameS = SDL_CreateTextureFromSurface(this->sdl_renderer, nameSurface);

    SDL_Surface* nameSurfaceA = TTF_RenderText_Solid(Sans, this->terrain.get_joueur_a().get_nom().c_str(), White);
    SDL_Texture * nameSA = SDL_CreateTextureFromSurface(this->sdl_renderer, nameSurfaceA);

    // Create a surface containing the game count
    SDL_Surface* gameCountSurface = TTF_RenderText_Solid(Sans, std::to_string(this->terrain.get_joueur_b().get_score().get_jeu()).data(), White);
    SDL_Texture * gameCS = SDL_CreateTextureFromSurface(this->sdl_renderer, gameCountSurface);

     SDL_Surface* gameCountSurfaceA = TTF_RenderText_Solid(Sans, std::to_string(this->terrain.get_joueur_a().get_score().get_jeu()).data(), White);
    SDL_Texture * gameCSA = SDL_CreateTextureFromSurface(this->sdl_renderer, gameCountSurfaceA);

    // Create a surface containing the point count
    SDL_Surface* pointCountSurface;
    SDL_Texture * pointCS;
    SDL_Surface* pointCountSurfaceA;
    SDL_Texture * pointCSA;

    if(this->terrain.get_joueur_a().get_score().get_avantage() == true)
    {
        pointCountSurfaceA = TTF_RenderText_Solid(Sans, "A", White);
        pointCSA = SDL_CreateTextureFromSurface(this->sdl_renderer, pointCountSurfaceA);
    }
    else
    {
        pointCountSurfaceA = TTF_RenderText_Solid(Sans, std::to_string(this->terrain.get_joueur_a().get_score().get_points()).data(), White);
        pointCSA = SDL_CreateTextureFromSurface(this->sdl_renderer, pointCountSurfaceA);
    }

    if(this->terrain.get_joueur_b().get_score().get_avantage() == true)
    {
        pointCountSurface = TTF_RenderText_Solid(Sans, "A", White);
        pointCS = SDL_CreateTextureFromSurface(this->sdl_renderer, pointCountSurface);
    }
    else
    {
        pointCountSurface = TTF_RenderText_Solid(Sans, std::to_string(this->terrain.get_joueur_b().get_score().get_points()).data(), White);
        pointCS = SDL_CreateTextureFromSurface(this->sdl_renderer, pointCountSurface);
    }

    // Define the positions of the surfaces in the table
    SDL_Rect nameRect = { 30, 55, nameSurface->w, nameSurface->h };
    SDL_Rect gameCountRect = { 160, 55, gameCountSurface->w, gameCountSurface->h };
    SDL_Rect pointCountRect = { 210, 55, pointCountSurface->w, pointCountSurface->h };

    SDL_Rect nameRectA = { 30, 25, nameSurfaceA->w, nameSurfaceA->h };
    SDL_Rect gameCountRectA = { 160, 25, gameCountSurfaceA->w, gameCountSurfaceA->h };
    SDL_Rect pointCountRectA = { 210, 25, pointCountSurfaceA->w, pointCountSurfaceA->h };

    SDL_SetRenderDrawColor(this->sdl_renderer, 16, 106, 31, 255);
    SDL_Rect backgroundRect = {20, 20, 231, 60};
    SDL_RenderFillRect(this->sdl_renderer, &backgroundRect);

    SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255);
    SDL_Rect backgroundRect2 = {202, 20, 49, 60};
    SDL_RenderFillRect(this->sdl_renderer, &backgroundRect2);


    SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255); 

    SDL_SetRenderDrawColor(this->sdl_renderer, 255, 165, 0, 255);
    
    //Dessin des lignes horizontales
    SDL_RenderDrawLine(this->sdl_renderer, 20, 20, 250, 20);
    SDL_RenderDrawLine(this->sdl_renderer, 20, 50, 250, 50);
    SDL_RenderDrawLine(this->sdl_renderer, 20, 80, 250, 80);
    SDL_RenderDrawLine(this->sdl_renderer, 21, 21, 251, 21);
    SDL_RenderDrawLine(this->sdl_renderer, 21, 51, 251, 51);
    SDL_RenderDrawLine(this->sdl_renderer, 21, 81, 251, 81);

    // Dessin des lignes verticales
    SDL_RenderDrawLine(this->sdl_renderer, 20, 20, 20, 80);
    SDL_RenderDrawLine(this->sdl_renderer, 150, 20, 150, 80);
    SDL_RenderDrawLine(this->sdl_renderer, 200, 20, 200, 80);
    SDL_RenderDrawLine(this->sdl_renderer, 250, 20, 250, 80);
    SDL_RenderDrawLine(this->sdl_renderer, 21, 21, 21, 81);
    SDL_RenderDrawLine(this->sdl_renderer, 151, 21, 151, 81);
    SDL_RenderDrawLine(this->sdl_renderer, 201, 21, 201, 81);
    SDL_RenderDrawLine(this->sdl_renderer, 251, 21, 251, 81);


    // Draw the surfaces on the screen
    SDL_RenderCopy(this->sdl_renderer, nameS, NULL, &nameRect);
    SDL_RenderCopy(this->sdl_renderer, gameCS, NULL, &gameCountRect);
    SDL_RenderCopy(this->sdl_renderer, pointCS, NULL, &pointCountRect);

    SDL_RenderCopy(this->sdl_renderer, nameSA, NULL, &nameRectA);
    SDL_RenderCopy(this->sdl_renderer, gameCSA, NULL, &gameCountRectA);
    SDL_RenderCopy(this->sdl_renderer, pointCSA, NULL, &pointCountRectA);

    SDL_FreeSurface(nameSurface);
    SDL_FreeSurface(gameCountSurface);
    SDL_FreeSurface(pointCountSurface);
    SDL_FreeSurface(nameSurfaceA);
    SDL_FreeSurface(gameCountSurfaceA);
    SDL_FreeSurface(pointCountSurfaceA);
    TTF_CloseFont(Sans);
}


void Affichage::draw_terrain()
{
    SDL_Rect r;
    Vec2 top_left_image = this->get_screen_coords(Vec2(-BORDER_X_SIZE, BORDER_Y_SIZE));
    Vec2 bottom_right_image = this->get_screen_coords(Vec2(BORDER_X_SIZE, -BORDER_Y_SIZE));
    r.x = top_left_image.get_x();
    r.y = top_left_image.get_y();
    r.w = bottom_right_image.get_x() - top_left_image.get_x();
    r.h = bottom_right_image.get_y() - top_left_image.get_y();
    int ok = SDL_RenderCopy(this->sdl_renderer,this->terrain_texture,nullptr,&r);
    assert(ok == 0);
    
    // Dessin du filet
    Vec2 top_left_net = this->get_screen_coords(Vec2(-BORDER_X_SIZE, NET_HEIGHT * 1.1));
    Vec2 bottom_right_net = this->get_screen_coords(Vec2(BORDER_X_SIZE, -NET_HEIGHT * 0.7));
    int line_count = 20; // Nombre de lignes de quadrillage

    // Définir la couleur de dessin en gris foncé
    SDL_SetRenderDrawColor(this->sdl_renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);

    // Dessiner les lignes horizontales de quadrillage
    for (int i = 0; i < line_count; i++) {
        int y = top_left_net.get_y() + (bottom_right_net.get_y() - top_left_net.get_y()) / line_count * i;
        SDL_RenderDrawLine(this->sdl_renderer, top_left_net.get_x(), y, bottom_right_net.get_x(), y);
    }

    // Dessiner les lignes verticales de quadrillage
    for (int i = 0; i < line_count; i++) {
        int x = top_left_net.get_x() + (bottom_right_net.get_x() - top_left_net.get_x()) / line_count * i;
        SDL_RenderDrawLine(this->sdl_renderer, x, top_left_net.get_y(), x, bottom_right_net.get_y());
    }

    // Chargemenet du logo
    SDL_Surface* logo = IMG_Load("data/logoRG.png");
    SDL_Texture* logoTexture = SDL_CreateTextureFromSurface(this->sdl_renderer, logo);
    int logoWidth, logoHeight;
    SDL_QueryTexture(logoTexture, nullptr, nullptr, &logoWidth, &logoHeight);

    // Copie de la texture du logo sur le rendu SDL
    SDL_Rect logoDestRect = {650, 20, logoWidth, logoHeight};
    SDL_RenderCopy(this->sdl_renderer, logoTexture, nullptr, &logoDestRect);
}

bool Affichage::test()
{
    Vec2 v(0,0);
    Vec2 v_proj = this->get_screen_coords(v, 0, 0);
    //assert(v_proj == Vec2(this->x_size / 2, this->y_size / 2));

    return (true);
}