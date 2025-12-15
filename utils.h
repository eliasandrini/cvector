#ifndef VEC_UTILS
#define VEC_UTILS

#include "vector.h"
#include <stdio.h>

/* -- Utility functions for vector -- */

/**
 * Print
 */
void vec_print(const vector self);
void vec_print_info(const vector self);

/**
 * Calculations
 */
int vec_sum(const vector self);
int vec_max(const vector self);
int vec_min(const vector self);
size_t vec_find(const vector self, const int *value);

#endif // !VEC_UTILS