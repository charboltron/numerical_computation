
/*
    FPToolkit.c : A simple set of graphical tools.
    FPToolkitDemo.c 
    Copyright (C) 2018  Ely

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License (version 3)
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

This code assumes an underlying X11 environment.

       Most freshly installed unbuntu environments do not have
       the X11 developr stuff they'll need to do graphics.
       To download X11 developer stuff, connect to the internet and 
       issue the following two commands.  Each will ask for your password
       and each will take a few minutes.  At some point it might even
       look like nothing is happening....be patient :
       
sudo  apt-get  install  libx11-dev     

sudo  apt-get  install  xorg-dev

*/




/*
If this file and the file, FPToolkit.c, are in the
same directory that you are trying to compile in,  
do the following :

cc  FPToolkitDemo.c   -lm  -lX11

*/


#include  "FPToolkit.c"
//#include "system_solver.c"

#define M 80

void print_matrix (double m[M][M+1], int n)
{
   for(int i = 0; i < n; i++){
       for(int j = 0; j < n+1; j++){
           printf("%-10.2lf ", m[i][j]);
       }
       printf("\n");
   }
   printf("\n-------------------------\n\n");
}

int gaussian_elimination(double m[M][M+1], int n, double x[M])
{
   int i,j,k ;
   double v,sum ;
   int max_row,c ;

   // reduce matrix to upper triangular form 

   for (j = 0 ; j < n-1 ; j++) {

    //  print_matrix(m,n) ;

     // search from row j+1 down to find the largest magnitude
     max_row = j ;
     for (k = j+1 ; k < n ; k++) {
       if (fabs(m[k][j]) > fabs(m[max_row][j])) { max_row = k ; }
     }
     if (max_row != j) {
       // swap rows
       for(c = j ; c <= n ; c++) {
         v = m[j][c] ; m[j][c] = m[max_row][c] ; m[max_row][c] = v ;
       }
     }

     if (m[j][j] == 0) return 0; 
  
     for (k = j+1 ; k < n ; k++) {
       v = m[k][j] / m[j][j] ;
       for (i = 0 ; i <= n ; i++) {
          m[k][i] = m[k][i] - v*m[j][i] ;
       }

     }
   }
   // Output the upper triangular form
   // print_matrix(m,n) ;

   // Now do the back substitution 
   for (j = n - 1 ; j >= 0 ; j--) {

     sum = 0.0 ;
     for (k = j + 1 ; k < n ; k++) {
        sum += (m[j][k] * x[k]) ;
     }
     if (m[j][j] == 0) return 0 ;
     x[j] = (m[j][n] - sum)/m[j][j] ;
   }

   /*
   for (j = 0 ; j < n ; j++) {
     printf("x[%d] = %.16lf\n",j,x[j]) ;
   }
   printf("\n") ;
   */
   return 1 ;
}

int main()
{
   printf("\nBest Polynomial Fitter: Charles Bolton 2019"); 
   printf("\n====================================\n");
   printf("NOTICE: THIS PROGRAM RUNS IN A LOOP!");
   printf("\n====================================\n");
   printf("\nTo make testing this program easier, you can enter as many data sets as you like.\n");
   printf("\nINSTRUCTIONS:");
   printf("\n   1. Enter your desired degree for the best fit polynomial.");
   printf("\n   2. Click up to the maximum allowable points.");
    printf("\n   3. Click the black margin to draw the best fit polynomial.");
    printf("\n   4. Hit the space bar to start over and enter a new polynomial degree in the terminal.");
    printf("\n   5. If at anytime you wish to exit, enter 0 for the polynomial degree.\n\n"); 
   while(1){ 
   const int MAX_POINTS = 50; 

   int    swidth, sheight ;
   double p[2] ;
   double x[MAX_POINTS],y[MAX_POINTS] ;
   double X,Y ;
   int poly_degree;
   int num_points;

    
   for(int i = 0; i < MAX_POINTS; i++){
        x[i] = y[i] = 0;
   }

   //Take user input before creating display
   printf("Please enter the degree of the best fit polynomial: ");
   scanf("%d", &poly_degree);
   if(poly_degree <= 0){
       printf("Exiting Program. Thanks for trying.\n\n");
       exit(0);
   }
   poly_degree+=1; //the code was logically written off-by-one, so this accounts for that. 
   int num_unknowns = (poly_degree * 2)-1;
   if(num_unknowns > 50){
       printf("Sorry, you can't enter a polynomial of degree higher than 24.\nExiting...\n");
       exit(0);
   }
   //printf("\nnumber of unknowns you will have: %d\n\n", num_unknowns);
   

   // must do this before you do 'almost' any other graphical tasks 
   swidth = 900 ;  sheight = 800;
   G_init_graphics (swidth,sheight) ;  // interactive graphics

   // clear the screen in a given color
   G_rgb (0.3, 0.3, 0.3) ; // dark gray
   G_clear ();
   G_rgb(0, 0, 0);
   G_fill_rectangle(800, 0, 100, 800);

   G_rgb(1, 1, 0);
   

   //--------------------------------------------------------------------------------WAIT FOR CLICKED POINTS
   num_points = 0;
   for(int i = 0; i < MAX_POINTS; i++){
     G_wait_click(p);
        if(p[0] > 800){
            //printf("\n\n==\n\n");
            num_points = i;
            if(num_points < poly_degree){
                printf("You didn't enter enough points. Terminating program.\n\n");
                exit(1);
            }
            i = MAX_POINTS;
            break;
        }
        x[i] = p[0] ; y[i] = p[1];
        G_fill_circle(x[i],y[i],2);
        if(i+1==MAX_POINTS){
            printf("\nYou've entered the maximum number of points. Let's not get too excited.\n\n");
            num_points = MAX_POINTS;
        }
   }

    
    double E_Xi[100], E_Yi[100];
    for(int i = 0; i < 100; i++){
        E_Xi[i] = E_Yi[i] = 0;
    }
    
    // DEBUGGING PRINT STMTS
    // for(int i = 0; i < num_points; i++){
    //     printf("x[%d] = %lf", i, x[i]);
    //     printf("  y[%d] = %lf\n", i, y[i]);
    // }

    //------------------------------------------------------------------------FILL SUMS ARRAYS
    //char pause;
    E_Xi[0] = num_points*1.0; //summation of x^0
    E_Yi[0] = 0; //initialize this with nothing because we don't use the sum of y^0;
    for(int i = 1; i < num_unknowns; i++){
        for(int j = 1; j < num_points+1; j++){
            //scanf("%c", &pause);
            //printf("Before: E_Xi[%d] = %lf\n", i, E_Xi[i]);
            //printf("Adding: %lf\n", pow(x[j-1], i));
            E_Xi[i] += (pow(x[j-1], i));
            //printf("E_Xi[%d] = %lf\n", i, E_Xi[i]); 
            E_Yi[i] += (pow(x[j-1], i-1)*y[j-1]);
            //printf("E_Yi[%d] = %lf\n", i, E_Yi[i]);
            if(E_Xi[i] <0 || E_Yi[i] <0){
                printf("Overflow detected!\n\n");
            }   
        }
    }

    // DEBUGGING PRINT STMTS
    // for(int i = 0; i < num_unknowns; i++){
    //     printf("E_Xi[%d] = %lf\n", i, E_Xi[i]); 
    //     printf("E_Yi[%d] = %lf\n", i, E_Yi[i]);
    // }
   
   //--------------------------------------------------------------------------SYSTEM SOLVER 
   double m[M][M+1];
   for(int i = 0; i < M; i++){
       for(int j =0; j< M+1; j++){
           m[i][j] = 0;
       }
   }
   for(int i = 0; i < poly_degree; i++){
       for(int j = 0; j < poly_degree; j++){
           //printf("m[%d][%d] = E_Xi[%d+%d] = %lf\n", i, j, i, j, E_Xi[i+j]);
           m[i][j] = E_Xi[i+j];
           //printf("m[%d][%d] now = %lf\n", i, j, m[i][j]);
       }
       //printf("E_Yi[%d+1] = %lf\n", i, E_Yi[i+1]);
       m[i][poly_degree] = E_Yi[i+1];
       //printf("m[%d][%d] now = %lf\n", i, poly_degree, E_Yi[i+1]);

   }
   double sols[M];
   for(int i = 0; i < M; i++){
       sols[i] = 0;
   }
   int s; 

   //DEBUGGING PRINT STMTS
   //Output the original form 
   //printf("\nORIGINAL MATRIX:\n===========================\n");
   //print_matrix(m, poly_degree) ;

   s =  gaussian_elimination(m, poly_degree, sols);
   if (s == 0) {
     printf("gaussian_elimination with partial pivoting fails.\n") ;
     printf("There is no unique solution.\n") ;
     printf("The system may be inconsistent or underdetermined.\n") ;
     printf("This code does not distinguish between these last two situations.\n") ;
     exit(0) ;
   }

   //DEBUGGING PRINT STMTS
   // Output the modified form
   //print_matrix(m, poly_degree) ;

   // Ouptut the solution
   //printf("solutions:\n\n");
   //for (int r = 0 ; r < poly_degree ; r++) {
     //printf("%.16lf\n",sols[r]) ;
   //}
   //printf("\n") ;
   

   //----------------------------------------------------------------------PLOT THE BEST FIT POLYNOMIAL
   G_rgb(1,0,0) ;
   for (X = 0 ; X < 800 ; X++) {
     Y = 0;  
     for(int i = 0; i < num_unknowns; i++){
         Y += sols[i]*pow(X, i);
     }
     G_point(X,Y) ;
   }

   int key;   
   key = G_wait_key() ; // pause so user can see results

   G_save_image_to_file("best_fit_poly.xwd") ;

   }//end of while loop
}



