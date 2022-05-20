#include "Controller.hpp"
#include "Game.hpp"
class Controller;

void Controller::update(){
    if(Game::event.type==SDL_KEYDOWN){
        switch(Game::event.key.keysym.sym){
        case SDLK_w:
            jumping=true;
            break;
        case SDLK_a:
            ml=true;
            break;
        case SDLK_s:
            md=true;
            break;
        case SDLK_d:
            mr=true;
            break;
        case SDLK_SPACE:
            physicspointer->pickup=true;
            break;
        case SDLK_LEFT:
            arrL=true;
            break;
        case SDLK_RIGHT:
            arrR=true;
            break;
        case SDLK_UP:
            arrU=true;
            break;        
        default:break;
        }
    }
    if(Game::event.type==SDL_KEYUP){
        switch(Game::event.key.keysym.sym){
        case SDLK_w:
            jumping=false;
            break;
        case SDLK_a:
            ml=false;
            break;
        case SDLK_s:
            md=false;
            break;
        case SDLK_d:
            mr=false;
            break;
        case SDLK_SPACE:
            physicspointer->pickup=false;
            break;
        case SDLK_LEFT:
            arrL=false;
            break;
        case SDLK_RIGHT:
            arrR=false;
            break;
        case SDLK_UP:
            arrU=false;
            break;
        default:break;
        }
    }
    //update acceleration to where you're moving
    if(md)physicspointer->acceleration.y=0.3f;
    if(ml)physicspointer->acceleration.x=-0.3f;
    if(mr)physicspointer->acceleration.x=0.3f;
    if(!ml^mr)physicspointer->acceleration.x=0.0f;
    //refresh jump
    if(physicspointer->grounded)physicspointer->jump=1;
    //jump if jumping
    if(jumping&&physicspointer->jump>0){
        physicspointer->velocity.y=-25.0f;
        physicspointer->jump--;
        physicspointer->grounded=0;
    }
}