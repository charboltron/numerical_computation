#include <stdio.h>
#include <stdlib.h>

int main () { 

    //guess vector. Can be all ones or zeroes or whatever. Like FPI, just a seed. 
    double x1 = 1; //obviously doesn't matter
    double x2 = 2; 
    double x3 = 0; 
    double x4 = 4;

    for(int i = 1; i <= 20; i++){
        x1 = (44-5*x2-7*x3+2*x4)/20; 
        x2 = (-53-4*x1-2*x3-3*x4)/21; 
        x3 = (40-2*x1-3*x2-4*x4)/13; 
        x4 = (56-3*x1-5*x2+4*x3)/15; 
        printf("%2d : %10.6lf %10.6lf %10.6lf %10.6lf\n\n", i, x1, x2, x3, x4);
    }
}