#include <gameMap.h>
#include <asserts.h>

void GameMap::create(int w, int h) {
    *this = {};
    mapData.resize(w*h);
    this->w = w;
    this->h = h;
    for (auto &it : mapData) {
        it = {};
    }
}

Block &GameMap::getBlockUnsafe(int x, int y) {
    permaAssertCommentDevelopement(mapData.size() == w* h,"Map not initialized");
    permaAssertCommentDevelopement(x >= 0 && y >= 0 && x < w && y < h  ,"Out of bound access");
    return mapData[x + y * w];
}

Block *GameMap::getBlockSafe(int x,int y) {
    permaAssertCommentDevelopement(mapData.size() == w* h,"Map not initialized");
    if (x >= 0 && y >= 0 && x < w && y < h) {
        return &mapData[x + y * w];
    }
    return nullptr;
}