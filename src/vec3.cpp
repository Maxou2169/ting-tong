#include "includes/vec3.h"
#include <math.h>

Vec3::Vec3() : x(0), y(0) {}
Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
Vec3::~Vec3() {}

float Vec3::get_x() const
{
    return this->x;
}

float Vec3::get_y() const
{
    return this->y;
}

void Vec3::set_x(float x)
{
    this->x = x;
}

void Vec3::set_y(float y)
{
    this->y = y;
}

float Vec3::norm() const
{
    return sqrt(this->x * this->x + this->y * this->y);
}

Vec3 Vec3::operator+(Vec3 const &to_add) const
{
    Vec3 ret(this->x + to_add.get_x(), this->y + to_add.get_y(), this->z + to_add.get_z());
    return ret;
}

Vec3 Vec3::operator-(Vec3 const &to_add) const
{
    Vec3 ret(this->x - to_add.get_x(), this->y - to_add.get_y(), this->z - to_add.get_z());
    return ret;
}

Vec3 Vec3::operator*(const float f) const
{
    Vec3 ret(this->x * f, this->y * f, this->z * f);
    return ret;
}

void Vec3::operator*=(const float f)
{
    this->x *= f;
    this->y *= f;
    this->z *= f;
}

bool test()
{
    return true;
}