#include <cmath>
#include "vec2.hpp"
#include "utils.hpp"


Vec2 Vec2::operator+(const Vec2& other) const{
    return (Vec2){x+other.x, y+other.y};
}

Vec2 Vec2::operator-(const Vec2& other) const{
    return (Vec2){x-other.x, y-other.y};
}

Vec2 Vec2::operator*(const Vec2& other) const{
    return (Vec2){x*other.x, y*other.y};
}

Vec2 Vec2::operator/(const Vec2& other) const{
    return (Vec2){x/other.x, y/other.y};
}

bool Vec2::operator>(const Vec2& other) const{
    if ((x*y) > (other.x*other.y))
        return true;
    return false;
}

bool Vec2::operator<(const Vec2& other) const{
    return !operator>(other);
}

double Vec2::dotProduct(const Vec2& other) const{
    return x*other.x+y*other.y;
}

double Vec2::crossProduct(const Vec2& other) const{
    return x+other.x*y+other.y;
}

Vec2 Vec2::rotate(const double th) const{

    if (!th%360)
        return *this;

    const double rad = degToRad(360-th);

    Vec2 result;

    result.x = std::cos(rad) * this->x - std::sin(rad) * this->y;
    result.y = std::sin(rad) * this->x + std::cos(rad) * this->y;

    return result;
}

Vec2 Vec2::rotate(const double th, const Vec2& origin) const{
    Vec2 newPoint = *this - origin;

    return newPoint.rotate(th)+origin;
}

float Vec2::length() const{
    return std::sqrt(power2(x) + power2(y));
}

Vec2 Vec2::round() const{
    Vec2 result = {_round(x), _round(y)};

    return result;
}
