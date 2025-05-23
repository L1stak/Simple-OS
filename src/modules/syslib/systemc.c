#include "../std.h"

int size(const char* str) {
    int i = 0;
    while (str[i] != '\n') {
        i++;
    }
    return i;
}