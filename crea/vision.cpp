#include "vision.h"

#include "visionException.hpp"

#include <cmath>

#include <iostream>

const int Vision::getVisonAt(Vector3<int> &pos) const throw() {    
    Vector3<int> abso = actualPos;
    abso -= pos;

    Vector3<int> rel = Vector3<int>(range, range, 0) + pos;

    std::vector<Vector3<int>> vfield = std::vector<Vector3<int>>();
    double hypo = hypot(rel.x, rel.y);
    
    if (abso.x < 0 || abso.y < 0 || abso.x >= map->getSx() || abso.y >= map->getSy()){
        throw VOutWEx;
        return -42;
    }
    
    if (rel.x < 0 || rel.y < 0 || rel.x > 2 * range || rel.y > 2 * range){
        throw VUnavEx;
        return -42;
    }
    
    if (pos.y != 0) {
        double theta = (pos.x != 0)? atan((double)pos.y / (double)pos.x) : M_PI / 2;
        if (rel.x < 0 && rel.y > 0)
            theta = M_PI - theta;
        else if (rel.x < 0 && rel.y < 0)
            theta = M_PI + theta;


        int jmp = (rel.x < range) ? -1 : 1;
        
        for (int i = range; i != rel.x; i += jmp) {
            double nr = (hypo * fabs(i - range)) / fabs(rel.x - range);

            Vector3<int> v = Vector3<int>(i, round(sin(theta) * nr), 0);
            v.z = vision[v.x][v.y];
            vfield.push_back(v);
        }
    } else{
        int jmp = (rel.y < range) ? -1 : 1;

        for (int j = range; j != rel.y; j += jmp) {
            double nr = (hypo * fabs(j - range)) / fabs(rel.y - range);

            Vector3<int> v = Vector3<int>(j, round(nr), 0);
            v.z = vision[v.x][v.y];
            vfield.push_back(v);
        }
    }
    
    int max = vision[range][range];
    for (int i = 0; i < vfield.size(); i++){
        if(vfield[i].z >= max)
            max = vfield[i].z;
        else
            std::cout << "I";
    }

    return vision[rel.x][rel.y];
}

const int Vision::getVisonAt(const int &x, const int &y) const throw() {
    Vector3<int> pos = Vector3<int>(x, y, 0);
    try {
        return getVisonAt(pos);
    }catch(std::exception &e){
        std::cout << "youpi" << e.what() << "\n";
    }
    
    return 0;
}

void Vision::actualize() {
    vision.clear();
    int x = actualPos.x - range, y = 0, center = map->getPt(actualPos.x, actualPos.y).z;

    for (int i = 0; i < 2 * range +1; i++) {
        if (x < 0) {
            x = 0;
            i -= x;
        }
        vision.push_back(std::vector<int>());

        y = actualPos.y - range;
        for (int j = 0; j < 2 * range +1; j++) {
            if (y < 0) {
                y = 0;
                i -= y;
            }
            
            vision[i].push_back(
                (y < map->getSy()) ? map->getPt(x, y).z - center : 0);
            y++;
        }
        x++;
    }
}