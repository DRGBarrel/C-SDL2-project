#include "PhysicsComponent.hpp"
#include <iostream>

Physics::Physics(float x, float y, int w, int h){
    this->other();
    position.set(x, y);
    collider.w=w;
    collider.h=h;
}
void Physics::other(){
    velocity.set(0.0f, 0.0f);
    gravity.set(0.0f, 1.0f);
    position.set(0.0f, 0.0f);
    acceleration.set(0.0f, 0.0f);
    collider.h=collider.w=64;
    drag=0.97f;
    grounded=pickup=false;
    jump=tbug=collider.x=collider.y=collisioncounter=0;
    lastpos.set(0.0f, 0.0f);
}
void Physics::update(){
        //turn off collisions if you're told
        if(collisioncounter>0){
            collisioncounter--;
        }
        if(collisioncounter<0){
            collisioncounter=0;
        }
        //save last position
        lastpos=position;
        //save absolute values of current velocity
        float velX;
        if(velocity.x>=0)velX=velocity.x;
        else velX=velocity.x*-1;
        //accelerate if not fast enough
        if(velX<=42.0f)velocity.x+=acceleration.x;
        velocity.y+=acceleration.y;
        //reduce acceleration just in case
        if(acceleration.x>0)acceleration.x-=0.1f;
        if(acceleration.x<0)acceleration.x+=0.1f;
        if(acceleration.y>0)acceleration.y-=0.1f;
        if(acceleration.y<0)acceleration.y+=0.1f;
        if(acceleration.x>-0.1f&&acceleration.x<0.1f)acceleration.x=0.0f;
        if(acceleration.y>-0.1f&&acceleration.y<0.1f)acceleration.y=0.0f;
        //unground the player 2 frames after bouncing off
        if(tbug==1){tbug=0;grounded=0;}
        if(tbug==2)tbug=1;
        //apply drag
        velocity*=drag;
        //apply gravity
        if(!grounded){velocity+=gravity;}
        //update position
        position+=velocity;
        //check if on the bottom
        if(position.y+collider.h>=512)grounded=1;
        //make sure player is on screen
        if(position.y+collider.h>512){
            position.y=512-collider.h;
            velocity.y*=-0.5f;
            grounded=1;
            tbug=2;
            if(velocity.y>=-1.0f){
                velocity.y=0;
            }
        }
        if(position.x+collider.w<0){position.x=800;}
        if(position.x>Game::screenwidth){position.x=-1-collider.w;}
        //set velocity to 0 if too small
        if(velocity.x<0.1f&&velocity.x>-0.1f)velocity.x=0;
        if(velocity.y<0.1f&&velocity.y>-0.1f)velocity.y=0;
        //set collider position
        collider.x=(int)position.x;
        collider.y=(int)position.y;
}