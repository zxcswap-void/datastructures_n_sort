#include <stdio.h>
#include <stdlib.h>

unsigned int find_gcd(unsigned int a, unsigned int b) {
    if (a == 0 || a == b) {
        return b;
    } else if (b == 0) {
        return a;
    } else {
        return a > b ? find_gcd(b, a % b) : find_gcd(a, b % a);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: %s <NUMBER1> <NUMBER2>\n", argv[0]);
        return 1;
    }
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    printf("GCD: %d\n", find_gcd(num1, num2));
    return 0;
}
