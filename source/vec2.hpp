#pragma once

struct Vec2{
    float x;
    float y;

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(const Vec2& other) const;
    Vec2 operator/(const Vec2& other) const;
    bool operator>(const Vec2& other) const;
    bool operator<(const Vec2& other) const;
    double dotProduct(const Vec2& other) const;
    double crossProduct(const Vec2& other) const;
    Vec2 rotate(const double th) const;
    Vec2 rotate(const double th, const Vec2& origin) const;
    float length() const;
    Vec2 round() const;
};
