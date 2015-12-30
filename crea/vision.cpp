#include "vision.h"

#include "visionException.hpp"

#include "../math/math.hpp"

#include <iostream>

const int Vision::getVisonAt(Vector3<int> pos) {
    Vector3<int> abso = actualPos;
    abso -= pos;

    Vector3<int> rel = Vector3<int>(range, range, 0) + pos;

    std::vector<Vector3<int>> vfield = std::vector<Vector3<int>>();
    double hypo = hypot(rel.x, rel.y);    
    
    if (abso.x < 0 || abso.y < 0 || abso.x >= map->getSx() || abso.y >= map->getSy())
        throw VOutWEx; //out of world
    if (rel.x < 0 || rel.y < 0 || rel.x > 2 * range || rel.y > 2 * range)
        throw VUnavEx; //unaviable (out of range)


    if (pos.y != 0) {
        double theta = (pos.x != 0) ? atan((double)pos.y / (double)pos.x) : M_PI / 2; //angle du point regarder par rapport au centre
        if (rel.x < 0 && rel.y > 0)
            theta = M_PI - theta;
        else if (rel.x < 0 && rel.y < 0)
            theta = M_PI + theta;


        int jmp = (rel.x < range) ? -1 : 1;
        
        //recup des points de la droite (Centre, Point)
        for (int i = range; i != rel.x; i += jmp) {
            double nr = (hypo * abs(i - range)) / abs(rel.x - range); //rayon en i

            Vector3<int> v = Vector3<int>(i, round(sin(theta) * nr) + range, 0);
            v.z = vision[v.x][v.y];
            vfield.push_back(v);
        }
    } else {
        int jmp = (rel.y < range) ? -1 : 1;

        for (int j = range; j != rel.y; j += jmp) {
            Vector3<int> v = Vector3<int>(range, j, 0);
            v.z = vision[v.x][v.y];
            vfield.push_back(v);
        }
    }

    //test si le point est vu depuis le centre
    int center = vision[range][range];
    int val = vision[rel.x][rel.y];
    for (int i = 0; i < vfield.size(); i++) {
        if(m_linearInter(vfield[i].z, 0, center, abs(pos.x), val) < vfield[i].z)
            throw VUnavEx; //obstacle
    }

    return val;
}

const int Vision::getVisonAt(const int &x, const int &y) {
    Vector3<int> pos = Vector3<int>(x, y, 0);
    return getVisonAt(pos);
}

void Vision::actualize() {
    vision.clear();
    int x = actualPos.x - range, y = 0, center = map->getPt(actualPos.x, actualPos.y).z;

    for (int i = 0; i < 2 * range + 1; i++) {
        vision.push_back(std::vector<int>());

        y = actualPos.y - range;
        for (int j = 0; j < 2 * range + 1; j++) {
            if (x < 0 || y < 0 && x < map->getSx() && y < map->getSy())
                vision[i].push_back(0);
            else
                vision[i].push_back(map->getPt(x, y).z - center);

            y++;
        }
        x++;
    }
}