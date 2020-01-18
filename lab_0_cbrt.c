#include <stdio.h>
#include <math.h>

int main (void) {

    double x = 1;
    for(int i = 0; i < 20; i++){
        x = cbrt(30*x+36);
        printf("x = %lf \n", x);
    }

}

