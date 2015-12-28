#include "Planet.h"

#include <cmath>
#include <vector>
#include <cstdlib>

#include <iostream>

#include "../znoise/Perlin.hpp"

Planet::Planet(float radius, float var, unsigned int prec) {
    this->radius = radius;
    this->var = var;
    this->prec = 2 * prec;
    this->delta = M_PI / prec;

    this->map = new MPoint *[this->prec];
    for (uint i = 0; i < this->prec; i++)
        this->map[i] = new MPoint[this->prec];
}

Planet::~Planet() {
    for (uint i = 0; i < this->prec; i++)
        delete map[i];
    delete map;
}

void Planet::generate() {
    generate(rand());
}

void Planet::generate(int seed) {
    this->seed = seed;

    Perlin perl = Perlin(seed);

    float thetax = 0, thetay = delta * (prec / 4);

    for (uint i = 0; i < prec; i++) {
        thetay = delta * (prec / 4);
        for (uint j = 0; j < prec / 2; j++) {
            float r = radius + perl.Get({(float)cos(thetax) * radius, (float)sin(thetay) * radius}, 0.1f) * var;
            map[i][j].z = (int)r;
            thetay += delta;
        }
        thetax += delta;
    }

    for (int i = 0; i < 3; i++) {
        gen_liss();
        gen_uniformPole();
    }
    gen_gl();
}

void Planet::gen_liss() {
    for (uint i = 0; i < prec; i++)
        for (uint j = 0; j < prec / 2; j++) {
            int moy = map[i][j].z;

            moy += (i > 0) ? map[i - 1][j].z : map[prec / 2 - 1][j].z;
            moy += (i + 1 < prec) ? map[i + 1][j].z : map[0][j].z;
            moy += (j > 0) ? map[i][j - 1].z : map[i][prec / 2 - 1].z;
            moy += (j + 1 < prec / 2) ? map[i][j + 1].z : map[i][0].z;

            map[i][j].z = moy / 5;
        }
}

void Planet::gen_uniformPole() {
    _gen_uniformPole(0);
    _gen_uniformPole(prec - 1);
}
void Planet::_gen_uniformPole(int j) {
    int val = 0;

    for (uint i = 0; i < prec; i++)
        val += map[i][j].z;
    val /= prec;

    for (uint i = 0; i < prec; i++)
        map[i][j].z = val;
}

void Planet::gen_gl() {
    newList();

    glNewList(dl_index, GL_COMPILE);

    glBegin(GL_QUADS);

    float ax = 0, nax;
    float ay = delta * (prec / 4), nay;

    for (uint i = 0; i < prec; i++) {
        nax = ax + delta;
        ay = delta * (prec / 4);
        for (uint j = 0; j < prec / 2; j++) {
            nay = ay + delta;

            const int &z1 = map[i][j].z;
            const int &z2 = (j + 1 < prec / 2) ? map[i][j + 1].z : map[0][0].z;

            //const int &z3 = (j + 1 < prec / 2 && i + 1 < prec) ? map[i + 1][j + 1].z : map[0][0].z;
            int tz2 = 0;
            if (i + 1 < prec) {
                if (j + 1 < prec / 2)
                    tz2 = map[i + 1][j + 1].z;
                else
                    tz2 = map[i + 1][0].z;
            } else {
                if (j + 1 < prec / 2)
                    tz2 = map[0][j + 1].z;
                else
                    tz2 = map[0][0].z;
            }
            const int &z3 = tz2;


            const int &z4 = (i + 1 < prec) ? map[i + 1][j].z : map[0][j].z;

            float col[4] = {
                (z1 - radius + (var / 2)) * 255 / var,
                (z2 - radius + (var / 2)) * 255 / var,
                (z3 - radius + (var / 2)) * 255 / var,
                (z4 - radius + (var / 2)) * 255 / var};

            double pts[12] = {
                cos(ax) * (cos(ay) * z1), sin(ax) * (cos(ay) * z1), sin(ay) * z1,
                cos(nax) * (cos(ay) * z4), sin(nax) * (cos(ay) * z4), sin(ay) * z4,
                cos(nax) * (cos(nay) * z3), sin(nax) * (cos(nay) * z3), sin(nay) * z3,
                cos(ax) * (cos(nay) * z2), sin(ax) * (cos(nay) * z2), sin(nay) * z2};

            glColor3ub(col[0], 0, 0);
            glVertex3d(pts[0], pts[1], pts[2]);

            glColor3ub(col[3], 0, 0);
            glVertex3d(pts[3], pts[4], pts[5]);

            glColor3ub(col[2], 0, 0);
            glVertex3d(pts[6], pts[7], pts[8]);

            glColor3ub(col[1], 0, 0);
            glVertex3d(pts[9], pts[10], pts[11]);

            ay = nay;
        }
        ax = nax;
    }

    glEnd();
    glEndList();
}