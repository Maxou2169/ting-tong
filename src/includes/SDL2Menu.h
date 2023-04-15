#ifndef SDL2MENU_H
# define SDL2MENU_H

# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>
# include <map>
# include <string>

class BoundingBox
{
    public:
        int x;
        int y;
        int w;
        int h;
        /**
         * \brief Creates a bounding box
         * \param x : The x-coordinate of the start of the box
         * \param y : The y-coordinate of the start of the box
         * \param w : The width of the box
         * \param h : The hieght of the box
        */
        BoundingBox(int x, int y, int w, int h);
        /**
         * \brief Tells if the point (x,y) is into the bounding box
         * \param x : The x-coordinate of the point to test
         * \param y : The y-coordinate of the point to test
        */
        bool belong_to(int x, int y);
};

/**
 * \typedef t_sdl2menu
 * This typedef aims to define easily what's awaited by SDL2Menu, a map of strings, with a void callback for each string
*/
typedef std::map<std::string, void * (void)> t_sdl2menu;

/**
 * \class SDL2Menu
 * \author Ethan PEGEOT
 * \brief This class implements a simple menu in the SDL
 * 
 * This simple class creates some little boxes with the text inside
*/
class SDL2Menu
{
    private:
        SDL_Renderer * renderer;
        TTF_Font * font;
        t_sdl2menu & objects;
        std::map<std::string, BoundingBox> objects_to_draw;
        SDL_Color colour_bg;
        SDL_Color colour_text;

        int w;
        int h;

        int padding_y; //< Total padding over the y axis, to divide by 2 for the top and bottom
        int padding_x; //< Also total padding over the x axis
        int case_height;
        int space_between;

        void draw_case(std::string text, int x, int y, int w, int h);
    
    public:
        SDL2Menu(SDL_Renderer * renderer, TTF_Font * font, t_sdl2menu & objects, SDL_Color color_bg, SDL_Color colour_text, int w, int h);

        void draw();

};

#endif