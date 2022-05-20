#pragma once
#include "Game.hpp"
#include "Components.hpp"

class Controller{
    public:
    static Physics *physicspointer;
    static bool jumping, ml, mr, md, arrL, arrR, arrU;
    static void update();
    ~Controller(){}
};