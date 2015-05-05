#include <stdio.h>
#include <stdlib.h>

long cycle_length(long n) {
    long length = 1;
    while (n != 1) {
        if (n % 2) { // is n odd?
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
        long a, b, maximum = 1;
        if (scanf("%ld %ld", &a, &b) != 2) {
            break;
        }
        for (int i = a; i <= b; i++) {
            long length = cycle_length(i);
            if (length > maximum) {
                maximum = length;
            }
        }
        printf("%ld %ld %ld\n", a, b, maximum);
    }
    return 0;
}
