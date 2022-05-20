#include "Vector2D.hpp"

Vector2D& Vector2D::operator+=(const Vector2D &v2){
    this->x+=v2.x;
    this->y+=v2.y;
    return *this;
}
Vector2D& Vector2D::operator*=(const float &i){
    this->x*=i;
    this->y*=i;
    return *this;
}
Vector2D& Vector2D::operator=(const Vector2D &v2){
    this->x=v2.x;
    this->y=v2.y;
    return *this;
}
void Vector2D::set(const float &x, const float &y){
    this->x=x;
    this->y=y;
}
std::ostream& operator<<(std::ostream& stream, const Vector2D& vec){
stream<<'('<<vec.x<<", "<<vec.y<<')';
return stream;
}