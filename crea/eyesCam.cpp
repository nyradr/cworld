#include "eyesCam.h"

#include <GL/glut.h>
#include <cmath>

EyesCam::EyesCam(Vector3<float> &p, float &s) {
    this->pos = p;
    this->sensivity = s;
}

EyesCam::EyesCam(float x, float y, float z, float s) {
    this->pos = Vector3<float>(x, y, z);
    this->sensivity = s;
}


void EyesCam::setPos(Vector3<float> &p) {
    this->pos = p;
    pos.z +1;
}

void EyesCam::setPos(float x, float y, float z) {
    this->pos = Vector3<float>(x, y, z +1);
}

void EyesCam::onMouseMotion(const SDL_MouseMotionEvent &e) {
    theta -= e.xrel * sensivity;
    phi -= e.yrel * sensivity;

    calcTarget();
}

void EyesCam::calcTarget() {
    target.x = pos.x + cos(theta) * cos(phi);
    target.y = pos.y + sin(theta) * cos(phi);

    target.z = pos.z + sin(phi);
}

void EyesCam::look() {
    gluLookAt(pos.x, pos.y, pos.z, target.x, target.y, target.z, 0, 0, 1);
}