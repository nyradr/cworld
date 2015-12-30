#ifndef INC_VISION_EXCEP
#define INC_VISION_EXCEP

#include <exception>

class VisionUnavailableException : public std::exception{
    
public:
    
    virtual const char* what() const throw(){
        return "Vision unavailable";
    }
} VUnavEx;

class VisionOutOfWorldException : public std::exception{
    
public :
    
    virtual const char* what() const throw(){
        return "Vision out of world";
    }
    
} VOutWEx;

#endif