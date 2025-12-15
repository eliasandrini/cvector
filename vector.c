#include "vector.h"

/**
 * Constructor: vector with default capacity
 */
vector newVector()
{
    vector self = (vector)malloc(sizeof(struct vector_T));

    self->values = calloc(CVEC_CAPACITY, sizeof(int));
    if (self->values != NULL)
        self->capacity = CVEC_CAPACITY;
    else 
        self->capacity = 0;

    self->size = 0;

    return self;
}


/**
 * Constructor: vector copy
 */
vector copyVector(const vector other)
{
    vector self = (vector)malloc(sizeof(struct vector_T));

    self->values = malloc(other->capacity * sizeof(int));
    if (self->values != NULL)
    {
        for (size_t i = 0; i < other->size; i++)
            self->values[i] = other->values[i];

        self->capacity = other->capacity;
        self->size = other->size;
    }
    else
    {
        self->capacity = 0;
        self->size = 0;
    }

    return self;
}


/**
 * Constructor: vector with given size
 */
vector sizedVector(const size_t size)
{
    vector self = (vector)malloc(sizeof(struct vector_T));

    self->values = malloc(size * sizeof(int));
    if (self->values != NULL)
    {
        self->capacity = size;
        self->size = size;
    }
    else
    {
        self->capacity = 0;
        self->size = 0;
    }

    return self;
}


/**
 * Destructor
 */
void vec_free(vector self)
{
    free(self->values);
    free(self);
}


/**
 * Getter: size
 */
size_t vec_size(const vector self)
{
    return self->size;
}


/**
 * Getter: capacity
 */
size_t vec_capacity(const vector self)
{
    return self->capacity;
}


/**
 * Check if vector is empty
 */
bool vec_empty(const vector self)
{
    return self->size == 0;
}


/**
 * Setter: capacity
 */
void vec_reserve(vector self, const size_t capacity)
{
    if (capacity > self->capacity)
    {
        self->values = (int *)realloc(self->values, capacity);

        if (self->values == NULL)
        {
            self->capacity = 0;
            self->size = 0;
        }
        else
            self->capacity = capacity;
    }
}


/**
 * Setter: size
 */
void vec_resize(vector self, const size_t size)
{
    if (size > self->capacity)
        vec_reserve(self, size);

    if (self->capacity < size)
        self->size = self->capacity;
    else
        self->size = size;
}


/**
 * Setter: assign value to count elements
 */
void vec_assign(vector self, const size_t count, const int value)
{
    free(self->values);
    self->values = malloc(count * sizeof(int));

    if (self->values == NULL)
    {
        self->capacity = 0;
        self->size = 0;
        return;
    }
    else
        self->capacity = count;

    for (size_t i = 0; i < count && i < self->capacity; i++)
        self->values[i] = value;

    self->size = count;
}


/**
 * Setter: assign range of values
 */
void vec_assign_range(vector self, const int *begin, const int *end)
{
    free(self->values);
    self->values = malloc((end - begin) * sizeof(int));

    if (self->values == NULL)
    {
        self->capacity = 0;
        self->size = 0;
        return;
    }
    else
        self->capacity = end - begin;


    for (size_t i = 0; begin + i < end; i++)
        *(vec_at(self, i)) = *(begin + i);

    self->size = end - begin;
}


/**
 * Element access: pointer to begin
 */
int *vec_begin(const vector self)
{
    return self->values;
}


/**
 * Element access: pointer to last
 */
int *vec_last(const vector self)
{
    if (vec_empty(self))
        return vec_begin(self);
    else
        return vec_end(self) - 1;
}


/**
 * End pointer for iterators (condition: < vec_end)
 */
int *vec_end(const vector self)
{
    return &(self->values[self->size]);
}


/**
 * Element access: pointer index
 */
int *vec_at(const vector self, const size_t index)
{
    if (self->size > index)
        return &(self->values[index]);
    else
        return NULL;
}


/**
 * Element access: value at index
 */
int vec_value_at(const vector self, const size_t index)
{
    if (self->size > index)
        return self->values[index];
    else
        return 0;
}


/**
 * Pop last element
 */
int vec_pop_back(vector self)
{
    if (!vec_empty(self))
    {
        self->size--;
        return self->values[self->size];
    }
}


/**
 * Push value to the back of the vector
 */
void vec_push_back(vector self, const int value)
{
    if (self->size >= self->capacity)
    {
        size_t newc = self->capacity * 2;
        void *ptr = realloc(self->values, newc * sizeof(int));

        if (ptr == NULL)
            exit(-1);

        self->capacity = newc;
        free(self->values);
        self->values = (int *)ptr;
    }

    self->values[self->size] = value;
    self->size++;
}


/**
 * Append range of values (pointers) to the vector
 */
void vec_append_range(vector self, const int *begin, const int *end)
{
    size_t to_add = end - begin;
    size_t starting_point = self->size;
    vec_resize(self, self->size + to_add);

    int *iterator = vec_at(self, starting_point);
    for (size_t i = 0; begin + i < end; i++)
        *iterator = *(begin + i);
}


/**
 * Clear the vector (only changes size)
 */
void vec_clear(vector self)
{
    free(self->values);
    self->values = malloc(sizeof(int) * self->capacity);
    self->size = 0;
}


/**
 * Shrink the capacity to fit the size
 */
void vec_shrink_to_fit(vector self)
{
    if (self->capacity > self->size)
    {
        self->values = realloc(self->values, self->size * sizeof(int));
        self->capacity = self->size;
    }
}


/**
 * Insert value at index
 */
void vec_insert(vector self, const size_t index, const int value)
{
    if (index >= self->size)
        vec_push_back(self, value);
    else
    {
        size_t pos = self->size;
        self->size++;
        int *iterator = vec_last(self);

        while (pos > index)
        {
            *iterator = *(iterator - 1);
            iterator--;
            pos--;
        }

        *iterator = value;
        self->size++;
    }
}


/**
 * Insert range of values starting at index
 */
void vec_insert_range(vector self, const size_t index, const int *begin, const int *end)
{
    size_t to_add = end - begin;
    vec_resize(self, self->size + to_add);

    if (index >= self->size)
        for (size_t i = 0; begin + i < end; i++)
            vec_push_back(self, *(begin + i));
    else
    {
        int* start = vec_at(self, index);
        int *back_iterator = vec_last(self);

        // Shift existing elements to make space
        while (back_iterator - start > to_add)
        {
            *back_iterator = *(back_iterator - to_add);
            back_iterator--;
        }

        // Insert new elements
        for (size_t i = 0; i < to_add; i++)
        {
            *(start + i) = *(begin + i);
        }

        self->size += to_add;
    }
}


/**
 * Erase value at index.
 * Returns pointer to next element
 */
int *vec_erase(vector self, const size_t index)
{
    if (index >= self->size)
        return vec_end(self);
    else
    {
        int *iterator = vec_at(self, index);
        while (iterator < vec_last(self))
            *iterator = *(iterator + 1);

        self->size--;

        return vec_at(self, index);
    }
}


/**
 * Erase count values starting at index.
 * Returns pointer to next element
 */
int *vec_erase_range(vector self, const size_t index, const size_t count)
{
    if (index >= self->size)
        return vec_end(self);
    else
    {
        int *iterator1 = vec_at(self, index);
        int *iterator2 = vec_at(self, index + count);
        size_t removed = 0;
        while (iterator2 < vec_end(self))
        {
            *iterator1 = *iterator2;
            iterator1++;
            iterator2++;
            removed++;
        }

        self->size -= removed;

        return vec_at(self, index);
    }
}


/**
 * Swap two vectors
 */
void vec_swap(vector first, vector second)
{
    vector tmp = first;
    first = second;
    second = tmp;
}
