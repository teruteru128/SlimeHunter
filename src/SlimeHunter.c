
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include "random.h"
#include "mcSlimeChunkOracle.h"

int64_t readSeed(void){
  FILE* fp;
  char* rpath = "/dev/urandom";
  fp = fopen(rpath,"rb");
  if(fp == NULL){
    return EXIT_FAILURE;
  }
  int64_t val = 0;
  size_t len = fread(&val, sizeof(val), 1, fp);
  return val;
}

/*
   Minecraftのスライムチャンクのシード値探索ツール
   TODO 5x5向けに改修
   20/25 > 16/16 > 21/25

    for(chunkZ = zMin; chunkZ < zMax; chunkZ += 2){
      for(chunkX = xMin; chunkX < xMax; chunkX += 2){
        if(isSlimeChunkXZ(&seed, chunkX + 2, chunkZ) && isSlimeChunkXZ(&seed, chunkX + 2, chunkZ + 2)){
          if(isSlimeChunkXZ(&seed, chunkX, chunkZ) && isSlimeChunkXZ(&seed, chunkX, chunkZ + 2)){
            for(z = -1; z < 1; z ++){
              for(x = -1; x < 1; x++){
                slimeChunkCount = 4;
                chunkCount = 4;
                for(exX = 0; exX < countRangeX; exX++) {
                  for(exZ = 0; exZ < countRangeZ; exZ++) {
                    if((z + exZ) % 2 != 0 || (x + exX) % 2 != 0){
                      chunkCount++;
                      if(isSlimeChunkXZ(&seed, chunkX + exX + x, chunkZ + exZ + z)){
                        slimeChunkCount++;
                      }
                    }
                  }
                }
                if(slimeChunkCount >= minSlimeChunks){
                  printf("'%"PRId64",%"PRId64",%"PRId64",'%"PRId32"/%"PRId32"\n", currentSeed, (chunkX + x) * 16, (chunkZ + z) * 16, slimeChunkCount, chunkCount);
                }
              }
            }
          }
        } else {
          chunkX += 2;
        }
      }
    }
  }
  clock_t finish = clock();
  double seconds = ((double)(finish - start)/ CLOCKS_PER_SEC);
  printf("%"PRId64"seeds, %.2lfseeds/s, %.2lfs\n", searchSeeds, searchSeeds/seconds, seconds);
  return EXIT_SUCCESS;
   メモ化
   5行ごとにウィンドウサイズ5チャンクで移動しながらチャンク数を調べる
   5チャンク連続でスライムチャンクな場所を見つけたら上下4チャンク、近い側から数える
*/
int main(int argc, char* argv[]){
}

