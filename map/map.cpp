#include "map.h"

#include <cstdlib>
#include <cmath>

#include <iostream>

#include "../znoise/Simplex.hpp"
#include "../znoise/Perlin.hpp"
#include "../znoise/Worley.hpp"
#include "../znoise/FBM.hpp"

#include "../math/vector3.hpp"

#include "water.h"


Map::Map(const unsigned int sx, const unsigned int sy, const int min, const int max)
    : DrawGl() {
    this->sx = sx;
    this->sy = sy;
    this->dl_index = 0;
    this->max = max;
    this->min = min;

    map = new MPoint *[sx];
    for (uint i = 0; i < sx; i++) {
        map[i] = new MPoint[sy];
        for (uint j = 0; j < sy; j++)
            map[i][j] = MPoint();
    }
}

Map::~Map() {
    for (uint i = 0; i < sx; i++)
        delete map[i];
    delete map;
}

int Map::altMoy() {
    int moy = 0;
    for (uint i = 0; i < sx; i++)
        for (uint j = 0; j < sy; j++)
            moy += map[i][j].z;
    return moy / (sx * sy);
}

int Map::diffZ(int x1, int y1, int x2, int y2) {
    return abs(map[x1][y1].z - map[x2][y2].z);
}

void Map::generate(int seed) {
    this->seed = seed;
    srand(seed);

    gen_base();
    
    for (int i = 0; i < 2; i++) {
        gen_mountain(rand() % sx, rand() % sy, (sx + sy) / 8, 12);
    }

    for (int i = 0; i < 2; i++)
        gen_liss();

    Water water = Water(map, sx, sy, 0.01);
    for (int i = 0; i < (sx / sy) * 2; i++)
        water.addSource();

    gen_gl();
}
void Map::generate() {
    srand(time(NULL));
    generate(rand());
}

void Map::gen_base() {
    Worley n = Worley(seed);
    FBM noise(n);

    for (int i = 0; i < sx; i++) {
        for (int j = 0; j < sy; j++) {
            double s = (noise.Get({(float)i, (float)j}, 0.1f) + 1) / 2;
            map[i][j].z = min + (s * (max - min));
        }
    }
}

void Map::gen_mountain(int x, int y, int r, int p) {
    Vector3<int> center = Vector3<int>(x, y, 0);
    Vector3<int> pos = Vector3<int>();
    Perlin perlin = Perlin(seed);
    /*
    float delta = M_PI / p;

    for(float theta = 0; theta < 2 * M_PI; theta += delta){
        int nr = perlin.Get({theta, 0}, 0.3f) * r;
        
        pos.x = center.x + cos(theta) * nr;
        pos.y = center.y + sin(theta) * nr;
        
        if(pos.x >= 0 && pos.x < sx && pos.y >= 0 && pos.y < sy)
            map[pos.x][pos.y].z = max;
    }*/

    for (pos.x = x - r; pos.x < x + r && pos.x < sx; pos.x++) {
        if (pos.x < 0)
            pos.x = 0;

        for (pos.y = y - r; pos.y < y + r && pos.y < sy; pos.y++) {
            if (pos.y < 0)
                pos.y = 0;

            if ((center - pos).norme() < r) {

                int &z = map[pos.x][pos.y].z;
                int rp = min + ((perlin.Get({pos.x, pos.y}, .09f) + 1) / 2) * max;

                z = (z + rp) / 2;
            }
        }
    }
}

void Map::gen_liss() {
    for (uint i = 0; i < sx; i++)
        for (uint j = 0; j < sy; j++) {
            int moy = map[i][j].z;

            if (i > 0)
                moy = (moy + map[i - 1][j].z) / 2;
            if (i + 1 < sx)
                moy = (moy + map[i + 1][j].z) / 2;

            if (j > 0)
                moy = (moy + map[i][j - 1].z) / 2;
            if (j + 1 < sy)
                moy = (moy + map[i][j + 1].z) / 2;

            map[i][j] = moy;
        }
}


void Map::gen_gl() {
    newList();

    int startx = 0, starty = 0, sqsize = 1;

    glNewList(dl_index, GL_COMPILE);

    glBegin(GL_QUADS);

    for (uint i = 0; i < sx; i++) {
        for (uint j = 0; j < sy; j++) {
            double pts[4] = {
                /*0*/ (startx + i) * sqsize, /*1*/ (startx + i + 1) * sqsize,
                /*2*/ (starty + j) * sqsize, /*3*/ (starty + j + 1) * sqsize};
            int z = map[i][j].z;
            int nz = z;

            double col = map[i][j].z * 255 / max;

            dglSetColor(col, 0, 0);
            glVertex3d(pts[0], pts[2], z);
            glVertex3d(pts[0], pts[3], z);
            glVertex3d(pts[1], pts[3], z);
            glVertex3d(pts[1], pts[2], z);


            //left
            if (i == 0)
                nz = 0;
            else if (map[i - 1][j].z < z)
                nz = map[i - 1][j].z;
            if (nz != z) {
                glColor3ub(0, col, 0);
                glVertex3d(pts[0], pts[2], z);
                glVertex3d(pts[0], pts[2], nz);
                glVertex3d(pts[0], pts[3], nz);
                glVertex3d(pts[0], pts[3], z);
            }

            //right
            nz = z;
            if (i == sx - 1)
                nz = 0;
            else if (map[i + 1][j].z < z)
                nz = map[i + 1][j].z;
            if (nz < z) {
                glColor3ub(col, col, 0);
                glVertex3d(pts[1], pts[2], z);
                glVertex3d(pts[1], pts[2], nz);
                glVertex3d(pts[1], pts[3], nz);
                glVertex3d(pts[1], pts[3], z);
            }

            //front
            nz = z;
            if (j == sy - 1)
                nz = 0;
            else if (map[i][j + 1].z < z)
                nz = map[i][j + 1].z;
            if (nz < z) {
                glColor3ub(col, 0, col);
                glVertex3d(pts[0], pts[3], z);
                glVertex3d(pts[0], pts[3], nz);
                glVertex3d(pts[1], pts[3], nz);
                glVertex3d(pts[1], pts[3], z);
            }
            //back
            nz = z;
            if (j == 0)
                nz = 0;
            else if (map[i][j - 1].z < z)
                nz = map[i][j - 1].z;
            if (nz < z) {
                glColor3ub(0, col, col);
                glVertex3d(pts[0], pts[2], z);
                glVertex3d(pts[0], pts[2], nz);
                glVertex3d(pts[1], pts[2], nz);
                glVertex3d(pts[1], pts[2], z);
            }

            if (map[i][j].w > 0) {
                double &w = map[i][j].w;
                int &z = map[i][j].z;
                int col = 255;

                glColor3ub(0, 0, col);
                glVertex3d(i, j, z + w);
                glVertex3d(i, j + 1, z + w);
                glVertex3d(i + 1, j + 1, z + w);
                glVertex3d(i + 1, j, z + w);
            }
        }
    }
    glEnd();
    glEndList();
}