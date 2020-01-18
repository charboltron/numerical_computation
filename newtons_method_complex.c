#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>

complex f(complex x) 
{
  complex ans ;

  ans = x*x*x - 11*x*x + 55*x - 125 ;
  //ans = x*x - 4 ;

  return ans ;
}

complex p(complex x) 
{
  complex ans ;

  ans =  3*x*x - 22*x + 55 ;
  //ans =  2*x*x ;

  return ans ;
}

int main()
{

  // This program finds the roots of a function using Newton's Method.  
  // Define the function and its derivative.

  int k ;
  double a,b,gr,gi ;
  complex x, y, m ;
  
  printf("Input a complex number (in the form of a + bi) seed for Newton's Method:\n") ;
  printf("a = ") ;
  scanf("%lf", &gr) ; 
  printf("\nb = ") ;
  scanf("%lf", &gi) ; 

  // Invoke Netwon's Method (g for guess)
  x = gr + gi*I ;
  for(k=0;k<20;k++) {
    y = f(x);
    m = p(x) ;
    x = (m*x-y)/m ;
    a = creal(x) ;
    b = cimag(x) ;
    printf("root = %lf + %lfi\n", a, b) ;
  }
}
