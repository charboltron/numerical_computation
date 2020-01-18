#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f (double x)
{
  double y ;
  y = x*x*x - 30*x - 36 ;
  return y ;
}

double fprime(double x)
{
    double y ; 
    y = 3*(x*x)-30;
    return y;
}

int newtons_method(double (*f)(double x), double x,
		       double epsilon, int maxreps,
		       double results[2])
{
    for (int i = 0; i < maxreps; i++){
        x = x - (f(x)/fprime(x));
        printf("%lf\n", x);
    }
    return x;//don't return x
}

int main (){
    int maxreps, numr;
    double x,res[2];
    maxreps = 100;
    x = 4;
    numr = newtons_method(f, x, 1e-12, maxreps,  res);
    if (numr == 0) {
    printf("Failure to find a root.\n") ;
    } else {
        printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
    
        // res[0] is our approximation to a root.
        // res[1] is the function evaluated at res[0],
        // which should be close to 0 if we came close to finding a root.
    
        // NOTE: numreps equals maxreps, if the algorithm performed maxreps repititions
    }
    
}
