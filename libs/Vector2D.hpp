#pragma once
#include <iostream>

class Vector2D{
    public:
    float x, y;
    Vector2D(){
        x=y=0.0f;
    }
    Vector2D(float x, float y){
        this->x=x;
        this->y=y;
    }
    Vector2D& operator+=(const Vector2D &v2);
    Vector2D& operator*=(const float &i);
    Vector2D& operator=(const Vector2D &v2);
    void set(const float &x, const float &y);
    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
    ~Vector2D(){}
};