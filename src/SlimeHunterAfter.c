
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include "random.h"
#include "mcSlimeChunkOracle.h"

int main(int argc, char* argv[]){
  char buf[BUFSIZ];
  int64_t seed = 0;
  int64_t x = 0;
  int64_t z = 0;
  while(fgets(buf, BUFSIZ, stdin) != NULL) {
    if(sscanf(buf, "%" SCNd64 ",%" SCNd64",%" SCNd64, &seed, &x, &z) != 3){
      fprintf(stderr, "sscanf error!\n");
    }
    printf("seed = %" PRId64", x = %" PRId64", z = %" PRId64"\n", seed, x, z);
  }

  return EXIT_SUCCESS;
}
