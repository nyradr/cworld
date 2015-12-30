#include "math.hpp"

#include <cmath>

float m_linearInter(float c, float a, float fa, float b, float fb){
    return fa + (c - a) * ((fb - fa) / (b - a));
}