#ifndef TUPLE_H
#define TUPLE_H

#include <stdlib.h>

typedef struct Tuple
{
    size_t num_values;
    size_t* values;
} Tuple;

Tuple* createTuple(size_t* values, size_t num_values);
void freeTuple(Tuple* tuple);

#endif
