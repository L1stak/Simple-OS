## Vector
### Vector из библиотеки vector.h.
### Для использования Vector нужно подключить библиотеку std.h.
Пример кода с типом `double`:
```c
vector v;
vectorInit(&v, sizeof(double));

double x = sin(4); // -0.756802
vectorPush_back(&v, &x);
x = pow(4, 3); // 64
vectorPush_back(&v, &x);

for (size_t i = 0; i < v.size; i++) {
    double *val = (double*)vectorGet(&v, i);
    print(double_to_char(*val));
    print("\n");
}

vectorFree(&v);
```
