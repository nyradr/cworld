#ifndef INC_CIRCLE
#define INC_CIRCLE

#include <cmath>

double cosDeg(double a){
    return cos(a * M_PI / 180.f);
}

double sinDeg(double a){
    return sin(a * M_PI / 180.f);
}


class Circle{

public :
    
    Circle(int cx, int cy, int r){
        this->cx = cx;
        this->cy = cy;
        this->r = r;
    }
    
    int getMinX(){return cx - r;}
    int getMinY(){return cy - r;}
    int getMaxX(){return cx + r;}
    int getMaxY(){return cy + r;}
    
    int absX(double c){return (c * r) + cx;}
    int absY(double s){return (s * r) + cy;}
    
    double relX(int x){return (x - cx) / r;}
    double relY(int y){return (y - cy) / r;}
    
    
    
    
private:
    
    int cx;
    int cy;
    int r;
    
};

#endif