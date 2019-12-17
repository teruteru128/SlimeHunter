
#include <stdio.h>
#include <stdint.h>
#include "mcSlimeChunkOracle.h"

void setMCSeed(SlimeChunkSeed* t, int64_t seed){
    t->seed = seed;
}

/*
int64_t getMCSeed(int64_t mc_seed, int32_t chunkX, int32_t chunkZ){
  return mc_seed + chunkX * chunkX * 0x4c1906 + chunkX * 0x5ac0db + chunkZ * chunkZ * 0x4307a7L + chunkZ * 0x5f24f ^ 0x3ad8025f;
}
*/
/*
   https://minecraft.gamepedia.com/Slime#.22Slime_chunks.22
   シード計算の各項は再利用できる
   chunkX*chunkX*0x4c1906
   chunkX*0x5ac0db
   chunkZ*chunkZ*0x4307a7L
   chunkZ*0x5f24f^0x3ad8025f
   TODO: 乗算処理は重いため計算結果をメモ化する
*/
int64_t getMCSeed(SlimeChunkSeed* seed, int32_t chunkX, int32_t chunkZ){
  return seed->seed + chunkX * chunkX * 0x4c1906 + chunkX * 0x5ac0db + chunkZ * chunkZ * 0x4307a7LL + chunkZ * 0x5f24f ^ 0x3ad8025f;
}

/*
   bool isSlimeChunk(int64_t seed, int32_t x_chunk, int32_t z_chunk){
      return nextIntWithRange(getMCSeed(seed, x_chunk, z_chunk));
   }
 */
/*
   TODO: seed, x, zを引数に取るハッシュ関数として実装し直す
   bool isSlimeChunk(int64_t seed, int32_t x, int32_t z)
   もしくは
   bool isSlimeChunk(Random* rnd, int64_t seed, int32_t x, int32_t z)
   Randomインスタンスをライブラリ内部で持たない理由
   マルチスレッド/マルチプロセスに対して安全にしたい
*/
bool isSlimeChunk(Random* rnd){
    return nextIntWithRange(rnd, 10) == 0;
}

/*
   TODO: Randomインスタンスを使いまわし、なおかつマイクラシードをint64_tで毎回指定するようにする
*/
bool isSlimeChunkXZ(SlimeChunkSeed* seed, int64_t chunkX, int64_t chunkZ){
  return isSlimeChunk(setSeed(&seed->rnd, getMCSeed(seed, (int32_t)chunkX, (int32_t)chunkZ)));
}

