#include <raylib.h>
#include <gameMain.h>
#include <iostream>
#include <gameMap.h>
#include "assetManager.h"

struct GameData {
    GameMap gameMap;
    Camera2D camera;
} gameData;

AssetManager assetManager;

bool initGame() {
    assetManager.loadAll();
    gameData.gameMap.create(30,10);
    gameData. gameMap.getBlockUnsafe(0, 0) .type = Block::dirt;
    gameData. gameMap. getBlockUnsafe(1, 1). type = Block::dirt;
    gameData. gameMap.getBlockUnsafe(2, 2) .type = Block::dirt;
    gameData. gameMap. getBlockUnsafe(3, 3). type = Block::dirt;
    gameData. gameMap.getBlockUnsafe(4, 4). type = Block::dirt;

    gameData.camera.target = {0,0};
    gameData.camera.rotation = 0.0f;
    gameData.camera.zoom = 100.0f;

    std::cout << "init game called";
    return true;
}

bool updateGame() {
    float deltaTime = GetFrameTime();
    if (deltaTime > 1.f / 5 ){ deltaTime = 1.f / 5; }
    gameData.camera.offset = {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};
    ClearBackground({135, 206, 235, 255});

    if (IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= 7.f *deltaTime;
    if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += 7.f  *deltaTime;
    if (IsKeyDown(KEY_UP)) gameData.camera.target.y -= 7.f *deltaTime;
    if (IsKeyDown(KEY_DOWN)) gameData.camera.target.y += 7.f * deltaTime;
    BeginMode2D(gameData.camera);
    for (int y = 0 ; y < gameData.gameMap.h;y++) {
        for (int x = 0 ; x < gameData.gameMap.w;x++) {
            auto &b = gameData.gameMap.getBlockUnsafe(x,y);
            if (b.type != Block::air) {
                float size = 1;
                float posX = x*size;
                float posY = y*size;
                DrawTexturePro(assetManager.dirt,
                                Rectangle{0.f,0.f,(float)assetManager.dirt.width,(float)assetManager.dirt.height},
                                {posX,posY,size,size},
                                {0,0},
                                0.0f,
                                WHITE
                                );
            }
        }
    }

        EndMode2D();
    
    return true;
}
bool closeGame() {
    std::cout << "game closed";
};
