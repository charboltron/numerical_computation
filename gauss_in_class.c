#include <stdio.h>
#include <stdlib.h>

double det(double **, int);
void gaussian_elimination(double **, double *, int);

int main () { 

    double ** A = malloc(4 * sizeof(double *));
    double * B = malloc(4 *sizeof(double *));

    for(int i = 0; i < 4; i++){
        A[i] = malloc(4*sizeof(double));
    }
    double a[16] = { 
                     3,  2,  4,  9, 
                    12, 15, 17, 44, 
                     6, 53, 21, 78,
                    18, 47, 83, 135 
                    };
    double b[4] = {9, 54, 122, -44};

    int n = 4;
    int index = 0; 
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            A[i][j] = a[index];
            index++;
        }
    }
    for(int i = 0; i<n; i++){
        B[i] = b[i];
    }
    
    // double x = det(A, n);
    // printf("%lf\n", x);
    gaussian_elimination(A, B, n);
}

void gaussian_elimination(double **A, double *B, int n){

    double ** A2 = malloc((n)*sizeof(double *));

    for(int i = 0; i < n; i++) {
        A2[i] = malloc(n+1 *sizeof(double));
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            A2[i][j] = A[i][j];
            printf("%d %d  ", i, j);
        }
    }
    
    for(int i = 0; i < n; i++){
        A2[i][n] = B[i];
    }
    
    printf("Initial Matrix: \n"); 
    for(int i = 0; i < n; i++){
        printf("\n");
        for(int j = 0; j < n+1; j++){
            printf("%.2lf  ", A2[i][j]);
        }
    }
    
    printf("\n");
    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j < n; j++){
            double temp = A2[j][i];
            for(int k = i; k < n+1; k++){
                printf("\n");
                printf("A2[%d][%d] = (A2[%d][%d]-(A2[%d][%d]*A2[%d][%d])/A2[%d][%d])\n", j, k, j, k, i, k, j, i, i, i);
                printf("    %.1lf    =  %.1lf  - %.1lf  *   %.1lf   /   %.1lf  ", A2[j][k], A2[j][k], A2[i][k], temp, A2[i][i]);

                A2[j][k] = (A2[j][k]-(A2[i][k]*temp)/A2[i][i]);
                                
                    for(int x = 0; x < n; x++){
                        printf("\n");
                        for(int y = 0; y < n+1; y++){
                            printf("%.2lf  ", A2[x][y]);
                        }
                    }
            }   
        }
    }
}

double det(double **A, int n) {

    double ** minor = malloc(n *sizeof(double*));

    for(int i = 0; i < n; i++){
        minor[i] = malloc(n *sizeof(double));
    }

    int i, j, k, c1, c2;
    int determ;
    int c[n];
    int sign = 1;

    
    determ = 0;
    if(n == 2)
    {
        determ = A[0][0]*A[1][1]-A[0][1]*A[1][0];
        return determ;
    }
    else
    {
        for(i = 0 ; i < n ; i++)
        {
            c1 = 0, c2 = 0;
            for(j = 0 ; j < n ; j++)
            {
                for(k = 0 ; k < n ; k++)
                {
                    if(j != 0 && k != i)
                    {
                        minor[c1][c2] = A[j][k];
                        c2++;
                        if(c2>n-2)
                        {
                            c1++;
                            c2=0;
                        }
                    }
                }
            }
            determ = determ + sign*(A[0][i]*det(minor,n-1));
            sign=-1*sign;
        }
    }
    return determ;
}

    


