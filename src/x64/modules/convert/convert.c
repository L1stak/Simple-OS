#define ALIGN_UP(x, a)   ((((x) + ((a)-1)) & ~((a)-1)))
#define HEAP_SIZE (1024 * 1024)

#include "../std.h"

const char* int_to_char(int num) {
    static char buffer[12];
    int isNegative = 0;
    int i = 10;

    buffer[11] = '\0';

    if (num == 0) {
        buffer[10] = '0';
        return &buffer[10];
    }
    
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    while (num > 0 && i > 0) {
        buffer[i--] = '0' + (num % 10);
        num /= 10;
    }

    if (isNegative && i > 0) {
        buffer[i--] = '-';
    }

    return &buffer[i + 1];
}
const char* double_to_char(double num) {
    static char buffer[32];
    int i = 30;
    buffer[31] = '\0';

    bool is_negative = false;
    if (num < 0) {
        is_negative = true;
        num = -num;
    }

    long long int_part = (long long)num;
    double frac_part = num - (double)int_part;

    long long frac_scaled = (long long)(frac_part * 1000000.0 + 0.5);

    if (frac_scaled >= 1000000) {
        int_part += 1;
        frac_scaled = 0;
    }
    if (frac_scaled == 0) {
        for (int j = 0; j < 6; j++) {
            buffer[i--] = '0';
        }
    } else {
        for (int j = 0; j < 6; j++) {
            buffer[i--] = '0' + (int)(frac_scaled % 10);
            frac_scaled /= 10;
        }
    }

    buffer[i--] = '.';

    if (int_part == 0) {
        buffer[i--] = '0';
    } else {
        while (int_part > 0 && i > 0) {
            buffer[i--] = '0' + (int)(int_part % 10);
            int_part /= 10;
        }
    }

    if (is_negative && i > 0) {
        buffer[i--] = '-';
    }

    return &buffer[i + 1];
}


void memClear(char* str, int size) {
    for (int i = 0; i < size; i++) {
        str[i] = '\0';
    }
}
void* memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d = dest;
    const unsigned char* s = src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}


// -------------------------------
// Этот код я нагло спиздил 
// И мне похуй, что я его спиздил
// Главное, что работает :3
// -------------------------------
static uint8_t heap[HEAP_SIZE];
typedef struct header {
    size_t size;
    struct header *next;
} header_t;

static header_t *free_list = NULL;

void heap_init() {
    free_list = (header_t*)heap;
    free_list->size = HEAP_SIZE - sizeof(header_t);
    free_list->next = NULL;
}

void *memcpy_naive(void *dst, const void *src, size_t n) {
    unsigned char *d = (unsigned char*)dst;
    const unsigned char *s = (const unsigned char*)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dst;
}

void *malloc(size_t size) {
    size = ALIGN_UP(size, sizeof(void*));
    header_t **prev = &free_list;
    for (header_t *blk = free_list; blk; blk = blk->next) {
        if (blk->size >= size) {
            if (blk->size >= size + sizeof(header_t) + sizeof(void*)) {
                header_t *new_blk = (header_t*)((uint8_t*)blk + sizeof(header_t) + size);
                new_blk->size = blk->size - size - sizeof(header_t);
                new_blk->next = blk->next;
                blk->next = NULL;
                blk->size = size;
                *prev = new_blk;
            } else {
                *prev = blk->next;
                blk->next = NULL;
            }
            return (uint8_t*)blk + sizeof(header_t);
        }
        prev = &blk->next;
    }
    return NULL;
}

void free(void *ptr) {
    if (!ptr) return;
    header_t *blk = (header_t*)((uint8_t*)ptr - sizeof(header_t));
    blk->next = free_list;
    free_list = blk;
}

void *realloc(void *ptr, size_t new_size) {
    if (!ptr) return malloc(new_size);
    header_t *old_blk = (header_t*)((uint8_t*)ptr - sizeof(header_t));
    size_t old_size = old_blk->size;
    if (new_size <= old_size) {
        return ptr;
    }
    void *new_ptr = malloc(new_size);
    if (!new_ptr) return NULL;
    memcpy_naive(new_ptr, ptr, old_size);
    free(ptr);
    return new_ptr;
}