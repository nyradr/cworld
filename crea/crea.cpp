#include "crea.h"

#include <cstdlib>

#include <iostream>

Crea::Crea(Map *map) {
    this->map = map;
}

void Crea::spawn() {
    pos = Vector3<int>(rand() % map->getSx(),
                       rand() % map->getSy(),
                       0);
    pos.z = map->getPt(pos.x, pos.z).z;
    gen_gl();
}

bool Crea::move(int mvmt) {
    bool ret = false;

    switch (mvmt) {
    case 0: //up
        if ((ret = pos.y < map->getSy()))
            pos.y++;
        break;

    case 1: //down
        if ((ret = pos.y > 0))
            pos.y--;
        break;
        
    case 2: //left
        if((ret = pos.x < map->getSx()))
            pos.x++;
        break;
        
    case 3: //right
        if((ret = pos.x > 0))
            pos.x--;
        break;
    }
    
    if(ret){
        pos.z = map->getPt(pos.x, pos.y).z +1;
        gen_gl();
    }
    return ret;
}


void Crea::gen_gl() {
    newList();

    glNewList(dl_index, GL_COMPILE);
    glBegin(GL_QUADS);

    glColor3ub(255, 255, 255);
    glVertex3d(pos.x, pos.y, pos.z);
    glVertex3d(pos.x, pos.y + 1, pos.z);
    glVertex3d(pos.x + 1, pos.y + 1, pos.z);
    glVertex3d(pos.x + 1, pos.y, pos.z);

    glEnd();
    glEndList();
}