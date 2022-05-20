#include "libs/Game.hpp"
#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>

struct pos{
    float x, y;
};

Game *game=nullptr;

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    if(TTF_Init()==0)std::cout<<"init\n";

    const int FPS=60, frameDelay=1000/FPS;
    Uint32 framestart;
    int frameTime, score=0, highscore=0;
    //read player position to start the game with it
    struct pos startpos;
    startpos.x=200.0f;
    startpos.y=350.0f;
    std::fstream dat;
    dat.open("data.bin", std::ios::binary | std::ios::in);
    if(!dat.is_open()){
        //create the thing
        std::cout<<"ustvarjam novo...\n";
        dat.close();
        dat.open("data.bin", std::ios::binary | std::ios::out);
        dat.write((char*)&startpos, sizeof(startpos));
        dat.write((char*)&score, sizeof(score));
        dat.write((char*)&highscore, sizeof(highscore));        
    }
    else {
        std::cout<<"berem\n";
        dat.read((char*)&startpos, sizeof(startpos));
        dat.read((char*)&score, sizeof(score));
        dat.read((char*)&highscore, sizeof(highscore));
    }
    dat.close();
    std::cout<<"player will start on location "<<startpos.x<<", "<<startpos.y<<'\n';
    if(score!=0)std::cout<<"the score from last time is "<<score;
    if(highscore!=0)std::cout<<" while the highscore is "<<highscore;
    std::cout<<'\n';
    game=new Game("trolley", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    game->init(startpos.x, startpos.y);
    while(game->running){
        framestart=SDL_GetTicks64();

        game->handleEvents();
        game->update();
        game->render();
        frameTime=SDL_GetTicks64()-framestart;
        if(frameDelay>frameTime)SDL_Delay(frameDelay-frameTime);
    }
    //save player position before we go, and the score as well
    score=game->getscore();
    for(game->ePointer=Entity::start;game->ePointer->label!=std::string("player")&&game->ePointer!=NULL;game->ePointer=game->ePointer->next);
    if(game->ePointer!=NULL)
    {   
        startpos.x=game->ePointer->physics->position.x;
        startpos.y=game->ePointer->physics->position.y;
        std::cout<<"i'll save the position ("<<startpos.x<<", "<<startpos.y<<")\n";
        dat.open("data.bin", std::ios::binary | std::ios::out);
        dat.write((char*)&startpos, sizeof(startpos));
        dat.write((char*)&score, sizeof(score));
        if(score>highscore){
            std::cout<<"cool a new high score i'll save that\n";
            dat.write((char*)&score, sizeof(score));
        }
        else dat.write((char*)&highscore, sizeof(highscore));
        dat.close();
    }
    game->clean();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}