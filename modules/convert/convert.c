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