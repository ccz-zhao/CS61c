#include <stdint.h>
#include <stdio.h>
#include "bit_ops.h"

/*
  Returns the n-th bit of x.
  Assumes 0 <= n <= 31.
*/
uint32_t get_bit(uint32_t x, uint32_t n) {
    /* YOUR CODE HERE */
    int mask = 1 << n;
    if (x & mask) 
      return 1;
    else
      return 0; /* UPDATE RETURN VALUE */
}

/*
  Set the n-th bit of *x to v.
  Assumes 0 <= n <= 31, and v is 0 or 1.
*/
void set_bit(uint32_t *x, uint32_t n, uint32_t v) {
    /* YOUR CODE HERE */
    int mask = 1 << n;
    if (v == 1) 
      *x =  *x | mask;
    else 
      *x = *x & (~mask);
}

/*
  Flips the n-th bit of *x.
  Assumes 0 <= n <= 31.
*/
void flip_bit(uint32_t *x, uint32_t n) {
    /* YOUR CODE HERE */
    if (get_bit(*x, n))
      set_bit(x, n, 0);
    else
      set_bit(x, n, 1);
}

