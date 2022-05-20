#include "Entity.hpp"
#include "Components.hpp"

Entity *Entity::start=NULL;

Entity::Entity(){
    this->other();
    this->addToPList();
}
void Entity::init(float x, float y, int w, int h, const char* spritepath, const char* label){
    physics=new Physics(x, y, w, h);
    sp=new SpriteComponent(spritepath);
    this->label=label;
    physics->label=label;
}
void Entity::addToPList(){
    next=NULL;
    if(start!=NULL)
        next=start;
    start=this;
}
void Entity::other(){
    physics=nullptr;
    sp=nullptr;
    label="";
    next=nullptr;
}
void Entity::update(){
    physics->update();
}
void Entity::render(){
    SDL_RenderCopy(Game::renderer, sp->tex, NULL, &physics->collider);
}