#include "grayCode.h"
#include "math.h"
#include "stdio.h"

int grayCode(int digits) {
    if (digits <= 0) return 0;
    int currentNumber = 0;
    int totalNumbers = (int)pow(2.0, (double)digits);
    for (int i = 0; totalNumbers > i; i++) {
        int auxiliaryNumber = currentNumber>>1;
        auxiliaryNumber = auxiliaryNumber ^ currentNumber;
        int correction = digits - 1;
        for (int j = totalNumbers>>1; j > 0; j = j>>1) {
            printf("%u", (auxiliaryNumber & j)>>correction);
            correction--;
        }
        printf("\n");
        currentNumber++;
    }
    return 0;
}