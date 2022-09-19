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
    Tik(naive)
    for(int j = 0;j<iterations;j++) {
      #pragma omp parallel
      for(int i = 0; i < LENGTH; i++) {
        x[i] = j;
      }
    }
    Tok(naive)
}
