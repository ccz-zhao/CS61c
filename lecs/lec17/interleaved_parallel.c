#include "tiktok.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define LENGTH (1<<28)
#define iterations 8
int main () {
    char* x = malloc(sizeof(char)*LENGTH);
    printf("Starting\n");
    fflush(stdout);
    Tik(interleaved)
    for(int j = 0;j<iterations;j++) {
      #pragma omp parallel
      {
        int tid = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        for(int i = tid; i < LENGTH; i+= num_threads) {
          x[i] = j;
        }
      }
    }
    Tok(interleaved)
}
