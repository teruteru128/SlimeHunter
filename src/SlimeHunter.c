
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include "random.h"
#include "mcSlimeChunkOracle.h"

/*
  TODO renovate to search 5x5
  20/25 > 16/16 > 21/25

  メモ化
  1行ごとに移動最大

*/
int main(int argc, char* argv[]){
  SlimeChunkSeed seed;
  Random random;
  setSeed(&random, 0);
  fprintf(stderr, "%u\n", next(&random, 32));
  fprintf(stderr, "%u\n", nextInt(&random));
  fprintf(stderr, "%u\n", nextIntWithRange(&random, 10));
  fprintf(stderr, "%"PRId64"\n", nextLong(&random));

  FILE* fp;
  char* rpath = "/dev/urandom";
  fp = fopen(rpath,"rb");
  if(fp == NULL){
    return EXIT_FAILURE;
  }
  int64_t rndSeed = 0;
  int64_t currentSeed = 0;
  size_t len = fread(&rndSeed, sizeof(rndSeed), 1, fp);

  fprintf(stderr, "Initial Seed : %"PRId64"\n", rndSeed);

  int64_t chunkX, xMin = -313, xMax = 312, x;
  int64_t chunkZ, zMin = -313, zMax = 312, z;
  int64_t countRangeX = 4;
  int64_t countRangeZ = 4;
  int64_t minSlimeChunks = 9;
  uint64_t i = 0;
  int32_t slimeChunkCount = 0;
  int32_t chunkCount = 0;
  long exX = 0;
  long exZ = 0;
  clock_t start = clock();
  int64_t searchSeeds = 10000ULL;

  char cache[4][625];
  for(i = 0; i < searchSeeds; i++){
    currentSeed = rndSeed++;
    setMCSeed(&seed, currentSeed);

    // 最初の4行のキャッシュを作成
    // 1行ずつcountRangeごとの移動最大を取る
    // 最大がcountRangeと等しくなかったら行ごとスキップ

    // 行
    for(chunkZ = zMin; chunkZ < zMax; chunkZ += 2){

      // 列
      for(chunkX = xMin; chunkX < xMax; chunkX += 2){
        
        if(isSlimeChunkXZ(&seed, chunkX + 2, chunkZ) && isSlimeChunkXZ(&seed, chunkX + 2, chunkZ + 2)){
          if(isSlimeChunkXZ(&seed, chunkX, chunkZ) && isSlimeChunkXZ(&seed, chunkX, chunkZ + 2)){
            /*
            printf("%"PRId64",%"PRId64",%"PRId64"\n", currentSeed, chunkX, chunkZ);
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
                  fprintf(stderr, "'%"PRId64",%"PRId64",%"PRId64",'%"PRId32"/%"PRId32"\n", currentSeed, (chunkX + x) * 16, (chunkZ + z) * 16, slimeChunkCount, chunkCount);
                }
              }
            }
            */
          }
        } else {
          chunkX += 2;
        }
      }
    }
  }
  clock_t finish = clock();
  double seconds = ((double)(finish - start)/ CLOCKS_PER_SEC);
  fprintf(stderr, "%"PRId64"seeds, %.2lfseeds/s, %.2lfs\n", searchSeeds, searchSeeds/seconds, seconds);
}

