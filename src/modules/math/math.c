#include "../math.h"
#include "../std.h"

unsigned int seed = 1;

double normalize(double x) {
    while (x > M_PI) x -= 2 * M_PI;
    while (x < -M_PI) x += 2 * M_PI;
    return x;
}
double exp(double x) {
    // Это первый раз, когда мне пришлось юзать ии в этом проектике :3
    if (x < 0) return 1.0 / exp(-x);

    double sum = 1.0;
    double term = 1.0;
    for (int i = 1; i < 50; ++i) {
        term *= x / i;
        sum += term;
        if (term < 1e-15) break;
    }
    return sum;
}
double sin(double x) {
    x = normalize(x);
    double tmp = x;
    double res = x;
    int sign = -1;
    for (int i = 3; i <= 21; i += 2) {
        tmp *= x * x / ((i - 1) * i);
        res += sign * tmp;
        sign *= -1;
    }
    return res;
}
double cos(double x) {
    x = normalize(x);
    double res = 1;
    double tmp = 1;
    int sign = -1;
    for (int i = 2; i <= 20; i += 2) {
        tmp *= x * x / ((i - 1) * i);
        res += sign * tmp;
        sign *= -1;
    }
    return res;
}
float tan(float x) {
    return sin(x) / cos(x);
}
float pow(float x, float y) {
    if (x <= 0) return -1;
    return exp(y * log(x));
}
float sqrt(float x) {
    if (x < 0 || x == 0) {
        return x != 0 ? -1 : 0;
    }
    double guess = x / 2.0;
    for (int i = 0; i < 20; ++i)
        guess = 0.5 * (guess + x / guess);
    return guess;
}
double log(double x) {
    if (x <= 0) return -1;

    double y = (x - 1) / (x + 1);
    double y2 = y * y;
    double sum = 0.0;
    double term = y;
    for (int n = 1; n < 100; n += 2) {
        sum += term / n;
        term *= y2;
    }
    return 2.0 * sum;
}

int rand(int min, int max) {
    time* t = getTime();
    seed = (1103515245 * seed + ((t->seconds * t->minutes * t->hours) / 5)) % (1 << 31);
    return min + (seed % (max - min + 1));
}