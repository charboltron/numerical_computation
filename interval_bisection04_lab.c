/*

The interval bisection method works iff 
the function is continuous and you can 
establish and initial left & right guess, 
such that:
   f(left) and f(right) have different signs
(i.e.: both positive or both negative).

COMPILE THIS CODE BY RUNNING:

gcc interval_bisection04_lab.c -lm

The -lm links with the math library

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f1 (double x)
{
  double y ;
  y = x*x - 2 ;
  return y ;
}


double f2 (double x)
//  three roots,
//  -3 - sqrt(3) = -4.732050,
//  -3 + sqrt(3) = -1.267949,
//   6
{
  double y ;
  y = x*x*x - 30*x - 36 ;
  return y ;
}



int interval_bisection(double (*f)(double x), // f points at a function with one double input and a double output 
		       double left, double right,
		       double epsilon, int maxreps,
		       double results[2])
// return 0 failure, else 'numreps' (>= 1)
// 'maxreps' is the maximum iterations through the loop
{
  // example of a valid function call to f:
  // double fl ;
  // fl = f(left) ;

  // Your algorithm should continue until 'maxreps' iterations have been
  // performed or the difference between guesses is within 'epsilon'

  // YOUR CODE GOES BELOW!!!!!!!!!
  double fl, fr, fm, mid;
  int numreps;
  for (int i = 1; i <= maxreps; i++){
    fl = f(left);
    fr = f(right);
    mid = (right+left)/2;
    if(fl == 0 || fr == 0){
      printf("You guessed a root.\n");
      if(fl){mid = right;}
      else{mid = left;}
      numreps = i;
      break;
    }
    if((fl < 0 && fr > 0)||(fl > 0 && fr < 0)){
      fm = f(mid);  
      if((fm < 0 && fl < 0)||(fm > 0 && fl > 0)){
        left = mid;
      }
      else{
        right = mid;
      }
      if(fabs(fm) <= epsilon){
        numreps = i;
        break;
      }
    } else {
      printf("The function evaluated at these two x-values has the same sign for both!\n");
      return 0;
    } 
  }
     results[0] = mid;
     results[1] = f(mid);
     return numreps; 
  return 0;
}


int main()
{
  int maxreps, numr;
  double left_guess,right_guess,res[2] ;

  // test #1:
  
  left_guess  = 1 ;
  right_guess = 2 ;

  maxreps = 100 ;
  numr = interval_bisection(f1, left_guess,right_guess,  1e-12, maxreps,  res) ;
  if (numr == 0) {
    printf("Failure to find a root.\n") ;
  } else {
    printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
    
    // res[0] is our approximation to a root.
    // res[1] is the function evaluated at res[0],
    // which should be close to 0 if we came close to finding a root.
    
    // NOTE: numreps equals maxreps, if the algorithm performed maxreps repititions
  }
  //////////////////////////////////////////////////////////////


  // test #2 :

  numr = interval_bisection(sin, 3,4,  1e-12, 50,  res) ;
  // for this test the function is the sin(x)
  
  if (numr == 0) {
    printf("Failure to find a root.\n") ;
  } else {
    printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
  }

  /////////////////////////////////////////////////////////////
  
  // test #3:
  
  printf("Enter left, right for root search: ") ;
  scanf("%lf %lf",&left_guess,&right_guess) ;
  if(left_guess > right_guess){
    double temp = left_guess;
    left_guess = right_guess;
    right_guess = temp; 
  }
  maxreps = 100 ;
  numr = interval_bisection(f2, left_guess,right_guess,  1e-12, maxreps,  res) ;
  
  if (numr == 0) {
    printf("Failure to find a root.\n") ;
  } else {
    printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
  }
}
