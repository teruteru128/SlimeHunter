
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include "random.h"
#include "mcSlimeChunkOracle.h"
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

int64_t readSeed(void){
  FILE* fp;
  char* rpath = "/dev/urandom";
  fp = fopen(rpath,"rb");
  if(fp == NULL){
    return EXIT_FAILURE;
  }
  int64_t val = 0;
  size_t len = fread(&val, sizeof(val), 1, fp);
  fclose(fp);
  return val;
}

void init_db_file(void);
/*
   Minecraftのスライムチャンクのシード値探索ツール
   TODO 5x5向けに改修
   20/25 > 16/16 > 21/25

    for(chunkZ = zMin; chunkZ < zMax; chunkZ += 2){
      for(chunkX = xMin; chunkX < xMax; chunkX += 2){
        if(isSlimeChunk(&seed, chunkX + 2, chunkZ) && isSlimeChunk(&seed, chunkX + 2, chunkZ + 2)){
          if(isSlimeChunk(&seed, chunkX, chunkZ) && isSlimeChunk(&seed, chunkX, chunkZ + 2)){
            for(z = -1; z < 1; z ++){
              for(x = -1; x < 1; x++){
                slimeChunkCount = 4;
                chunkCount = 4;
                for(exX = 0; exX < countRangeX; exX++) {
                  for(exZ = 0; exZ < countRangeZ; exZ++) {
                    if((z + exZ) % 2 != 0 || (x + exX) % 2 != 0){
                      chunkCount++;
                      if(isSlimeChunk(&seed, chunkX + exX + x, chunkZ + exZ + z)){
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
#define X_MIN (-312)
#define X_MAX (312)
#define Z_MIN (-312)
#define Z_MAX (312)
int main(int argc, char* argv[]){
  const int64_t seed = 1613738097659009556L;
  Random rnd;
  int32_t x=-3136/16;
  int32_t z=-2400/16;
  printf("%d%d%d%d\n", isSlimeChunk(&rnd, seed, x+0,z+0), isSlimeChunk(&rnd, seed, x+1,z+0), isSlimeChunk(&rnd, seed, x+2,z+0), isSlimeChunk(&rnd, seed, x+3,z+0));
  printf("%d%d%d%d\n", isSlimeChunk(&rnd, seed, x+0,z+1), isSlimeChunk(&rnd, seed, x+1,z+1), isSlimeChunk(&rnd, seed, x+2,z+1), isSlimeChunk(&rnd, seed, x+3,z+1));
  printf("%d%d%d%d\n", isSlimeChunk(&rnd, seed, x+0,z+2), isSlimeChunk(&rnd, seed, x+1,z+2), isSlimeChunk(&rnd, seed, x+2,z+2), isSlimeChunk(&rnd, seed, x+3,z+2));
  printf("%d%d%d%d\n", isSlimeChunk(&rnd, seed, x+0,z+3), isSlimeChunk(&rnd, seed, x+1,z+3), isSlimeChunk(&rnd, seed, x+2,z+3), isSlimeChunk(&rnd, seed, x+3,z+3));
  printf("%d%d%d%d\n", isSlimeChunk(&rnd, seed, x+0,z+4), isSlimeChunk(&rnd, seed, x+1,z+4), isSlimeChunk(&rnd, seed, x+2,z+4), isSlimeChunk(&rnd, seed, x+3,z+4));

  x = X_MIN;
  uint64_t a = 0;
  const clock_t start = clock();
  while(x < X_MAX){
    z = Z_MIN;
    while(z < Z_MAX){
      a = a<<1|isSlimeChunk(&rnd, seed, x, z);
      if((a&0x0f) == 0x0f){
        fputs("アッー！", stdout);
      }else{
        fputs("", stdout);
      }
      z++;
    }
    x++;
  }
  const clock_t end = clock();
  fputs("\n", stdout);
  printf("%.8f秒かかりました\n",((double)(end-start)/CLOCKS_PER_SEC));
  printf("1秒あたり%.8f回\n",1/((double)(end-start)/CLOCKS_PER_SEC));
  return EXIT_SUCCESS;
}
