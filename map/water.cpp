#include "water.h"

#include <cstdlib>
#include <vector>
#include <algorithm>

Water::Water(MPoint **map, const unsigned int sx, const unsigned int sy, const double ecoul) {
    this->map = map;
    this->sx = sx;
    this->sy = sy;
    this->ecoul = ecoul;
}

void Water::addSource() {
    int x = rand() % sx;
    int y = rand() % sy;
    double w = 1;

    ecoulPt(x, y, w);
}

void Water::ecoulPt(int x, int y, double w) {
    if (w > 0 && map[x][y].w == 0) {
        map[x][y].w = w;

        std::vector<std::pair<int, int>> grad = getGrad(x, y);

        for (int i = 0; i < grad.size(); i++)
            ecoulPt(grad[i].first, grad[i].second, w - ecoul);
    }
}

std::vector<std::pair<int, int>> Water::getGrad(int x, int y) {
    std::vector<std::pair<int, int>> grad = std::vector<std::pair<int, int>>();
    std::vector<MPoint *> zgrad = std::vector<MPoint *>();

    std::vector<std::pair<int, int>> ret = std::vector<std::pair<int, int>>();

    MPoint &pt = map[x][y];


    if (x > 0) {
        grad.push_back(std::pair<int, int>(x - 1, y));
        zgrad.push_back(&map[x - 1][y]);
    }

    if (x + 1 < sx) {
        grad.push_back(std::pair<int, int>(x + 1, y));
        zgrad.push_back(&map[x + 1][y]);
    }

    if (y > 0) {
        grad.push_back(std::pair<int, int>(x, y - 1));
        zgrad.push_back(&map[x][y - 1]);
    }

    if (y + 1 < sy) {
        grad.push_back(std::pair<int, int>(x, y + 1));
        zgrad.push_back(&map[x][y + 1]);
    }

    if (grad.size() > 0) {
        MPoint *min = zgrad[0];

        for (int i = 0; i < zgrad.size(); i++) {
            if (zgrad[i]->z <= pt.z) {
                if (zgrad[i]->z < min->z) {
                    ret.clear();
                    ret.push_back(grad[i]);
                } else if (zgrad[i]->z == min->z)
                    ret.push_back(grad[i]);
            }
        }
    }

    return ret;
}
