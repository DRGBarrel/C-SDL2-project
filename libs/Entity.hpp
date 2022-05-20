#pragma once
#include "Components.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include "Game.hpp"
#include <SDL2/SDL.h>
#include <iostream>

class SpriteComponent;
class Physics;

class Entity{
    private:
    
    public:
    const char* label;
    Entity *next;
    static Entity *start;
    Physics *physics;
    SpriteComponent *sp;
    
    Entity();
    void init(float x, float y, int w, int h, const char* spritepath, const char* label);
    void addToPList();
    void other();
    void update();
    void render();
    ~Entity(){
        if(next!=NULL){
            delete next;
            next==NULL;
        }
    }
};