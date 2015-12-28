#ifndef INC_VISION
#define INC_VISION

#include "../map/map.h"
#include "../math/vector3.hpp"

#include <vector>

class Vision{

public:
    
    Vision(Map* map, unsigned int &range);
    
    void setRange(unsigned int &range);
    void setPos(Vector3<int> &pos);
    void setMap(Map* map, bool del = false);
    
    const unsigned int& getRange();
    const Vector3<int>& getPos();
    const int getVisonAt(const Vector3<int> &pos);     //position relative, vision relative
    const int getVisonAt(const int &x, const int &y);
    
    void actualize();
    void actualize(const Vector3<int> &pos);
    void actualize(const int &x, const int &y);
    
private:
    
    Vector3<int> actualPos;
    std::vector<std::vector<int>> vision;     //relative à la position
    
    unsigned int range;
    Map* map;
};

#endif