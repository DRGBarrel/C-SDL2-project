#include "Collision.hpp"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB){
    if(
        recA.x+recA.w>=recB.x&&
        recB.x+recB.w-1>=recA.x&&
        recA.y+recA.h>=recB.y&&
        recB.y+recB.h>=recA.y
    ){return true;}
    return false;
}
bool Collision::AABB(const Physics& colA, const Physics& colB){
    if(AABB(colA.collider, colB.collider)){
        return true;
    }
    else return false;
}
float Collision::collisiondistanceX(const SDL_Rect& recA, const SDL_Rect& recB){
    if(recA.x+recA.w-recB.x>recA.w)return recB.x+recB.w-recA.x;
    else return recA.x+recA.w-recB.x;
}
float Collision::collisiondistanceY(const SDL_Rect& recA, const SDL_Rect& recB){
    if(recA.y+recA.h-recB.y>recA.h)return recB.y+recB.h-recA.y;
    else return recA.y+recA.h-recB.y;
}
void Collision::resolveCollision(Physics& pA, Physics& pB){
    if((pB.label!=std::string("player")&&pA.collisioncounter<29)||(pB.label==std::string("player")&&pA.collisioncounter==0))
    {   
        float distX=collisiondistanceX(pA.collider, pB.collider)
        , distY=collisiondistanceY(pA.collider, pB.collider);
        if(distX<distY)
        {
            pA.velocity.x*=-0.5f;
            if(pA.velocity.x<1.0f&&pA.velocity.x>-1.0f)
                pA.velocity.x=0.0f;
            if(pA.lastpos.x<pB.position.x){
                pA.position.x=pB.position.x-pA.collider.w;
            }
            else {
                pA.position.x=pB.position.x+pB.collider.w;
            }
        }
        else {
            if(pA.lastpos.y>pB.position.y){
                pA.position.y=pB.position.y+pB.collider.h;
                if(pA.velocity.y<0)pA.velocity.y=0;
            }
            else{
                pA.position.y=pB.position.y-pA.collider.h;
                pA.velocity.y*=-0.5f;
                pA.grounded=1;
                pA.tbug=2;
                if(pA.velocity.y>=-1.0f){
                    pA.velocity.y=0;
                }
            }
        }
    }
    if(pB.pickup)pA.collisioncounter=30;
}
