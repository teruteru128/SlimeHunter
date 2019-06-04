
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

   メモ化
   5行ごとにウィンドウサイズ5チャンクで移動しながらチャンク数を調べる
   5チャンク連続でスライムチャンクな場所を見つけたら上下4チャンク、近い側から数える
*/
int main(int argc, char* argv[]){
}

