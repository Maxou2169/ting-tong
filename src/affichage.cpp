#include "includes/terrain.h"
#include "includes/affichage.h"
#include "includes/balle.h"
#include "includes/joueur.h"
#include "includes/coup.h"
#include "includes/boundingbox.h"

#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <string>
#include <vector>
#include <map>

Affichage::Affichage(Terrain &t, unsigned int x, unsigned int y)
	: terrain(t), x_size(x), y_size(y)
{
	this->load_config();
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

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		cerr << "SDL_m_image could not initialize! SDL_m_image Error: " << IMG_GetError() << endl;
		SDL_Quit();
		exit(1);
	}

	if (TTF_Init() != 0)
	{
		cerr << "Erreur lors de la creation de l'écriture : " << SDL_GetError() << endl;
		TTF_Quit();
		exit(100);
	}

	this->game_font = TTF_OpenFont("data/arial.ttf", 24);

	this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1, SDL_RENDERER_ACCELERATED);
}

void Affichage::sdl_init_terrain_logo(std::string terrain_path, std::string logo_path)
{
	SDL_DestroyTexture(this->terrain_texture);
	SDL_DestroyTexture(this->logo_texture);
	
	SDL_Surface *image_surface = IMG_Load(terrain_path.data());
	if (image_surface == nullptr)
	{
		cerr << "Error: cannot load " << terrain_path << endl;
		exit(1);
	}

	SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(image_surface, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(image_surface);
	image_surface = surfaceCorrectPixelFormat;

	this->terrain_texture = SDL_CreateTextureFromSurface(this->sdl_renderer, surfaceCorrectPixelFormat);
	if (terrain_texture == nullptr)
	{
		cerr << "Error: problem to create the texture of " << terrain_path << endl;
		exit(1);
	}
	SDL_FreeSurface(surfaceCorrectPixelFormat);
	image_surface = IMG_Load(logo_path.data());
	if (image_surface == nullptr)
	{
		cerr << "Error: cannot load " << logo_path << endl;
		exit(1);
	}

	surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(image_surface, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(image_surface);
	image_surface = surfaceCorrectPixelFormat;

	this->logo_texture = SDL_CreateTextureFromSurface(this->sdl_renderer, surfaceCorrectPixelFormat);
	if (this->logo_texture == nullptr)
	{
		cerr << "Error: problem to create the texture of " << logo_path << endl;
		exit(1);
	}
	SDL_FreeSurface(surfaceCorrectPixelFormat);
}

void Affichage::sdl_init_players(std::string j1_path, std::string j2_path)
{
	SDL_DestroyTexture(this->j1_texture);
	SDL_DestroyTexture(this->j2_texture);
	
	SDL_Surface *image_surface = IMG_Load(j1_path.data());
	if (image_surface == nullptr)
	{
		cerr << "Error: cannot load " << j1_path << endl;
		exit(1);
	}

	SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(image_surface, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(image_surface);
	image_surface = surfaceCorrectPixelFormat;

	this->j1_texture = SDL_CreateTextureFromSurface(this->sdl_renderer, surfaceCorrectPixelFormat);
	if (j1_texture == nullptr)
	{
		cerr << "Error: problem to create the texture of " << j2_path << endl;
		exit(1);
	}
	SDL_FreeSurface(surfaceCorrectPixelFormat);

	image_surface = IMG_Load(j2_path.data());
	if (image_surface == nullptr)
	{
		cerr << "Error: cannot load j2 at " << j2_path << endl;
		exit(1);
	}

	surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(image_surface, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(image_surface);
	image_surface = surfaceCorrectPixelFormat;

	this->j2_texture = SDL_CreateTextureFromSurface(this->sdl_renderer, surfaceCorrectPixelFormat);
	if (this->j2_texture == nullptr)
	{
		cerr << "Error: problem to create the texture of j2 at " << j2_path << endl;
		exit(1);
	}
	SDL_FreeSurface(surfaceCorrectPixelFormat);
}

void Affichage::sdl_destroy()
{
	SDL_DestroyRenderer(this->sdl_renderer);
	SDL_DestroyWindow(this->sdl_window);
	SDL_DestroyTexture(this->terrain_texture);
	SDL_DestroyTexture(this->logo_texture);
	SDL_DestroyTexture(this->j1_texture);
	SDL_DestroyTexture(this->j2_texture);
	TTF_CloseFont(this->game_font);
	SDL_Quit();
}

void Affichage::load_config()
{
	std::ifstream players_file("data/players.cfg");
	std::string name, path;
	while (players_file >> name >> path)
		this->joueurs_config.insert(make_pair(name, path));
	players_file.close();

	// On définit les valeurs par défaut (car J2 doit être défini en même temps que J1 pour le callback)
	this->terrain.get_joueur_a().set_nom(name);
	this->terrain.get_joueur_b().set_nom(name);

	std::ifstream terrain_file("data/terrains.cfg");
	std::string paths_buf, t_path, l_path;
	while (getline(terrain_file, name, '\n') && getline(terrain_file, paths_buf, '\n'))
	{
		std::stringstream paths_buf_ss(paths_buf);
		getline(paths_buf_ss, t_path, ' ');
		getline(paths_buf_ss, l_path, ' ');
		this->terrains_config.insert(make_pair(name, make_pair(t_path, l_path)));
	}
}

void Affichage::cb_change_terrain(std::string terrain_name)
{
	// On rappelle que la map est de forme "nom" => (terrain_path, logo_path)
	this->sdl_init_terrain_logo(this->terrains_config.find(terrain_name)->second.first, this->terrains_config.find(terrain_name)->second.second);
}

void Affichage::cb_change_format(std::string nb_jeux)
{
	if (nb_jeux == "1 Jeu")
		this->terrain.set_format(UN_JEU);
	else if (nb_jeux == "3 Jeux")
		this->terrain.set_format(TROIS_JEUX);
	else if (nb_jeux == "6 Jeux")
		this->terrain.set_format(SIX_JEUX);
	else // Should not happen but let's protect everything
		cout << "Else" << endl;
}

void Affichage::cb_change_joueur(std::string nom_joueur, int num_joueur)
{
	if (num_joueur == 1)
		this->terrain.get_joueur_a().set_nom(nom_joueur);
	else
		this->terrain.get_joueur_b().set_nom(nom_joueur);

	this->sdl_init_players(
		this->joueurs_config.find(this->terrain.get_joueur_a().get_nom())->second,
		this->joueurs_config.find(this->terrain.get_joueur_b().get_nom())->second
	);
}

void Affichage::sous_affichage_menu_terrain()
{
	SDL_Colour colour_bg = {255, 255, 255, 255};
	SDL_Colour colour_text = {0, 0, 0, 255};
	
	std::vector<std::string> options;
	for(auto it = this->terrains_config.begin(); it != this->terrains_config.end(); ++it) {
		options.push_back(it->first);
	}

	// Trouver le max des cases à afficher
	int max_size = 0;
	for (auto it = options.begin(); it != options.end(); it++)
	{
		int temp_size;
		TTF_SizeText(this->game_font, it->data(), &temp_size, nullptr);
		if (temp_size > max_size)
			max_size = temp_size;
	}
	int case_height = (this->y_size / (options.size() + 3));

	// Créer les bounding_box pour chaque case
	std::map<std::string, BoundingBox> objects_to_draw;
	int case_width = max_size + 0.05 * this->x_size;
	case_height = (this->y_size / (options.size() + 3));
	int space_between = case_height / (options.size() - 1);
	int total_height = (case_height + space_between) * options.size() - space_between;
	int x = (this->x_size - case_width) / 2;
	int y = (this->y_size - total_height) / 2;
	for (auto it = options.begin(); it != options.end(); it++)
	{
		objects_to_draw.insert(make_pair(*it, BoundingBox(
			x, y, case_width, case_height)));
		y += (case_height + space_between);
	}
	// Faire la boucle de rendu qui gère les pointeurs sur f()
	SDL_Event events;
	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&events))
		{ // Event loop
			if (events.type == SDL_QUIT)
				quit = true; // Si l'utilisateur a clique sur la croix de fermeture
			else if (events.type == SDL_MOUSEBUTTONDOWN)
			{
				int mouse_x = 0;
				int mouse_y = 0;
				SDL_GetMouseState(&mouse_x, &mouse_y);
				for (auto it = objects_to_draw.begin(); it != objects_to_draw.end(); it++)
				{
					if (it->second.belong_to(mouse_x, mouse_y))
					{
						std::string t(it->first);
						cb_change_terrain(t);
						quit = true;
					}
				}
			}
		}
		// Render at each frame
		SDL_SetRenderDrawColor(this->sdl_renderer, 100, 100, 100, 255);
		SDL_RenderClear(this->sdl_renderer);
		// Here we render
		SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255);

		// Afficher l'objectif du menu
		// Render at each frame
		SDL_Color White = {255, 255, 255, 255};

		// Create a surface containing the player's name
		SDL_Surface *Surface = TTF_RenderText_Solid(this->game_font, "Selectionner le tournoi", White);
		SDL_Texture *Texture = SDL_CreateTextureFromSurface(this->sdl_renderer, Surface);

		// Get the dimensions of the texture
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(Texture, NULL, NULL, &texW, &texH);

		// Calculate the position to center the text
		int a = (this->x_size - texW) / 2;
		SDL_Rect nameRect = {a, 0, Surface->w, Surface->h};

		SDL_SetRenderDrawColor(this->sdl_renderer, 100, 100, 100, 255);

		SDL_RenderCopy(this->sdl_renderer, Texture, NULL, &nameRect);

		SDL_FreeSurface(Surface);
		SDL_DestroyTexture(Texture);

		// Définir une variable pour la couleur de surbrillance
		SDL_Color highlight_color = {255, 255, 255, 255};

		// Initialiser selected_item à nullptr
		auto selected_item = objects_to_draw.end();

		// Boucle pour dessiner les éléments du menu
		for (auto it = objects_to_draw.begin(); it != objects_to_draw.end(); it++)
		{
			// Définir la couleur de fond de la case en fonction de si elle est sélectionnée ou non
			if (it == selected_item)
			{
				SDL_SetRenderDrawColor(this->sdl_renderer, highlight_color.r, highlight_color.g, highlight_color.b, highlight_color.a);
			}
			else
			{
				SDL_SetRenderDrawColor(this->sdl_renderer, colour_bg.r, colour_bg.g, colour_bg.b, colour_bg.a);
			}

			// Dessiner la case
			SDL_Rect rect = {it->second.x, it->second.y, it->second.w, it->second.h};
			SDL_RenderFillRect(this->sdl_renderer, &rect);

			// Centrer le texte dans la case
			SDL_Surface *text_surface = TTF_RenderText_Solid(this->game_font, it->first.data(), colour_text);
			SDL_Texture *text_tex = SDL_CreateTextureFromSurface(this->sdl_renderer, text_surface);
			int text_w, text_h;
			SDL_QueryTexture(text_tex, NULL, NULL, &text_w, &text_h);
			SDL_Rect text_rect = {(it->second.x + (it->second.w - text_w) / 2), (it->second.y + (it->second.h - text_h) / 2), text_w, text_h};
			SDL_RenderCopy(this->sdl_renderer, text_tex, NULL, &text_rect);
			SDL_FreeSurface(text_surface);
			SDL_DestroyTexture(text_tex);
		}

			// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
			SDL_RenderPresent(this->sdl_renderer);
	}
}

void Affichage::sous_affichage_menu_jeux()
{
	SDL_Colour colour_bg = {255, 255, 255, 255};
	SDL_Colour colour_text = {0, 0, 0, 255};

	// Menu choix nb_jeux-----------------------------------------------------------------------------------------------
	std::vector<std::string> options;

	options.push_back("1 Jeu");
	options.push_back("3 Jeux");
	options.push_back("6 Jeux");

	// Trouver le max des cases à afficher
	int max_size = 0;
	for (auto it = options.begin(); it != options.end(); it++)
	{
		int temp_size;
		TTF_SizeText(this->game_font, it->data(), &temp_size, nullptr);
		if (temp_size > max_size)
			max_size = temp_size;
	}
	int case_height = (this->y_size / (options.size() + 3));

	// Créer les bounding_box pour chaque case
	std::map<std::string, BoundingBox> objects_to_draw;
	int case_width = max_size + 0.05 * this->x_size;
	case_height = (this->y_size / (options.size() + 3));
	int space_between = case_height / (options.size() - 1);
	int total_height = (case_height + space_between) * options.size() - space_between;
	int x = (this->x_size - case_width) / 2;
	int y = (this->y_size - total_height) / 2;
	for (auto it = options.begin(); it != options.end(); it++)
	{
		objects_to_draw.insert(make_pair(*it, BoundingBox(
			x, y, case_width, case_height)));
		y += (case_height + space_between);
	}
	// Faire la boucle de rendu qui gère les pointeurs sur f()
	SDL_Event events;
	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&events))
		{ // Event loop
			if (events.type == SDL_QUIT)
				quit = true; // Si l'utilisateur a clique sur la croix de fermeture
			else if (events.type == SDL_MOUSEBUTTONDOWN)
			{
				int mouse_x = 0;
				int mouse_y = 0;
				SDL_GetMouseState(&mouse_x, &mouse_y);
				for (auto it = objects_to_draw.begin(); it != objects_to_draw.end(); it++)
				{
					if (it->second.belong_to(mouse_x, mouse_y))
					{
						std::string t(it->first); // Utile pour simplifier les histoires de templates de templates de string
						cb_change_format(t);
						quit = true;
					}
				}
			}
		}
		// Render at each frame
		SDL_SetRenderDrawColor(this->sdl_renderer, 100, 100, 100, 255);
		SDL_RenderClear(this->sdl_renderer);
		// Here we render
		SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255);

		// Afficher l'objectif du menu
		// Render at each frame
		SDL_Color White = {255, 255, 255, 255};

		// Create a surface containing the player's name
		SDL_Surface *Surface = TTF_RenderText_Solid(this->game_font, "Selectionner le format du match", White);
		SDL_Texture *Texture = SDL_CreateTextureFromSurface(this->sdl_renderer, Surface);

		// Get the dimensions of the texture
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(Texture, NULL, NULL, &texW, &texH);

		// Calculate the position to center the text
		int a = (this->x_size - texW) / 2;
		SDL_Rect nameRect = {a, 0, Surface->w, Surface->h};

		SDL_SetRenderDrawColor(this->sdl_renderer, 100, 100, 100, 255);

		SDL_RenderCopy(this->sdl_renderer, Texture, NULL, &nameRect);

		SDL_FreeSurface(Surface);
		SDL_DestroyTexture(Texture);


		// Définir une variable pour la couleur de surbrillance
		SDL_Color highlight_color = {255, 255, 255, 255};

		// Initialiser selected_item à nullptr
		auto selected_item = objects_to_draw.end();

		// Boucle pour dessiner les éléments du menu
		for (auto it = objects_to_draw.begin(); it != objects_to_draw.end(); it++)
		{
			// Définir la couleur de fond de la case en fonction de si elle est sélectionnée ou non
			if (it == selected_item)
			{
				SDL_SetRenderDrawColor(this->sdl_renderer, highlight_color.r, highlight_color.g, highlight_color.b, highlight_color.a);
			}
			else
			{
				SDL_SetRenderDrawColor(this->sdl_renderer, colour_bg.r, colour_bg.g, colour_bg.b, colour_bg.a);
			}

			// Dessiner la case
			SDL_Rect rect = {it->second.x, it->second.y, it->second.w, it->second.h};
			SDL_RenderFillRect(this->sdl_renderer, &rect);

			// Centrer le texte dans la case
			SDL_Surface *text_surface = TTF_RenderText_Solid(this->game_font, it->first.data(), colour_text);
			SDL_Texture *text_tex = SDL_CreateTextureFromSurface(this->sdl_renderer, text_surface);
			int text_w, text_h;
			SDL_QueryTexture(text_tex, NULL, NULL, &text_w, &text_h);
			SDL_Rect text_rect = {(it->second.x + (it->second.w - text_w) / 2), (it->second.y + (it->second.h - text_h) / 2), text_w, text_h};
			SDL_RenderCopy(this->sdl_renderer, text_tex, NULL, &text_rect);
			SDL_FreeSurface(text_surface);
			SDL_DestroyTexture(text_tex);
		}

		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
		SDL_RenderPresent(this->sdl_renderer);
	}
}

void Affichage::sous_affichage_menu_joueur()
{
	for (int num_joueur = 1; num_joueur <= 2; num_joueur++)
	{ 
		SDL_Colour colour_bg = {255, 255, 255, 255};
		SDL_Colour colour_text = {0, 0, 0, 255};

    	// Menu choix joueur
    	std::vector<std::string> options;
		// On charge les différentes options
		for(auto it = this->joueurs_config.begin(); it != this->joueurs_config.end(); ++it) {
			options.push_back(it->first);
		}

		int max_size = 0;
		for (auto it = options.begin(); it != options.end(); it++)
		{
			int temp_size;
			TTF_SizeText(this->game_font, it->data(), &temp_size, nullptr);
			if (temp_size > max_size)
				max_size = temp_size;
		}
		int case_height = (this->y_size / (options.size() + 3));

		// Créer les bounding_box pour chaque case
		std::map<std::string, BoundingBox> objects_to_draw;
		int case_width = max_size + 0.05 * this->x_size;
		case_height = (this->y_size / (options.size() + 3));
		int space_between = case_height / (options.size() - 1);
		int total_height = (case_height + space_between) * options.size() - space_between;
		int x = (this->x_size - case_width) / 2;
		int y = (this->y_size - total_height) / 2;
		for (auto it = options.begin(); it != options.end(); it++)
		{
			objects_to_draw.insert(make_pair(*it, BoundingBox(
				x, y, case_width, case_height)));
			y += (case_height + space_between);
		}


    	// Faire la boucle de rendu qui gère les pointeurs sur f()
    	SDL_Event events;
    	bool quit = false;

    	while (!quit)
    	{
    	    while (SDL_PollEvent(&events))
    	    {
    	        if (events.type == SDL_QUIT)
    	            quit = true;
    	        else if (events.type == SDL_MOUSEBUTTONDOWN)
    	        {
    	            int mouse_x = 0;
    	            int mouse_y = 0;
    	            SDL_GetMouseState(&mouse_x, &mouse_y);
    	            for (auto it = objects_to_draw.begin(); it != objects_to_draw.end(); it++)
    	            {
    	                if (it->second.belong_to(mouse_x, mouse_y))
    	                {
    	                    std::string t(it->first);
    	                    cb_change_joueur(t, num_joueur);
    	                    quit = true;
    	                }
    	            }
    	        }
    	    }
		// Render at each frame
		SDL_SetRenderDrawColor(this->sdl_renderer, 100, 100, 100, 255);
		SDL_RenderClear(this->sdl_renderer);
		// Here we render
		SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255);

		// Afficher l'objectif du menu
		// Render at each frame
		SDL_Color White = {255, 255, 255, 255};

		// Create a surface containing the player's name
		std::string a_afficher = "Selectionner le joueur " + to_string(num_joueur);
		SDL_Surface *Surface = TTF_RenderText_Solid(this->game_font, a_afficher.data(), White);
		SDL_Texture *Texture = SDL_CreateTextureFromSurface(this->sdl_renderer, Surface);

		// Get the dimensions of the texture
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(Texture, NULL, NULL, &texW, &texH);

		// Calculate the position to center the text
		int a = (this->x_size - texW) / 2;
		SDL_Rect nameRect = {a, 0, Surface->w, Surface->h};

		SDL_SetRenderDrawColor(this->sdl_renderer, 100, 100, 100, 255);

		SDL_RenderCopy(this->sdl_renderer, Texture, NULL, &nameRect);

		SDL_FreeSurface(Surface);
		SDL_DestroyTexture(Texture);


		// Définir une variable pour la couleur de surbrillance
		SDL_Color highlight_color = {255, 255, 255, 255};

		// Initialiser selected_item à nullptr
		auto selected_item = objects_to_draw.end();

		// Boucle pour dessiner les éléments du menu
		for (auto it = objects_to_draw.begin(); it != objects_to_draw.end(); it++)
		{
			// Définir la couleur de fond de la case en fonction de si elle est sélectionnée ou non
			if (it == selected_item)
			{
				SDL_SetRenderDrawColor(this->sdl_renderer, highlight_color.r, highlight_color.g, highlight_color.b, highlight_color.a);
			}
			else
			{
				SDL_SetRenderDrawColor(this->sdl_renderer, colour_bg.r, colour_bg.g, colour_bg.b, colour_bg.a);
			}

			// Dessiner la case
			SDL_Rect rect = {it->second.x, it->second.y, it->second.w, it->second.h};
			SDL_RenderFillRect(this->sdl_renderer, &rect);

			// Centrer le texte dans la case
			SDL_Surface *text_surface = TTF_RenderText_Solid(this->game_font, it->first.data(), colour_text);
			SDL_Texture *text_tex = SDL_CreateTextureFromSurface(this->sdl_renderer, text_surface);
			int text_w, text_h;
			SDL_QueryTexture(text_tex, NULL, NULL, &text_w, &text_h);
			SDL_Rect text_rect = {(it->second.x + (it->second.w - text_w) / 2), (it->second.y + (it->second.h - text_h) / 2), text_w, text_h};
			SDL_RenderCopy(this->sdl_renderer, text_tex, NULL, &text_rect);
			SDL_FreeSurface(text_surface);
			SDL_DestroyTexture(text_tex);
		}


		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
		SDL_RenderPresent(this->sdl_renderer);
	}

	}
}	

void Affichage::affichage_menu()
{
	sous_affichage_menu_joueur();
	sous_affichage_menu_terrain();
	sous_affichage_menu_jeux();
}

void Affichage::affichage_jeu()
{
	SDL_Event events;
	bool quit = false;
	auto last_time = chrono::high_resolution_clock::now();
	while (!quit)
	{
		int jeuA = this->terrain.get_joueur_a().get_score().get_jeu();
		int jeuB = this->terrain.get_joueur_b().get_score().get_jeu();
		int f = this->terrain.get_format().get_jeux();
		if (jeuA == f || jeuB == f)
		{
			quit = true;
		}
		while (SDL_PollEvent(&events))
		{ // Event loop
			if (events.type == SDL_QUIT)
				quit = true; // Si l'utilisateur a clique sur la croix de fermeture
			else if (events.type == SDL_KEYDOWN || events.type == SDL_KEYUP)
			{
				const Uint8 *state = SDL_GetKeyboardState(NULL);
				if (state[SDL_SCANCODE_ESCAPE])
					quit = true;
				if (this->terrain.joueur_peut_bouger(this->terrain.get_joueur_b()))
				{
					if (state[SDL_SCANCODE_W])
						this->terrain.get_joueur_b().haut_joueur();
					if (state[SDL_SCANCODE_S])
						this->terrain.get_joueur_b().bas_joueur();
					if (state[SDL_SCANCODE_A])
						this->terrain.get_joueur_b().gauche_joueur();
					if (state[SDL_SCANCODE_D])
						this->terrain.get_joueur_b().droite_joueur();
				}
				if (state[SDL_SCANCODE_E])
					Coup c(this->terrain.get_joueur_b(), this->terrain.get_balle());

				if (this->terrain.joueur_peut_bouger(this->terrain.get_joueur_a()))
				{
					if (state[SDL_SCANCODE_O])
						this->terrain.get_joueur_a().haut_joueur();
					if (state[SDL_SCANCODE_L])
						this->terrain.get_joueur_a().bas_joueur();
					if (state[SDL_SCANCODE_K])
						this->terrain.get_joueur_a().gauche_joueur();
					if (state[SDL_SCANCODE_SEMICOLON])
						this->terrain.get_joueur_a().droite_joueur();
				}
				if (state[SDL_SCANCODE_P])
					Coup c(this->terrain.get_joueur_a(), this->terrain.get_balle());
			}
		}

		auto now = chrono::high_resolution_clock::now();
		auto duration_between = chrono::duration_cast<chrono::microseconds>(now - last_time);
		this->terrain.get_balle().avancer_temps((double)duration_between.count() / 1000000.0);
		last_time = now; // Puts the current time into prev_frame_ts

		this->terrain.maj_points_service();
		this->terrain.repousser();

		// Render at each frame
		SDL_SetRenderDrawColor(this->sdl_renderer, 100, 100, 100, 255);
		SDL_RenderClear(this->sdl_renderer);
		// Here we render
		SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255);

		this->draw_terrain();
		this->draw_joueur(this->terrain.get_joueur_a());
		this->draw_joueur(this->terrain.get_joueur_b());
		this->draw_balle(this->terrain.get_balle());
		this->draw_score();

		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
		SDL_RenderPresent(this->sdl_renderer);
	}
}

void Affichage::affichage_vainqueur()
{
	SDL_Event events;
	bool quit = false;
	while (!quit)
	{

		while (SDL_PollEvent(&events))
		{ // Event loop
			if (events.type == SDL_QUIT)
				quit = true; // Si l'utilisateur a clique sur la croix de fermeture
		}

		int jeuA = this->terrain.get_joueur_a().get_score().get_jeu();
		int jeuB = this->terrain.get_joueur_b().get_score().get_jeu();

		int PointA = this->terrain.get_joueur_a().get_score().get_points();
		int PointB = this->terrain.get_joueur_b().get_score().get_points();

		bool avA = this->terrain.get_joueur_a().get_score().get_avantage();

		string Vainqueur;
		string Perdant;

		if (jeuA > jeuB)
		{
			Vainqueur = this->terrain.get_joueur_a().get_nom();
			Perdant = this->terrain.get_joueur_b().get_nom();
		}
		else if (jeuA == jeuB)
		{
			if (PointA > PointB)
			{
				Vainqueur = this->terrain.get_joueur_a().get_nom();
				Perdant = this->terrain.get_joueur_b().get_nom();
			}
			else if (PointA == PointB)
			{
				if (avA == true)
				{
					Vainqueur = this->terrain.get_joueur_a().get_nom();
					Perdant = this->terrain.get_joueur_b().get_nom();
				}
				else
				{
					Vainqueur = this->terrain.get_joueur_b().get_nom();
					Perdant = this->terrain.get_joueur_a().get_nom();
				}
			}
			else
			{
				Vainqueur = this->terrain.get_joueur_b().get_nom();
				Perdant = this->terrain.get_joueur_a().get_nom();
			}
		}
		else
		{
			Vainqueur = this->terrain.get_joueur_b().get_nom();
			Perdant = this->terrain.get_joueur_a().get_nom();
		}

		// Render at each frame
		SDL_Color White = {255, 255, 255, 255};

		string formulation = " gagne le match contre ";
		string annonce = Vainqueur + formulation + Perdant;

		// Create a surface containing the player's name
		SDL_Surface *Surface = TTF_RenderText_Solid(this->game_font, annonce.c_str(), White);
		SDL_Texture *Texture = SDL_CreateTextureFromSurface(this->sdl_renderer, Surface);

		// Get the dimensions of the texture
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(Texture, NULL, NULL, &texW, &texH);

		// Calculate the position to center the text
		int x = (this->x_size - texW) / 2;
		int y = (this->y_size - texH) / 2;

		SDL_Rect nameRect = {x, y, Surface->w, Surface->h};

		SDL_SetRenderDrawColor(this->sdl_renderer, 100, 100, 100, 255);
		SDL_RenderClear(this->sdl_renderer);

		SDL_RenderCopy(this->sdl_renderer, Texture, NULL, &nameRect);

		SDL_FreeSurface(Surface);
		SDL_DestroyTexture(Texture);

		SDL_RenderPresent(this->sdl_renderer);
	}
}

void Affichage::draw_joueur(const Joueur& j)
{
    Vec2 pos_proj = this->get_screen_coords(j.get_pos());

	SDL_Texture * player_to_draw;
	if (j.get_pos().get_y() > 0)
		player_to_draw = this->j1_texture;
	else
		player_to_draw = this->j2_texture;

	// Set the destination rectangle for the image
    SDL_Rect destRect = {
        (int)pos_proj.get_x() - 50,   // x-coordinate of the top-left corner of the rectangle
        (int)pos_proj.get_y() - 50,   // y-coordinate of the top-left corner of the rectangle
        100,                          // width of the rectangle
        100                           // height of the rectangle
    };
    // Render the texture on the screen
    SDL_RenderCopy(this->sdl_renderer, player_to_draw, NULL, &destRect);
}

void Affichage::draw_circle(int x, int y, int radius, SDL_Color color)
{
	SDL_Renderer *renderer = this->sdl_renderer;
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, x + dx, y + dy);
			}
		}
	}
}

void Affichage::draw_balle(const Balle &b)
{
	Vec2 pos_proj = this->get_screen_coords(b.get_pos());
	SDL_Color yellow = {255, 255, 0, 255};
	this->draw_circle(
		pos_proj.get_x(),
		pos_proj.get_y(),
		10,
		yellow);
}

Vec2 Affichage::get_screen_coords(const Vec2 &v, float x_margin, float y_margin)
{
	float scale = (float)this->y_size / TERRAIN_Y_TOTAL;

	float origin_x = x_margin + (this->x_size - x_margin) / (float)2;
	float origin_y = y_margin + (this->y_size - y_margin) / (float)2;
	return Vec2(
		origin_x + (v.get_x() * scale),
		origin_y - (v.get_y() * scale));
}

void Affichage::draw_score()
{

	SDL_Color White = {0, 0, 0, 0};

	// Create a surface containing the player's name
	SDL_Surface *nameSurface = TTF_RenderText_Solid(this->game_font, this->terrain.get_joueur_b().get_nom().c_str(), White);
	SDL_Texture *nameS = SDL_CreateTextureFromSurface(this->sdl_renderer, nameSurface);

	SDL_Surface *nameSurfaceA = TTF_RenderText_Solid(this->game_font, this->terrain.get_joueur_a().get_nom().c_str(), White);
	SDL_Texture *nameSA = SDL_CreateTextureFromSurface(this->sdl_renderer, nameSurfaceA);

	// Create a surface containing the game count
	SDL_Surface *gameCountSurface = TTF_RenderText_Solid(this->game_font, std::to_string(this->terrain.get_joueur_b().get_score().get_jeu()).data(), White);
	SDL_Texture *gameCS = SDL_CreateTextureFromSurface(this->sdl_renderer, gameCountSurface);

	SDL_Surface *gameCountSurfaceA = TTF_RenderText_Solid(this->game_font, std::to_string(this->terrain.get_joueur_a().get_score().get_jeu()).data(), White);
	SDL_Texture *gameCSA = SDL_CreateTextureFromSurface(this->sdl_renderer, gameCountSurfaceA);

	// Create a surface containing the point count
	SDL_Surface *pointCountSurface;
	SDL_Texture *pointCS;
	SDL_Surface *pointCountSurfaceA;
	SDL_Texture *pointCSA;

	if (this->terrain.get_joueur_a().get_score().get_avantage() == true)
	{
		pointCountSurfaceA = TTF_RenderText_Solid(this->game_font, "A", White);
		pointCSA = SDL_CreateTextureFromSurface(this->sdl_renderer, pointCountSurfaceA);
	}
	else
	{
		pointCountSurfaceA = TTF_RenderText_Solid(this->game_font, std::to_string(this->terrain.get_joueur_a().get_score().get_points()).data(), White);
		pointCSA = SDL_CreateTextureFromSurface(this->sdl_renderer, pointCountSurfaceA);
	}

	if (this->terrain.get_joueur_b().get_score().get_avantage() == true)
	{
		pointCountSurface = TTF_RenderText_Solid(this->game_font, "A", White);
		pointCS = SDL_CreateTextureFromSurface(this->sdl_renderer, pointCountSurface);
	}
	else
	{
		pointCountSurface = TTF_RenderText_Solid(this->game_font, std::to_string(this->terrain.get_joueur_b().get_score().get_points()).data(), White);
		pointCS = SDL_CreateTextureFromSurface(this->sdl_renderer, pointCountSurface);
	}

	// Define the positions of the surfaces in the table
	SDL_Rect nameRect = {30, 55, nameSurface->w, nameSurface->h};
	SDL_Rect gameCountRect = {160, 55, gameCountSurface->w, gameCountSurface->h};
	SDL_Rect pointCountRect = {210, 55, pointCountSurface->w, pointCountSurface->h};

	SDL_Rect nameRectA = {30, 25, nameSurfaceA->w, nameSurfaceA->h};
	SDL_Rect gameCountRectA = {160, 25, gameCountSurfaceA->w, gameCountSurfaceA->h};
	SDL_Rect pointCountRectA = {210, 25, pointCountSurfaceA->w, pointCountSurfaceA->h};

	SDL_SetRenderDrawColor(this->sdl_renderer, 16, 106, 31, 255);
	SDL_Rect backgroundRect = {20, 20, 231, 60};
	SDL_RenderFillRect(this->sdl_renderer, &backgroundRect);

	SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255);
	SDL_Rect backgroundRect2 = {202, 20, 49, 60};
	SDL_RenderFillRect(this->sdl_renderer, &backgroundRect2);

	SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255);

	SDL_SetRenderDrawColor(this->sdl_renderer, 255, 165, 0, 255);

	// Dessin des lignes horizontales
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
	SDL_FreeSurface(nameSurfaceA);
	SDL_FreeSurface(gameCountSurface);
	SDL_FreeSurface(gameCountSurfaceA);
	SDL_FreeSurface(pointCountSurface);
	SDL_FreeSurface(pointCountSurfaceA);

	SDL_DestroyTexture(nameS);
	SDL_DestroyTexture(nameSA);
	SDL_DestroyTexture(gameCS);
	SDL_DestroyTexture(gameCSA);
	SDL_DestroyTexture(pointCS);
	SDL_DestroyTexture(pointCSA);
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
	int ok = SDL_RenderCopy(this->sdl_renderer, this->terrain_texture, nullptr, &r);
	assert(ok == 0);

	// Dessin du filet
	Vec2 top_left_net = this->get_screen_coords(Vec2(-BORDER_X_SIZE, NET_HEIGHT * 1.1));
	Vec2 bottom_right_net = this->get_screen_coords(Vec2(BORDER_X_SIZE, -NET_HEIGHT * 0.7));
	int line_count = 20; // Nombre de lignes de quadrillage

	// Définir la couleur de dessin en gris foncé
	SDL_SetRenderDrawColor(this->sdl_renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);

	// Dessiner les lignes horizontales de quadrillage
	for (int i = 0; i < line_count; i++)
	{
		int y = top_left_net.get_y() + (bottom_right_net.get_y() - top_left_net.get_y()) / line_count * i;
		SDL_RenderDrawLine(this->sdl_renderer, top_left_net.get_x(), y, bottom_right_net.get_x(), y);
	}

	// Dessiner les lignes verticales de quadrillage
	for (int i = 0; i < line_count; i++)
	{
		int x = top_left_net.get_x() + (bottom_right_net.get_x() - top_left_net.get_x()) / line_count * i;
		SDL_RenderDrawLine(this->sdl_renderer, x, top_left_net.get_y(), x, bottom_right_net.get_y());
	}

	int logoWidth;
	int logoHeight;
	SDL_QueryTexture(this->logo_texture, nullptr, nullptr, &logoWidth, &logoHeight);

	logoWidth /= 20;
	logoHeight /= 20;

	// Copie de la texture du logo sur le rendu SDL
	SDL_Rect logoDestRect = {650, 20, logoWidth, logoHeight};
	SDL_RenderCopy(this->sdl_renderer, this->logo_texture, nullptr, &logoDestRect);
}

void Affichage::affichage()
{
	affichage_menu();
	affichage_jeu();
	affichage_vainqueur();
}

bool Affichage::test()
{
	Vec2 v(0, 0);
	Vec2 v_proj = this->get_screen_coords(v, 0, 0);
	// assert(v_proj == Vec2(this->x_size / 2, this->y_size / 2));

	return (true);
}
