#ifndef INC_VISION
#define INC_VISION

#include "../map/map.h"
#include "../math/vector3.hpp"

#include <vector>

class Vision{

public:
    
    Vision(Map* map, unsigned int range){
        this->map = map;
        this->range = range;
    }
    
    void setRange(const unsigned int &range){this->range = range;}
    void setPos(Vector3<int> pos){this->actualPos = pos;}
    void setMap(Map* map, const bool del = false){
        if(del)
            delete this->map;
        this->map = map;
    }
    
    const unsigned int& getRange(){return range;}
    const Vector3<int>& getPos(){return actualPos;}
    
    //position relative, vision relative
    const int getVisonAt(Vector3<int> &pos) const throw();     
    const int getVisonAt(const int &x, const int &y) const throw();
    
    void actualize();
    void actualize(Vector3<int> &pos){
        setPos(pos);
        actualize();
    }
    void actualize(const int &x, const int &y){
        setPos(Vector3<int>(x, y, 0));
        actualize();
    }
    
private:
    
    Vector3<int> actualPos;
    std::vector<std::vector<int>> vision;     //relative à la position
    
    unsigned int range;
    Map* map;
    
    
    
};

#endif