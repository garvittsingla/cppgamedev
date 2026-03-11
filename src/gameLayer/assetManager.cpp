#include "assetManager.h" //look into the same folder

void AssetManager::loadAll() {
    dirt = LoadTexture(RESOURCE_PATH "dirt.png");
    textures = LoadTexture(RESOURCE_PATH "textures.png");
    frame = LoadTexture(RESOURCE_PATH "frame.png");

}
