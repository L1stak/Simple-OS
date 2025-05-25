#include "../std.h"

const char* int_to_char(int num) {
    static char buffer[12];
    int is_negative = 0;
    int i = 10;

    buffer[11] = '\0';

    if (num == 0) {
        buffer[10] = '0';
        return &buffer[10];
    }
    
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num > 0 && i > 0) {
        buffer[i--] = '0' + (num % 10);
        num /= 10;
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