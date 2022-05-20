#pragma once
#include "Components.hpp"
#include "Vector2D.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Physics{
    public:
    Vector2D position, lastpos, velocity, gravity, acceleration;
    bool grounded, pickup;
    float drag;
    int jump, tbug, collisioncounter;
    SDL_Rect collider;
    const char* label;

    Physics(float x, float y, int w, int h);
    void other();
    void update();
    ~Physics(){}
};