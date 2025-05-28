#include <stddef.h>
#include <stdint.h>

typedef struct GDT {
uint8_t limit;
uint16_t flags;

};