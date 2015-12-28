#ifndef INC_POINT
#define INC_POINT

/* Représente un point sur la carte
*/
class MPoint{
    
public:
    
    int z;
    double w;
    
    MPoint(){}
    MPoint(int z, double w = 0){
        this->z = z;
        this->w = w;
    }
    
};

#endif