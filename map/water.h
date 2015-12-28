#ifndef INC_WATER
#define INC_WATER

#include "point.h"

#include <vector>

class Water{
    
public:
    
    Water(MPoint** map, const unsigned int sx, const unsigned int sy, const double ecoul);
    
    void addSource();
    
private:
    
    unsigned int sx;
    unsigned int sy;
    
    MPoint** map;
    double ecoul;
    
    std::vector<std::pair<int, int>> getGrad(int x, int y);
    
    void ecoulPt(int x, int y, double w);
};

#endif