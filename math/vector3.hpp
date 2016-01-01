#ifndef INC_VECTOR3
#define INC_VECTOR3


template <typename T>
class Vector3 {

public:
    T x;
    T y;
    T z;

    Vector3();
    Vector3(const T &x, const T &y, const T &z);

    double norme();

    void normalize();
    
    Vector3<T> crossProduct(Vector3<T> &v);

    Vector3 &operator=(const Vector3<T> &v);

    Vector3 &operator+=(const Vector3<T> &v);

    Vector3 operator+(const Vector3<T> &v);

    Vector3 &operator-=(const Vector3<T> &v);

    Vector3 operator-(const Vector3<T> &v);

    Vector3 &operator*=(const Vector3<T> &v);

    Vector3 operator*(const Vector3<T> &v);

    Vector3 operator*(const T &v);

    Vector3 &operator/=(const Vector3<T> &v);

    Vector3 operator/(const Vector3<T> &v);

};


#endif