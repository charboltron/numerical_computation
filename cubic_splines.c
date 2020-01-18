
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
//include "system_solver.c"

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
   printf("\nCubic Spline Generator: Charles Bolton 2019"); 
   printf("\n====================================\n");
   printf("NOTICE: THIS PROGRAM RUNS IN A LOOP!");
   printf("\n====================================\n");
   printf("\nTo make testing this program easier, you can enter as many data sets as you like.\n");
   printf("\nINSTRUCTIONS:");
   printf("\n   1. Click up to the maximum allowable points from left to right.");
   printf("\n   2. Click the black margin to draw the cubic spline.");
   printf("\n   3. Hit the space bar to start over and enter a new data set.");
   printf("\n   4. If at anytime you wish to exit, enter 0.\n\n"); 
while(1){ 
   const int MAX_POINTS = 50; 

   int    swidth, sheight ;
   double p[2] ;
   double x[MAX_POINTS],y[MAX_POINTS] ;
   double X,Y ;
   int choice;
   int n;

   for(int i = 0; i < MAX_POINTS; i++){
        x[i] = y[i] = 0;
   }

   //Take user input before creating display
   printf("Please type 1 to create a cubic spline, or 0 to exit: ");
   scanf("%d", &choice);
   if(choice == 0){
       printf("Exiting Program. Thanks for trying.\n\n");
       exit(0);
   }
   
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
   n = 0;
   for(int i = 0; i < MAX_POINTS; i++){
     G_wait_click(p);
        if(p[0] > 800){
            //printf("\n\n==\n\n");
            n = i;
            i = MAX_POINTS;
            break;
        }
        x[i] = p[0] ; y[i] = p[1];
        if(i > 0 && x[i] < x[i-1]){
            printf("\nCubic Splines can only be generated if points are clicked left to right!\nTerminating program.\n\n.");
            exit(1);
        }
        G_fill_circle(x[i],y[i],2);
        if(i+1==MAX_POINTS){
            printf("\nYou've entered the maximum number of points. Let's not get too excited.\n\n");
            n = MAX_POINTS;
        }
   }

   //printf("\nNumber of points: %d\n", n);
   if(n < 3) {
       printf("This program doesn't work with less than 3 points (we are drawing cubic functions after all).\nTerminating.\n\n");
       exit(0);
   }
      
    // PRINT OUT THE CLICKED ABSCISSA AND ORDINATE
    // for(int i = 0; i < n; i++){
    //     printf("x[%d] = %lf", i, x[i]);
    //     printf("  y[%d] = %lf\n", i, y[i]);
    // }
   
   //--------------------------------------------------------------------------SYSTEM SOLVER 
   
   int n_u = (2*n)-2;
   //printf("\nNumber of unknowns: %d\n", n_u);
   double m[M][M+1];
   for(int i = 0; i < n_u; i++){
       for(int j =0; j< n_u+1; j++){
           m[i][j] = 0.0;
       }
   }
    
   m[0][0] = 1.0;
   m[0][1] = (x[1]-x[0])*-1.0;
   int _ = 1;
   
   //Fill up the matrix with the Tridiagonal Values and Augmented Solution vector
   for(int i = 1; i < n_u-1; i++){  //Start on 2nd row, end at penultimate row. 
       if(i % 2 != 0){//every odd row has this pattern  
            
            //printf("matrix row: %d has tracker = %d\n", i, _);
            m[i][i-1]  =     x[_]-x[_-1];
            m[i][i]    = pow(m[i][i-1], 2); //diagonal 
            m[i][i+1]  =     x[++_]-x[_-1];
            m[i][n_u]  = ((y[_]-y[_-1])/(x[_]-x[_-1]))-((y[_-1]-y[_-2])/(x[_-1]-x[_-2]));
       
       }else if(i % 2 == 0){//every even row has this pattern 

            m[i][i-1] =  m[i-1][i-1];
            m[i][i]   = (x[_]-x[_-2])*-1.0; //diagonal
            m[i][i+1] = (m[i-1][i-2]*m[i-1][i]);
            m[i][n_u] =  m[i-1][n_u]*-1.0;
       }
   }
   
   m[n_u-1][n_u-2] = 1.0; 
   m[n_u-1][n_u-1] = 2.0*(x[n-1]-x[n]); 
   m[n_u-1][n_u] = 0.0;
   
   double sols[M];
   for(int i = 0; i < M; i++){
       sols[i] = 0;
   }
   int s; 

   //DEBUGGING PRINT STMTS
   //Output the original form 
//    printf("\nORIGINAL MATRIX:\n===========================\n");
//    print_matrix(m, n_u) ;

   s =  gaussian_elimination(m, n_u, sols);
   if (s == 0) {
     printf("gaussian_elimination with partial pivoting fails.\n") ;
     printf("There is no unique solution.\n") ;
     printf("The system may be inconsistent or underdetermined.\n") ;
     printf("This code does not distinguish between these last two situations.\n") ;
     exit(0) ;
   }

   //DEBUGGING PRINT STMTS
   //Output the modified form
//    printf("UPPER TRIANGULAR MATRIX\n-------------------------\n");
//    print_matrix(m, n_u) ;

   //Ouptut the solution
//    printf("solutions:\n\n");
//    for (int r = 0 ; r < n_u; r++) {
//      printf("%.16lf\n",sols[r]) ;
//    }
//    printf("\n") ;
   

   //----------------------------------------------------------------------PLOT THE  SPLINE

   int sols_index = 0; 
   G_rgb(1,0,0) ; 
   for(int k = 1; k < n; k++){
       //printf("\nGenerating segment %d from x = %lf to x = %lf\n", k, x[k-1], x[k]);
       //printf("Equation %d is: S_%d(x) = y[%d] + (Q[%d]/P_one[%d])*(x-x[%d]) + (sols[%d]*(x-x[%d])*(x-x[%d])) + (sols[%d]*((i-x[%d])*(i-x[%d]))*(i-x[%d]))\n",k,k,k-1,k,k,k-1,sols_index,k-1,k,sols_index+1,k-1,k-1,k);
       
       for (int i = x[k-1]; i < x[k]; i++)
       {    
           Y =  y[k-1]
           +(((y[k]-y[k-1])/(x[k]-x[k-1]))*(i-x[k-1]))
           +(sols[sols_index]*(i-x[k-1])*(i-x[k]))
           +(sols[sols_index+1]*(pow((i-x[k-1]), 2)*(i-x[k])));
           //printf("Y = %lf\n", Y);
           G_point(i, Y);
       }
       sols_index+=2;
   }

   int key;   
   key = G_wait_key() ; // pause so user can see results

   G_save_image_to_file("best_fit_poly.xwd");
   }//end of while loop
}



