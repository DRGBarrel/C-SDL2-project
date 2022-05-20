#pragma once
#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Entity;
class SpriteComponent;
class Vector2D;
class Controller;

class Game{
    public:
    const static int screenwidth;
    const static int screenheight;
    SDL_Window *window;
    static SDL_Renderer *renderer;
    bool running;
    static SDL_Event event; 
    Entity *ePointer;
    SDL_Rect floor, textposition;
    SpriteComponent *floorsprite;
    static int gamescore, scorecooldown;
    static SDL_Texture *text;
    static TTF_Font *font;
    static SDL_Surface *surfaceMessage;
    static SDL_Color textcolor;

    Game(const char* title, int winposx, int winposy);
    void handleEvents();
    void clean();
    void init(const float &a, const float &b);
    void update();
    void render();
    int getscore();
    ~Game(){}
};