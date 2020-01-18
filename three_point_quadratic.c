
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
*/





/*

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


int main()
{
   int    swidth, sheight ;
   double p[2] ;
   double x[3],y[3] ;
   double X,Y ;
   
   // must do this before you do 'almost' any other graphical tasks 
   swidth = 800 ;  sheight = 800 ;
   G_init_graphics (swidth,sheight) ;  // interactive graphics

   
   // clear the screen in a given color
   G_rgb (0.3, 0.3, 0.3) ; // dark gray
   G_clear () ;


   G_rgb(1,1,0) ;
   
   G_wait_click(p) ;
   x[0] = p[0] ; y[0] = p[1] ;
   G_fill_circle(x[0],y[0],2) ;
   
   G_wait_click(p) ;
   x[1] = p[0] ; y[1] = p[1] ;
   G_fill_circle(x[1],y[1],2) ;
   
   G_wait_click(p) ;
   x[2] = p[0] ; y[2] = p[1] ;   
   G_fill_circle(x[2],y[2],2) ;

   
   G_rgb(1,0,0) ;
   for (X = 0 ; X < 800 ; X++) {
     Y =   y[0] * (X - x[1])*(X - x[2]) / ((x[0] - x[1])*(x[0] - x[2]))
        +  y[1] * (X - x[0])*(X - x[2]) / ((x[1] - x[0])*(x[1] - x[2]))
        +  y[2] * (X - x[0])*(X - x[1]) / ((x[2] - x[0])*(x[2] - x[1])) ;

     G_point(X,Y) ;
   }
   
   
   int key ;   
   key =  G_wait_key() ; // pause so user can see results

   G_save_image_to_file("three_point_quadratic.xwd") ;
}



