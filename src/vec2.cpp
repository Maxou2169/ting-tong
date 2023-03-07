#include "includes/vec2.h"
#include <math.h>

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(float x, float y) : x(x), y(y) {}
Vec2::~Vec2() {}

float Vec2::get_x() const
{
    return this->x;
}

float Vec2::get_y() const
{
    return this->y;
}

void Vec2::set_x(float x)
{
    this->x = x;
}

void Vec2::set_y(float y)
{
    this->y = y;
}

float Vec2::norm() const
{
    return sqrt(this->x * this->x + this->y * this->y);
}

Vec2 Vec2::operator+(Vec2 const &to_add) const
{
    Vec2 ret(this->x + to_add.get_x(), this->y + to_add.get_y());
    return ret;
}

Vec2 Vec2::operator-(Vec2 const &to_add) const
{
    Vec2 ret(this->x - to_add.get_x(), this->y - to_add.get_y());
    return ret;
}

Vec2 Vec2::operator*(Vec2 const &to_add) const
{
    Vec2 ret((this->x * to_add.get_x()) - (this->y * to_add.get_y()),
             (this->x - to_add.get_y()) + (this->y - to_add.get_x()));
    return ret;
}

Vec2 Vec2::operator*(const float f) const
{
    Vec2 ret(this->x * f, this->y * f);
    return ret;
}

void Vec2::operator*=(const float f)
{
    this->x *= f;
    this->y *= f;
}

bool test()
{
    return true;
}