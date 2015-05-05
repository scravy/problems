#include <stdio.h>
#include <stdlib.h>

int cycle_length(int n) {
    int length = 1;
    while (n != 1) {
        if (n % 2) {
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
        length += 1;
    }
    return length;
}

int main(int argc, char** argv) {
    for (;;) {
        int i, t, a, b, maximum = 1;
        if (scanf("%d %d", &a, &b) != 2) {
            break;
        }
        if (a > b) {
            i = b;
            t = a;
        } else {
            i = a;
            t = b;
        }
        for (; i <= t; i++) {
            int length = cycle_length(i);
            if (length > maximum) {
                maximum = length;
            }
        }
        printf("%d %d %d\n", a, b, maximum);
    }
    return 0;
}
