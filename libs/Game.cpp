#include "Game.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include "Collision.hpp"

struct pos{
    float x, y;
    pos(float a, float b){
        x=a;
        y=b;
    }
};

bool Controller::jumping=0;
bool Controller::ml=0;
bool Controller::mr=0;
bool Controller::md=0;
bool Controller::arrL=0;
bool Controller::arrR=0;
bool Controller::arrU=0;

Physics* Controller::physicspointer=nullptr;

const int Game::screenheight=640;
const int Game::screenwidth=800;
SDL_Renderer *Game::renderer=nullptr;
SDL_Event Game::event;
int Game::gamescore=0;
int Game::scorecooldown=0;
SDL_Texture *Game::text=nullptr;
TTF_Font *Game::font=nullptr;
SDL_Surface *Game::surfaceMessage=nullptr;
SDL_Color Game::textcolor={0,0,0};

Game::Game(const char* title, int winposx, int winposy){
    window=SDL_CreateWindow(title, winposx, winposy, screenwidth, screenheight, 0);
    renderer=SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 0);
    running=1;
    floor.x=0;
    floor.y=512;
    floor.w=screenwidth;
    floor.h=screenheight-floor.y;
    textposition.x=0;
    textposition.y=-16;
    textposition.w=192;
    textposition.h=96;
    font = TTF_OpenFont("img/Pixellettersfull-BnJ5.ttf", 24);
    surfaceMessage=TTF_RenderText_Solid(font, "score:0", textcolor);
}
void Game::init(const float &a, const float &b){
    //load entities that stop the player (walls)
    ePointer=new Entity();
    ePointer->init(125.0f, 448.0f, 500, 70, "img/block.png", "wall1");
    ePointer=new Entity();
    ePointer->init(700.0f, 400.0f, 50, 90, "img/block.png", "wall2");
    ePointer=new Entity();
    ePointer->init(20.0f, 300.0f, 500, 20, "img/block.png", "wall3");
    ePointer->physics->gravity.set(0.0f, 0.0f);
    ePointer=new Entity();
    ePointer->init(0.0f, 200.0f, 20, 212, "img/block.png", "wall4");
    ePointer=new Entity();
    ePointer->init(780.0f, 100.0f, 20, 100, "img/block.png", "wall5");
    ePointer->physics->gravity.set(0.0f, 0.0f);
    ePointer=new Entity();
    ePointer->init(700.0f, 200.0f, 100, 20, "img/hoop.png", "hoop");
    ePointer->physics->gravity.set(0.0f, 0.0f);
    //load the player and give it controls
    ePointer=new Entity();
    ePointer->init(a, b, 64, 64, "img/player.png", "player");
    Controller::physicspointer=ePointer->physics;
    //load entities the player can move
    ePointer=new Entity();
    ePointer->init(200.0f, 250.0f, 16, 16, "img/ball.png", "square");

    //set how the floor looks like
    floorsprite=new SpriteComponent("img/floor.png");
}
void Game::handleEvents(){
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:running=false;break;
        default:break;
    }
}
void Game::update(){
    Controller::update();
    for(ePointer=Entity::start;ePointer!=NULL;ePointer=ePointer->next){
        //update all entities
        ePointer->update();
        //update collisions
        for(Entity *tmp=ePointer->next;tmp!=NULL;tmp=tmp->next){
            if(Collision::AABB(*ePointer->physics, *tmp->physics)){
                //note the ePointer's entity (the one loaded later) gets moved
                if(ePointer->label!=std::string("hoop")&&tmp->label!=std::string("hoop"))
                    Collision::resolveCollision(*ePointer->physics, *tmp->physics);
                if(ePointer->label==std::string("square")&&tmp->label==std::string("hoop")&&scorecooldown==0){
                    if(ePointer->physics->lastpos.y>tmp->physics->position.y){
                        std::cout<<"aha ti pa goljufas\n";
                        gamescore-=2;
                    }
                    {
                        gamescore++;
                        scorecooldown=20;
                        std::cout<<"hooray now your score is "<<gamescore<<'\n';
                    }
                }
            }
            //pickup functionality
            if(tmp->physics->pickup&&ePointer->physics->collisioncounter>=29){
                ePointer->physics->collisioncounter++;
                ePointer->physics->position.set(tmp->physics->position.x+(tmp->physics->collider.w/2)-(ePointer->physics->collider.w/2), tmp->physics->position.y);
                ePointer->physics->velocity=tmp->physics->velocity;
                ePointer->physics->acceleration=tmp->physics->acceleration;
                ePointer->physics->velocity+=tmp->physics->acceleration;
                //now make it so i can throw it with the arrow keys
                if(Controller::arrL){
                    ePointer->physics->velocity.x-=30.0f;
                }
                if(Controller::arrR){
                    ePointer->physics->velocity.x+=30.0f;
                }
                if(Controller::arrU){
                    ePointer->physics->velocity.y-=20.0f;
                }
            }
        }
    }
    if(scorecooldown>0)scorecooldown--;
    else scorecooldown=0;
}
void Game::render(){
    SDL_RenderClear(renderer);
    for(ePointer=Entity::start;ePointer!=NULL;ePointer=ePointer->next){
        ePointer->render();
    }
    SDL_RenderCopy(renderer, floorsprite->tex, NULL, &floor);
    std::string a="score:"+std::to_string(gamescore);
    surfaceMessage=TTF_RenderText_Solid(font, a.c_str(), textcolor);
    text=SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    SDL_RenderCopy(renderer, text, NULL, &textposition);
    SDL_RenderPresent(renderer);
}
int Game::getscore(){
    return gamescore;
}
void Game::clean(){
    for(ePointer=Entity::start;ePointer!=NULL;){
        Entity *tmp=ePointer;
        ePointer=ePointer->next;
        delete tmp;
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}