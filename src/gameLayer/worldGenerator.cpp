#include <random>
#include <worldGenerator.h>
#include <iostream>
#include "randomStuff.h"
#include <blocks.h>
#include <FastNoiseSIMD.h>
#include <cstdlib>
void generateWorld(GameMap &gameMap, int seed) {
    int w = 900;
    int h = 500;
    gameMap.create(w,h);
    int stoneSize = 380;
    int dirtSize = 50;
    std::ranlux24_base rng(seed);

    //noise generators
    std::unique_ptr<FastNoiseSIMD> dirtNoiseGenerator(FastNoiseSIMD::NewFastNoiseSIMD());
    std::unique_ptr<FastNoiseSIMD> stoneNoiseGenerator(FastNoiseSIMD::NewFastNoiseSIMD());

    dirtNoiseGenerator->SetSeed(seed++);
    stoneNoiseGenerator->SetSeed(seed++);

    dirtNoiseGenerator->SetNoiseType(FastNoiseSIMD::NoiseType::SimplexFractal);
    dirtNoiseGenerator->SetFractalOctaves(1);
    dirtNoiseGenerator->SetFrequency(0.02);

    stoneNoiseGenerator->SetNoiseType(FastNoiseSIMD::NoiseType::SimplexFractal);
    stoneNoiseGenerator->SetFractalOctaves(4);
    stoneNoiseGenerator->SetFrequency(0.01);

    float *dirtNoise =  FastNoiseSIMD::GetEmptySet(w);
    float *stoneNoise=  FastNoiseSIMD::GetEmptySet(w);

    dirtNoiseGenerator->FillNoiseSet(dirtNoise,0,0,0,w,1,1);
    stoneNoiseGenerator->FillNoiseSet(stoneNoise,0,0,0,w,1,1);

    for (int i = 0 ; i < w ; i++) {
        dirtNoise[i]=  (dirtNoise[i]+1)/2;
        stoneNoise[i]=  (stoneNoise[i]+1)/2;
    }

    int dirtoffsetStart = -5;
    int dirtoffsetEnd = 35;
    int stoneHeightStart = 80;
    int stoneHeightEnd = 170;

    for (int x = 0 ; x < w ; x++) {

        int stoneHeight = stoneHeightStart + (stoneHeightEnd - stoneHeightStart) * stoneNoise[x];
        int dirtHeight = dirtoffsetStart + (dirtoffsetEnd - dirtoffsetStart) * dirtNoise[x];
        dirtHeight = stoneHeight - dirtHeight;

        for (int y = 0 ; y < h ; y++) {
            Block b;
            std::cout<<"inside the game geenrator";

            if (y > dirtHeight) {
                b.type = Block::dirt;
            }else if (y == dirtHeight) {
                b.type = Block::grassBlock;
            }else if (y>=stoneHeight) {
                b.type = Block::stone;
            }
            gameMap.getBlockUnsafe(x,y) = b;

        }




    }
    FastNoiseSIMD::FreeNoiseSet(dirtNoise);
    FastNoiseSIMD::FreeNoiseSet(stoneNoise);
}
