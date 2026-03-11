#include <raylib.h>
#include <gameMain.h>
#include <iostream>
#include <gameMap.h>
#include "assetManager.h"
#include "helpers.h"
#include "imgui.h"
#include "worldGenerator.h"

struct GameData {
    GameMap gameMap;
    Camera2D camera;
} gameData;

AssetManager assetManager;

bool initGame() {
    assetManager.loadAll();
    generateWorld(gameData.gameMap);

    gameData.camera.target = {450,250};
    gameData.camera.rotation = 0.0f;
    gameData.camera.zoom = 1.0f;

    std::cout << "init game called";
    return true;
}

bool updateGame() {
    float deltaTime = GetFrameTime();
    if (deltaTime > 1.f / 5 ){ deltaTime = 1.f / 5; }
    gameData.camera.offset = {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};
    ClearBackground({135, 206, 235, 255});
    static float CAMERA_SPEED = 1.0f;
    if (IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= 7.f *deltaTime * CAMERA_SPEED;
    if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += 7.f  *deltaTime * CAMERA_SPEED;
    if (IsKeyDown(KEY_UP)) gameData.camera.target.y -= 7.f *deltaTime * CAMERA_SPEED;
    if (IsKeyDown(KEY_DOWN)) gameData.camera.target.y += 7.f * deltaTime * CAMERA_SPEED;

    Vector2 worldpos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
    int blockX = worldpos.x;
    int blockY = worldpos.y;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
        if (b) {
            *b = {};
        }
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
        if (b) {
            b->type = Block::goldBlock;
        }
    }
    BeginMode2D(gameData.camera);
    for (int y = 0 ; y < gameData.gameMap.h;y++) {
        for (int x = 0 ; x < gameData.gameMap.w;x++) {
            auto &b = gameData.gameMap.getBlockUnsafe(x,y);
            if (b.type != Block::air) {
                float size = 1;
                float posX = x*size;
                float posY = y*size;

                DrawTexturePro(assetManager.textures,
                                getTextureAtlas(b.type,0,32,32),
                                {posX,posY,size,size},
                                {0,0},
                                0.0f,
                                WHITE
                                );
            }
        }
    }
    DrawTexturePro(assetManager.frame,
                              getTextureAtlas(0,0,(float)assetManager.frame.width,(float)assetManager.frame.height),
                              {(float)blockX,(float)blockY,1,1},
                              {0,0},
                              0.0f,
                              WHITE
                              );

        EndMode2D();
    ImGui::Begin("Game control");
    ImGui::SliderFloat("Camera zoom : ",&gameData.camera.zoom,2,150);
    ImGui::SliderFloat("Camera Speed : ",&CAMERA_SPEED,5,30);
    ImGui::End();
    DrawFPS(10,10);
    return true;
}
bool closeGame() {
    std::cout << "game closed";
};
