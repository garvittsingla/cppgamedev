#include <raylib.h>
#include <gameMain.h>
#include <iostream>

#include "assetManager.h"

struct GameData {
} gameData;

AssetManager assetManager;

bool initGame() {
    assetManager.loadAll();
    std::cout << "init game called";
    return true;
}

bool updateGame() {
    float deltaTime = GetFrameTime();
    if (deltaTime > 1.f / 5 ){ deltaTime = 1.f / 5; }
    DrawTexturePro(assetManager.dirt,{0,0,(float)assetManager.dirt.width,(float)assetManager.dirt.height},{50,50,100,100},{},0,WHITE);
    return true;
}
bool closeGame() {
    std::cout << "game closed";
};
