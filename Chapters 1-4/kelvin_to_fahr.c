#include <stdio.h>

#define LOWER 0
#define UPPER 250
#define STEP 20

double kelvin_to_fahr(double k);

int main() {
    printf("KELVIN\t\tFAHR\n");
    for (float kelvin = LOWER; kelvin <= UPPER; kelvin += STEP) {
        printf("%.0f\t\t%.2f\n", kelvin, kelvin_to_fahr(kelvin));
    }
}

double kelvin_to_fahr(double k) {
    return ((k - 273.15) * 9.0/5.0 + 32);
}