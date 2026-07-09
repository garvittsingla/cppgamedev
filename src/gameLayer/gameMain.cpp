#include "assetManager.h"
#include "helpers.h"
#include "imgui.h"
#include "worldGenerator.h"
#include <gameMain.h>
#include <gameMap.h>
#include <iostream>
#include <raylib.h>

#include "structure.h"

struct GameData {
  GameMap gameMap;
  Camera2D camera;
  int createiveSelectedBlock = Block::dirt;

  Vector2 selectionStart = {};
  Vector2 selectionEnd = {};

  Structure copyStructure;
} gameData;

AssetManager assetManager;

bool showimgui = false;

bool initGame() {
  assetManager.loadAll();
  generateWorld(gameData.gameMap);

  gameData.camera.target = {10, 120};
  gameData.camera.rotation = 0.0f;
  gameData.camera.zoom = 30.0f;

  std::cout << "init game called";
  return true;
}

bool updateGame() {
  float deltaTime = GetFrameTime();
  if (deltaTime > 1.f / 5) {
    deltaTime = 1.f / 5;
  }
  gameData.camera.offset = {GetScreenWidth() / 2.f,  GetScreenHeight() / 2.f};
  ClearBackground({135, 206, 235, 255});
  float CAMERA_SPEED = 1.0f;
  if (IsKeyDown(KEY_LEFT))
    gameData.camera.target.x -= 7.f * deltaTime * CAMERA_SPEED;
  if (IsKeyDown(KEY_RIGHT))
    gameData.camera.target.x += 7.f * deltaTime * CAMERA_SPEED;
  if (IsKeyDown(KEY_UP))
    gameData.camera.target.y -= 7.f * deltaTime * CAMERA_SPEED;
  if (IsKeyDown(KEY_DOWN))
    gameData.camera.target.y += 7.f * deltaTime * CAMERA_SPEED;
  if (IsKeyPressed(KEY_SLASH)) {
    showimgui = !showimgui;
  }
  // if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_W)) &gameData.camera.zoom += 7;

  Vector2 worldpos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
  int blockX = worldpos.x;
  int blockY = worldpos.y;

  if (gameData.createiveSelectedBlock < 0) {
    gameData.createiveSelectedBlock = 0;
  }
  if (gameData.createiveSelectedBlock >= Block::BLOCKS_COUNT) {
    gameData.createiveSelectedBlock = Block::BLOCKS_COUNT - 1;
  }


  if (showimgui) {
    if (IsKeyPressed(KEY_ONE)) { gameData. selectionStart = Vector2{(float)blockX, (float)blockY}; }
    if (IsKeyPressed(KEY_TWO)) {gameData.selectionEnd = Vector2{(float)blockX, (float)blockY}; }
    if (IsKeyPressed(KEY_THREE)) {
      gameData.copyStructure.pasteIntoMap(gameData.gameMap,Vector2{(float)blockX,(float)blockY});
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
      if (b) {
        *b = {};}
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
      auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
      if (b) {
        b->type = gameData.createiveSelectedBlock;
      }
    }


    if (gameData.selectionStart.x > gameData.selectionEnd.x)
      std::swap(gameData.selectionStart.x, gameData.selectionEnd.x);

    if (gameData.selectionStart.y > gameData.selectionEnd.y)
      std::swap(gameData.selectionStart.y, gameData.selectionEnd.y);


  }


    BeginMode2D(gameData.camera);
    for (int y = 0; y < gameData.gameMap.h; y++) {
      for (int x = 0; x < gameData.gameMap.w; x++) {
        auto &b = gameData.gameMap.getBlockUnsafe(x, y);
        if (b.type != Block::air) {
          float size = 1;
          float posX = x * size;
          float posY = y * size;

          DrawTexturePro(assetManager.textures,
                         getTextureAtlas(b.type, 0, 32, 32),
                         {posX, posY, size, size}, {0, 0}, 0.0f, WHITE);
        }
      }
    }
    DrawTexturePro(assetManager.frame,
                   getTextureAtlas(0, 0, (float)assetManager.frame.width,
                                   (float)assetManager.frame.height),
                   {(float)blockX, (float)blockY, 1, 1}, {0, 0}, 0.0f, WHITE);

  if (showimgui) {
    Rectangle rect;
    rect.x = gameData.selectionStart.x;
    rect.y = gameData.selectionStart.y;
    rect.width = gameData.selectionEnd.x - gameData.selectionStart.x;
    rect.height = gameData.selectionEnd.y - gameData.selectionStart.y;
    rect.width++; rect. height++;
    DrawRectangleLinesEx(rect, 0.1,
    {20, 101, 250, 145});
  }

    EndMode2D();
    if (showimgui) {
      ImGui::Begin("Game control");
      ImGui::SliderFloat("Camera zoom : ", &gameData.camera.zoom, 2, 150);
      ImGui::SliderFloat("Camera Speed : ", &CAMERA_SPEED, 5, 30);

      if (ImGui::Button("copy")){
        gameData.copyStructure.copyFromMap(gameData.gameMap,gameData.selectionStart,gameData.selectionEnd);
      }
      ImGui::Separator();


      for (int i = 0; i < Block::BLOCKS_COUNT; i++) {
        auto atlas = getTextureAtlas(i, 0, 32, 32);
        atlas.x /= assetManager.textures.width;
        atlas.y /= assetManager.textures.height;
        atlas.width /= assetManager.textures.width;
        atlas.height /= assetManager.textures.height;

        ImGui::PushID(i);
        ImTextureID tex = (ImTextureID)(intptr_t)assetManager.textures.id;
        if (ImGui::ImageButton(
                tex, {35, 35}, {atlas.x, atlas.y},
                {atlas.x + atlas.width, atlas.y + atlas.height})) {
          gameData.createiveSelectedBlock = i;
        }
        ImGui::PopID();
        if (i % 10 != 0) {
          ImGui::SameLine();
        }
      }
      ImGui::End();
    }
    DrawFPS(10, 10);
    return true;
  }

bool closeGame() { std::cout << "game closed"; };
