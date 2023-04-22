#include "includes/SDL2Menu.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <map>
#include <string>

SDL2Menu::SDL2Menu(SDL_Renderer * renderer, TTF_Font * font, t_sdl2menu & objects, SDL_Colour colour_bg, SDL_Colour colour_text, int w, int h)
: renderer(renderer), font(font), objects(objects), colour_bg(colour_bg), colour_text(colour_text), w(w), h(h)
{
	int max_size = 0;
	for (auto it = objects.begin(); it != objects.end(); it++ )
	{   // it->first for the key, it->second for the value
		int temp_size;
		TTF_SizeText(this->font, it->first.data(), &temp_size, nullptr);
		if (temp_size > max_size)
			max_size = temp_size;
	}

	this->padding_x = this->w - (max_size + 0.05 * this->w);
	this->case_height = (this->h / (this->objects.size() + 3));
	this->padding_y = this->case_height * 2;
	this->space_between = this->case_height / (this->objects.size() - 1);
}

void SDL2Menu::draw()
{
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
				for (auto it = this->objects_to_draw.begin(); it != this->objects_to_draw.end(); it++)
				{
					if (it->second.belong_to(mouse_x, mouse_y))
						this->objects.at(it->first)(); // A call to a callback
				}
			}
		}

		// Render at each frame
		SDL_SetRenderDrawColor(this->renderer, 100, 100, 100, 255);
		SDL_RenderClear(this->renderer);
		// Here we render
		SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);

		for (auto it = this->objects_to_draw.begin(); it != this->objects_to_draw.end(); it++)
		{
			SDL_SetRenderDrawColor(this->renderer, this->colour_bg.r,this->colour_bg.g, this->colour_bg.b, this->colour_bg.a);
			SDL_Rect rect = {it->second.x, it->second.y, it->second.x + it->second.w, it->second.y + it->second.h};
			SDL_RenderDrawRect(this->renderer, &rect);
			TTF_Font* Sans = TTF_OpenFont("data/arial.ttf", 24);

			SDL_Surface* text_surface = TTF_RenderText_Solid(Sans, it->first.data(), this->colour_text);
			SDL_Texture * text_tex = SDL_CreateTextureFromSurface(this->renderer, text_surface);
			SDL_RenderCopy(this->renderer, text_tex, NULL, &rect);
			SDL_FreeSurface(text_surface);
			SDL_DestroyTexture(text_tex);
			TTF_CloseFont(Sans);
		}

		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
		SDL_RenderPresent(this->renderer);
	}
}
