
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
  fclose(fp);
  return val;
}

void init_db_file(void);
/*
   Minecraftのスライムチャンクのシード値探索ツール
   TODO 5x5向けに改修
   20/25 > 16/16 > 21/25

   メモ化
   5行ごとにウィンドウサイズ5チャンクで移動しながらチャンク数を調べる
   5チャンク連続でスライムチャンクな場所を見つけたら上下4チャンク、近い側から数える
*/
int main(int argc, char* argv[]){
  // DB file exists check
  // get seed range list
  // select seed range
  //init_seed_db();
  //seed_list list = NULL;
  //get_seed_list(con, &list);
  int64_t seed_start = 1613738097659009550L;
  int64_t seed_end = 1613738097659009560L;

  int32_t gx_min = -309;
  int32_t gx_max = 312;
  int32_t globalx = 0;
  int32_t gy_min = -312;
  int32_t gy_max = 309;
  int32_t globaly = 0;

  int32_t localx = 0;
  const int32_t localx_range = 4;
  int32_t localy = 0;
  const int32_t localy_range = 4;


  int64_t seed = 0;
  SlimeChunkSeed seedt;
  //foreach seedlist
  int i=0;
  for(seed = seed_start; seed <= seed_end; seed++){
    setMCSeed(&seedt, seed);
    for(globalx = gx_min; globalx <= gx_max; globalx += localx_range){
      for(globaly = gy_min; globaly <= gy_max; globaly++){
        for(localx = 0; isSlimeChunkXZ(&seedt, globalx+localx, globaly)&&localx < localx_range;localx++){
        }

        if(localx == localx_range){
            //printf("%ld, %d, %d\n", seed, globalx*16, globaly*16);
            //goto finish;
          printf("5chunk seed,%ld,%d,%d\n", seed, globalx, globaly);
          i=1;
          for(localy = -1; localy > -localy_range;localy--){
              if(isSlimeChunkXZ(&seedt, globalx+0, globaly+localy)
              &&isSlimeChunkXZ(&seedt, globalx+1, globaly+localy)
              &&isSlimeChunkXZ(&seedt, globalx+2, globaly+localy)
              &&isSlimeChunkXZ(&seedt, globalx+3, globaly+localy)
              &&isSlimeChunkXZ(&seedt, globalx+4, globaly+localy)){
              i++;
              printf("ue,%ld,%d,%d\n", seed, globalx, globaly);
            }else{
              break;
            }
          }
          for(localy = 1; localy < localy_range;localy++){
              if(isSlimeChunkXZ(&seedt, globalx+0, globaly+localy)
              &&isSlimeChunkXZ(&seedt, globalx+1, globaly+localy)
              &&isSlimeChunkXZ(&seedt, globalx+2, globaly+localy)
              &&isSlimeChunkXZ(&seedt, globalx+3, globaly+localy)
              &&isSlimeChunkXZ(&seedt, globalx+4, globaly+localy)){
              i++;
              printf("shita,%ld,%d,%d\n", seed, globalx, globaly);
            }else{
              break;
            }
          }
          if(i>=localy_range){
             printf("found!, %ld,%d,%d\n", seed, globalx*16, globaly*16);
          }
        }else{
          //globaly+=localx;
        }
      }
    }
  }
  //mark_seed_range_as_searched
  //end foreach seedlist
finish:
  return EXIT_SUCCESS;
}

