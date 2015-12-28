#ifndef INC_VECTOR3
#define INC_VECTOR3

#include <vector>
#include <cmath>

template <typename T>
class Vector3 {

public:
    T x;
    T y;
    T z;


    Vector3() {
        x = 0;
        y = 0;
        z = 0;
    }
    Vector3(const T &x, const T &y, const T &z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double norme() {
        return sqrt(x * x + y * y + z * z);
    }

    void normalize() {
        double n = norme();
        x /= n;
        y /= n;
        z /= n;
    }
    
    Vector3<T> crossProduct(Vector3<T> &v) {
        return Vector3<T>(
            x * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
    }

    Vector3 &operator=(const Vector3<T> &v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    Vector3 &operator+=(const Vector3<T> &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3 operator+(const Vector3<T> &v) {
        return Vector3<T>(x + v.x, y + v.y, z + v.z);
    }

    Vector3 &operator-=(const Vector3<T> &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3 operator-(const Vector3<T> &v) {
        return Vector3<T>(x - v.x, y - v.y, z - v.z);
    }

    Vector3 &operator*=(const Vector3<T> &v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    Vector3 operator*(const Vector3<T> &v) {
        return Vector3<T>(x * v.x, y * v.y, z * v.z);
    }

    Vector3 operator*(const T &v){
        return Vector3<T>(x * v, y * v, z * v);
    }

    Vector3 &operator/=(const Vector3<T> &v) {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    Vector3 operator/(const Vector3<T> &v) {
        return Vector3<T>(x / v.x, y / v.y, z / v.z);
    }

    
};


#endif