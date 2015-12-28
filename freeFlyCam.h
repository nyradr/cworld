#include "math/vector3.hpp"
#include <GL/glut.h>
#include <SDL/SDL.h>
#include <map>

class FreeFlyCam
{

public:
    FreeFlyCam(const Vector3<double> &position = Vector3<double>(0, 0, 0));

    virtual void OnMouseMotion(const SDL_MouseMotionEvent &event);
    virtual void OnMouseButton(const SDL_MouseButtonEvent &event);
    virtual void OnKeyboard(const SDL_KeyboardEvent &event);

    virtual void animate(Uint32 timestep);
    virtual void setSpeed(double speed){_speed = speed;}
    virtual void setSensivity(double sensivity){_sensivity = sensivity;}

    virtual void setPosition(const Vector3<double> &position){_position = position;}

    virtual void look();

    virtual ~FreeFlyCam();


protected:
    double _speed;
    double _sensivity;

    Uint32 _timeBeforeStoppingVerticalMotion;
    bool _verticalMotionActive;
    int _verticalMotionDirection;


    typedef std::map<SDLKey, bool> KeyStates;
    KeyStates _keystates;
    typedef std::map<std::string, SDLKey> Keyconf;
    Keyconf _keyconf;


    Vector3<double> _position;
    Vector3<double> _target;
    Vector3<double> _forward;
    Vector3<double> _left;

    double _theta;
    double _phi;


    void VectorsFromAngles();
};