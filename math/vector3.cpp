#include "vector3.hpp"

#include <cmath>

template<class T>
Vector3<T>::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

template<class T>
Vector3<T>::Vector3(const T &x, const T &y, const T &z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template<class T>
double Vector3<T>::norme() {
    return sqrt(x * x + y * y + z * z);
}

template<class T>
void Vector3<T>::normalize() {
    double n = norme();
    x /= n;
    y /= n;
    z /= n;
}

template<class T>
Vector3<T> Vector3<T>::crossProduct(Vector3<T> &v) {
    return Vector3<T>(
        x * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x);
}

template<class T>
Vector3<T>& Vector3<T>::operator=(const Vector3<T> &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

template<class T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T> &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

template<class T>
Vector3<T> Vector3<T>::operator+(const Vector3<T> &v) {
    return Vector3<T>(x + v.x, y + v.y, z + v.z);
}

template<class T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T> &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

template<class T>
Vector3<T> Vector3<T>::operator-(const Vector3<T> &v) {
    return Vector3<T>(x - v.x, y - v.y, z - v.z);
}

template<class T>
Vector3<T>& Vector3<T>::operator*=(const Vector3<T> &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

template<class T>
Vector3<T> Vector3<T>::operator*(const Vector3<T> &v) {
    return Vector3<T>(x * v.x, y * v.y, z * v.z);
}

template<class T>
Vector3<T> Vector3<T>::operator*(const T &v){
    return Vector3<T>(x * v, y * v, z * v);
}

template<class T>
Vector3<T>& Vector3<T>::operator/=(const Vector3<T> &v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

template<class T>
Vector3<T> Vector3<T>::operator/(const Vector3<T> &v) {
    return Vector3<T>(x / v.x, y / v.y, z / v.z);
}