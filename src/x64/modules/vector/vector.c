#include "../std.h"
#include "../vector.h"

void vectorInit(vector* vec, size_t el_size) {
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
    vec->el_size = el_size;
}
void vectorFree(vector* vec) {
    free(vec->data);

    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
    vec->el_size = 0;
}
void vectorPush_back(vector* vec, void* el) {
    if (vec->size == vec->capacity) {
        size_t capacityTMP = vec->capacity == 0 ? 4 : vec->capacity * 2;
        void* dataTMP = realloc(vec->data, capacityTMP * vec->el_size);
        vec->data = dataTMP;
        vec->capacity = capacityTMP;
    }
    memcpy((char*)vec->data + vec->size * vec->el_size, el, vec->el_size);
    vec->size++;
}
void* vectorGet(vector* vec, size_t i) {
    return (char*)vec->data + i * vec->el_size;
}