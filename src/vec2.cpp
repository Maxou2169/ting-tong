#include "includes/vec2.h"
#include <math.h>
#include <assert.h>

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

void Vec2::operator+=(Vec2 const & to_add)
{
    this->x += to_add.get_x();
    this->y += to_add.get_y();
}

bool Vec2::operator==(Vec2 const & to_compare) const
{
    return (this->x == to_compare.get_x() && this->y == to_compare.get_y());
}

void Vec2::operator-=(Vec2 const & to_add)
{
    this->x -= to_add.get_x();
    this->y -= to_add.get_y();
}

void Vec2::normalise()
{
    Vec2 old(this->get_x(), this->get_y());
    float norm = this->norm();
    if (norm == 0)
        return;
    this->set_x(this->get_x()/norm);
    this->set_y(this->get_y()/norm);
}

bool Vec2::test()
{
    Vec2 v0(14,11); // getters / setters
    assert(v0.get_x() == 14);
    assert(v0.get_y() == 11);
    v0.set_x(0);
    v0.set_y(6);
    assert(v0.get_x() == 0);
    assert(v0.get_y() == 6);
    
    Vec2 v00(0,6); // operator ==
    assert(v0 == v0);
    assert(v0 == v00);

    Vec2 v1(3,1); // opeator * float
    Vec2 v1_01 = v1 * 0.01;
    Vec2 v1_01_att = Vec2(0.03, 0.01);
    assert((v1_01.get_x() == v1_01_att.get_x()) && (v1_01.get_y() == v1_01_att.get_y()));
    
    Vec2 v2(1,2); // operator +
    Vec2 v3 = v1 + v2;
    Vec2 v3_att = Vec2(4,3);
    assert((v3.get_x() == v3_att.get_x()) && (v3.get_y() == v3_att.get_y()));

    Vec2 v4 = v3 - v1; // operator -
    assert((v4.get_x() == v2.get_x()) && (v4.get_y() == v2.get_y()));

    v4 += v1; // operator +=
    assert((v4.get_x() == v3.get_x()) && (v4.get_y() == v3.get_y()));

    v4 *= 0.5; // operator *=
    assert((v4.get_x() == v3.get_x() * 0.5) && (v4.get_y() == v3.get_y() * 0.5));
    return true;
}