#pragma once
#include <cmath>

#define PI 2*acos(0.0)
#define power2(x) (x*x)


double radToDeg(double rad) { return rad / (PI / 180); }
double degToRad(double deg) { return deg * (PI / 180); }

float _round(float x){
    return std::floor(x+0.5);
}
