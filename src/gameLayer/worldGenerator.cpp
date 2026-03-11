#include <random>
#include <worldGenerator.h>
#include <iostream>
#include "randomStuff.h"
#include <blocks.h>

void generateWorld(GameMap &gameMap, int seed) {
    int w = 900;
    int h = 500;
    gameMap.create(w,h);
    int stoneSize = 380;
    int dirtSize = 50;
    std::ranlux24_base rng(seed);
    for (int x = 0 ; x < w ; x++) {

        for (int y = 0 ; y < h ; y++) {
            Block b;
            std::cout<<"inside the game geenrator";

            if (y < h - (dirtSize + stoneSize)) {
                //air
            }else if (y == h -  (dirtSize+stoneSize)) {
                b.type = Block::grassBlock;
            }else if (y < h-stoneSize) {
                b.type = Block::dirt;
            }else {
                b.type = Block::stone;
                if (getrandomChance(rng,0.1)) {
                    b.type= Block::gold;
                }
            }
            gameMap.getBlockUnsafe(x,y) = b;

        }


    }
}
