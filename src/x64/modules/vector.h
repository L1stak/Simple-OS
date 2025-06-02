#pragma once

#include <stdint.h>

typedef struct {
    void* data;
    size_t size;
    size_t capacity;
    size_t el_size;
} vector;

void vectorInit(vector* vec, size_t el_size);
void vectorFree(vector* vec);
void vectorPush_back(vector* vec, void* el);
void* vectorGet(vector* vec, size_t i);