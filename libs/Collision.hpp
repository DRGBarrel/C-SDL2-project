#pragma once
#include <SDL2/SDL.h>
#include "PhysicsComponent.hpp"
class Physics;

class Collision{
    public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const Physics& colA, const Physics& colB);
    static float collisiondistanceX(const SDL_Rect& recA, const SDL_Rect& recB);
    static float collisiondistanceY(const SDL_Rect& recA, const SDL_Rect& recB);
    static void resolveCollision(Physics& pA, Physics& pB);
};