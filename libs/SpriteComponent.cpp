#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(const char* path){
    setTex(path);
}
void SpriteComponent::setTex(const char* path){
    SDL_Surface* surface=IMG_Load(path);
    tex=SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
}