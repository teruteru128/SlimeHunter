
#include "internal_random.h"
#include "random.h"

static int64_t initialScramble(int64_t seed){
    return (seed ^ MULTIPLIER) & MASK;
}

Random* setSeed(Random *rnd, int64_t seed){
    rnd->seed = initialScramble(seed);
    return rnd;
}

/*
int32_t next(int64_t* seed, int32_t bits){
    int64_t oldseed, nextseed;
    int64_t seed = *seed;
    oldseed = seed;
    nextseed = (oldseed * MULTIPLIER + ADDEND) & MASK;
    *rnd = nextseed;
    return (uint32_t)(nextseed >> (48 - bits));
}
*/
int32_t next(Random* rnd, int32_t bits){
    int64_t oldseed, nextseed;
    int64_t seed = rnd->seed;
    oldseed = seed;
    nextseed = (oldseed * MULTIPLIER + ADDEND) & MASK;
    rnd->seed = nextseed;
    return (uint32_t)(nextseed >> (48 - bits));
}

int64_t nextLong(Random* rnd){
    return ((int64_t)(next(rnd, 32)) << 32) + next(rnd, 32);
}

int32_t nextInt(Random* rnd){
    return next(rnd, 32);
}
/*
int32_t nextIntWithRange(int64_t seed, int32_t bound){
    if(bound <= 0){
      // err!
      return 0;
    }
    int64_t tmp = seed;
    int32_t r = next(&tmp, 31);
    int32_t m = bound - 1;
    if((bound & m) == 0){
        r = (int32_t)((bound * (int64_t)r) >> 31);
    }else{
      int32_t u;
      for(u = r; u - (r = u % bound) + m < 0; u = next(&tmp, 31));
    }
    return r;
}
*/
int32_t nextIntWithRange(Random *rnd, int32_t bound){
    if(bound <= 0){
      // err!
      return 0;
    }
    int32_t r = next(rnd, 31);
    int32_t m = bound - 1;
    if((bound & m) == 0){
        r = (int32_t)((bound * (int64_t)r) >> 31);
    }else{
      int32_t u;
      for(u = r; u - (r = u % bound) + m < 0; u = next(rnd, 31));
    }
    return r;
}

