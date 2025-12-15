#include "utils.h"


/**
 * Print the elements of the vector
 */
void vec_print(const vector self)
{
    printf("[");
    for (int *i = vec_begin(self); i < vec_last(self); i++)
    {
        printf("%d, ", *i);
    }
    if (!vec_empty(self))
    {
        printf("%d", *(vec_last(self)));
    }
    printf("]\n");
}


/**
 * Print vector info: size, capacity and elements
 */
void vec_print_info(const vector self)
{
    printf("size: %ld \tcapacity: %ld\n", self->size, self->capacity);
    vec_print(self);
}


/**
 * Compute sum of all elements
 */
int vec_sum(const vector self)
{
    int *iterator = vec_begin(self);
    int sum = 0;
    while (iterator < vec_end(self))
    {
        sum += *iterator;
        iterator++;
    }
    return sum;
}


/**
 * Compute max element
 */
int vec_max(const vector self)
{
    if (vec_empty(self))
    {
        return 0;
    }

    int *iterator = vec_begin(self);
    int max = *iterator;
    iterator++;
    while (iterator < vec_end(self))
    {
        if (max < *iterator)
        {
            max = *iterator;
        }
        iterator++;
    }

    return max;
}


/**
 * Compute min element
 */
int vec_min(const vector self)
{
    if (vec_empty(self))
    {
        return 0;
    }

    int *iterator = vec_begin(self);
    int min = *iterator;
    iterator++;
    while (iterator < vec_end(self))
    {
        if (min > *iterator)
        {
            min = *iterator;
        }
        iterator++;
    }

    return min;
}


/**
 * Find the index of the first occurrence of a value in the vector
 */
size_t vec_find(const vector self, const int *value)
{
    int *iterator = vec_begin(self);
    while (iterator < vec_end(self))
    {
        if (*iterator = *value)
        {
            return iterator - vec_begin(self);
        }
        iterator++;
    }
    return -1;
}
