#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>

void print_polynomial(double coefficients[], int polynomial_degree){
        for(int i = 0; i < polynomial_degree+1; i++){
        printf("%d%s%d", (int)coefficients[i], "x^", polynomial_degree-i);
        if(i!=polynomial_degree){
            printf(" + ");
        }
    }
     printf("\n");
}

void calculate_derivative(double coeffs[], double prime_coeffs[], int polynomial_degree){
    for(int i = 0; i < polynomial_degree; i++){
        prime_coeffs[i] = coeffs[i]*(polynomial_degree-i);
    }
    printf("f_prime = ");
    print_polynomial(prime_coeffs, polynomial_degree-1);
}

complex f_complex(complex x){
    
}

double f(double x, double coeffs[], int polynomial_degree) 
{
  double y=0;
  for(int i = 0; i < polynomial_degree+1; i++){
      y += (coeffs[i]* pow(x, (polynomial_degree-i))); 
  }
  return y ;
}

double fprime(double x, double prime_coeffs[], int polynomial_degree)
{
    double y=0; 
    for(int i = 0; i < polynomial_degree; i++){
        //printf("y = %lf\n", y);
        y += (prime_coeffs[i]* pow(x, (polynomial_degree-i-1))); 
        //printf("y+= %lf * x^%d = %lf\n", prime_coeffs[i], (polynomial_degree-i-1), y);
    }
    //printf("returning y = %lf\n", y);
    return y;
}

int newtons_method(double x, double epsilon, int maxreps,
		           double results[2], double coeffs[], int polynomial_degree)
{
    double * prime_coeffs = malloc(sizeof(double) * polynomial_degree);
    printf("Calculating derivative...\n");
    calculate_derivative(coeffs, prime_coeffs, polynomial_degree);
    int numreps = 0;
    for (int i = 0; i < maxreps; i++){
        //printf("%lf\n", fprime(4, prime_coeffs, polynomial_degree));
        x = x - (f(x, coeffs, polynomial_degree)/fprime(x, prime_coeffs, polynomial_degree));
        printf("%lf\n", x);
        if(fabs(f(x, coeffs, polynomial_degree)) <= epsilon){
        numreps = i;
        break;
      }
    }
    results[0] = x;
    results[1] = f(x, coeffs, polynomial_degree);
    return numreps;
}

int main(){
    int polynomial_degree = 0;
    double guess_real, guess_imaginary, a, b;
    printf("Enter the exponent of the higest degree polynomial: ");
    scanf("%d", &polynomial_degree);
    double *coeffs = malloc(sizeof(double) * polynomial_degree+1);
    printf("Enter the coefficients (you must enter zero for missing degrees!). Also, don't forget the constant. \nEnter: ");
    double current_coefficient;
    for(int i = 0; i < polynomial_degree+1; i++){
        scanf("%lf", &current_coefficient);
        coeffs[i] = current_coefficient;
    }
    printf("f = ");
    print_polynomial(coeffs, polynomial_degree);

    int maxreps, numr;
    double x,res[2];
    maxreps = 100;
    printf("Enter a starting real value: ");
    scanf("%lf", &guess_real);
    printf("Enter a starting imaginary value: ");
    scanf("%lf", &guess_imaginary);
    x = guess_real+guess_imaginary*I;
    numr = newtons_method(x, 1e-12, maxreps, res, coeffs, polynomial_degree);
    if (numr == 0 || numr == maxreps) {
    printf("Failure to find a root.\n") ;
    } else {
    printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
    printf("\n\n");
    }
}

