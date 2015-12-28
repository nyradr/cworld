#ifndef INC_MAP
#define INC_MAP

#include "../drawgl.h"
#include "point.h"


#include <vector>

class Map : public DrawGl{
    
public:
    
    Map(const unsigned int sx, const unsigned int sy, const int min, const int max);
    ~Map();
    
    void generate(int seed);
    void generate();
    
    int getSx(){return sx;}
    int getSy(){return sy;}
    int getSeed(){return seed;}
    int altMoy();
    int diffZ(int x1, int y1, int x2, int y2);
    
    MPoint& getPt(const unsigned int x, const unsigned int y){return map[x][y];}
    
private:
    
    unsigned int sx;
    unsigned int sy;
    int max;
    int min;
    
    MPoint** map;
    int seed;
    
    std::vector<GLuint> dli_water;
    
    virtual void gen_gl();
    
    //generation
    void gen_base();
    void gen_mountain(int x, int y, int r, int p);
    void gen_liss();
};


#endif