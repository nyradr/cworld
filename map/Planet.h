#ifndef INC_PLANET
#define INC_PLANET

#include "point.h"
#include "../drawgl.h"

class Planet : public DrawGl{
    
public:
    
    Planet(float radius, float var, unsigned int prec);
    ~Planet();
    
    void generate(int seed);
    void generate();
    
private:
    
    int seed;
    
    int prec;
    float radius;
    float var;
    float delta;
    
    MPoint** map;
    
    void gen_liss();
    
    void gen_uniformPole();
    void _gen_uniformPole(int j);
    
    void gen_gl();
};

#endif