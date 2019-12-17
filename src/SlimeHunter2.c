
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>
#include "random.h"
#include "mcSlimeChunkOracle.h"

int main(int argc, char* argv[]){

  char chunks[1000]={};
  const int64_t seed_min=-9158047567848165954LL, seed_max=seed_min+1000LL;
  int64_t seed;
  int32_t x,z,offsetx=-500, offsetz=-500;
  SlimeChunkSeed seedt;
  Random rnd;
  for(seed = seed_min; seed < seed_max; seed++){
    setMCSeed(&seedt, seed);
    //キャッシュゼロクリア
    memset(chunks, 0, 1000);
    //西の端5チャンク分をchunksに入れる
    size_t filled_with_slime_chunks=0;
    for(x=0;x<1000;x++){
      filled_with_slime_chunks = 0;
    //紅の豚の冒頭のように複数行まとめてキャッシュに入れる
      for(z=0;z<1000;z++){
          chunks[z] = (chunks[z]<<1 | isSlimeChunk(&rnd, seed, x+offsetx, z+offsetz)) & 0x1f;
          //0x1fが連続しているかチェック
          if(chunks[z] == 0x1f){
            //printf("ヌッ %ld, %d, %d\n", seed, (x+offsetx)*16, (z+offsetz)*16);
            filled_with_slime_chunks++;
          }else{
            filled_with_slime_chunks = 0;
          }
          if(filled_with_slime_chunks == 5){
            printf("found! %ld, %d, %d\n", seed, x*16, z*16);
          }
        }
    }
  }
  return EXIT_SUCCESS;
}

