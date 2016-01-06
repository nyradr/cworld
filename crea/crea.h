#ifndef INC_CREA
#define INC_CREA

#include "../drawgl.h"
#include "../math/vector3.hpp"
#include "../map/map.h"

#include "vision.h"
#include "eyesCam.h"

class Crea : public DrawGl{
    
public:
    
    Crea(Map *map);
    
    void spawn();
    bool move(int mvmt);
    void setPos(int x, int y){pos.x = x; pos.y = y;}    
    
    EyesCam& getCam(){return cam;}
    
    Vision vision;
    
    void vact(){
        vision.actualize(pos);
    }
    
private:
    
    Map *map;
    
    EyesCam cam;
    
    Vector3<int> pos;
    Vector3<int> target;
    
    
    void gen_gl();
    
};

#endif