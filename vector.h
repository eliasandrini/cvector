#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * Default initial capacity of the vector
 */
#define CVEC_CAPACITY 32

/**
 * Vector pointer to handle struct
 */
typedef struct vector_T* vector;

/**
 * Vector structure
 */
struct vector_T
{
    size_t size;
    size_t capacity;
    int* values;
};

/**
 * Vector constructors and destructor
 */
vector newVector();
vector copyVector(const vector other);
vector sizedVector(const size_t size);
void vec_free(vector self);

/**
 * Getters
 */
size_t vec_size(const vector self);
size_t vec_capacity(const vector self);
bool vec_empty(const vector self);

/**
 * Setters
 */
void vec_reserve(vector self, const size_t capacity);
void vec_resize(vector self, const size_t size);
void vec_assign(vector self, const size_t count, const int value);
void vec_assign_range(vector self, const int *begin, const int *end);

/**
 * Element access
 */
int *vec_begin(const vector self);
int *vec_last(const vector self);
int *vec_end(const vector self);
int *vec_at(const vector self, const size_t index);
int vec_value_at(const vector self, const size_t index);
int vec_pop_back(vector self);

/**
 * Modifiers
 */
void vec_push_back(vector self, const int value);
void vec_clear(vector self);
void vec_shrink_to_fit(vector self);

/**
 * More complex modifiers (groups of elements)
 */
void vec_append_range(vector self, const int *begin, const int *end);
void vec_insert(vector self, const size_t index, const int value);
void vec_insert_range(vector self, const size_t index, const int *begin, const int *end);
int *vec_erase(vector self, const size_t index);
int *vec_erase_range(vector self, const size_t index, const size_t count);
void vec_swap(vector first, vector second);

#endif // !VECTOR_H