#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"

class SpriteComponent{
    public:
    SDL_Texture *tex;
    SpriteComponent(const char* path);
    void setTex(const char* path);
    ~SpriteComponent(){
        SDL_DestroyTexture(tex);
    }
};