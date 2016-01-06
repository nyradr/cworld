#ifndef INC_EYECAM
#define INC_EYECAM

#include "../math/vector3.hpp"

#include <SDL/SDL.h>

class EyesCam{
    
public:
    
    EyesCam(Vector3<float> &p, float &s);
    EyesCam(float x, float y, float z, float s);
    
    void setPos(Vector3<float> &p);
    void setPos(float x, float y, float z);
    void onMouseMotion(const SDL_MouseMotionEvent &e);
    
    void look();
    
private:
    
    float sensivity;
    
    Vector3<float> pos;
    Vector3<float> target;
    float theta;
    float phi;
    
    void calcTarget();
};

#endif