#include <structure.h>
#include "asserts.h"

void Structure::create(int w, int h) {
    mapData.resize(w*h);
    this->w = w;
    this->h = h;
    for (auto &e:mapData) {e={};};
}

Block &Structure::getBlockUnsafe(int x, int y) {
    permaAssertCommentDevelopement(x >= 0 && y>=0 && x < w && y < h,"getblockunsafe out of bounds error"); //check for false
    permaAssertCommentDevelopement(mapData.size() == w*h,"Map not initialized");
    return mapData[x+y*w];
}

Block *Structure::getBlockSafe(int x, int y) {
    //permaAssertCommentDevelopement(x >= 0 && y>=0 && x < w && y < h,"getblockunsafe out of bounds error"); //check for false
    permaAssertCommentDevelopement(mapData.size() == w*h,"Map not initialized");
    if (x < 0 || y < 0 || x >= w || y >= h) return nullptr;

    return &mapData[x+y*w];

}
