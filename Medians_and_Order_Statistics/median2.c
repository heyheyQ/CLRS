/*
 * Exercise 9.3-8 in CLRS:
 * Let X[1..n] and Y[1..n] be two arrays, each containing n numbers already in sorted order.
 * The program implements an algorithm to find the median of all 2n elements in arrays X and Y.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//X, Y are already sorted
//int X[] = {2, 4, 6, 8, 10};
//int Y[] = {1, 3, 5, 7, 9};
//int n = 5;

int X[] = {1, 3, 5, 7, 9, 11};
int Y[] = {2, 4, 6, 8, 10, 12};
int n = 6;

int
median2 (
  int *X,
  int px,
  int sx,
  int *Y,
  int py,
  int sy
  );

int
median (
  int *A,
  int p,
  int s
  );

int
main (void)
{
  int result = 0;

  result = median2 (X, 0, n-1, Y, 0, n-1);

  printf ("result = %d\n", result);
  return 0;
}

int
median2 (
  int *X,
  int px,
  int sx,
  int *Y,
  int py,
  int sy
  )
{
  int i, j;
  int sizex, sizey;

  sizex = sx-px+1;
  sizey = sy-py+1;
  
  //for debug
  int k;
  printf ("X:  ");
  for (k = px; k <= sx; k++) {
    printf ("%d  ", X[k]);    
  }
  printf ("\n");
  printf ("Y:  ");
  for (k = py; k <= sy; k++) {
    printf ("%d  ", Y[k]);    
  }
  printf ("\n");

  //base case!
//  if (sx-px+1 <= 2 && sy-py+1 <= 2) {
  if (sizex <= 2 && sizey <= 2) {
    //brute-force to solve 3 or 4 elements    
    int F[4];  //for debug
    if (X[px] > Y[py]) {
      F[0] = Y[py];
      if (X[px] > Y[sy]) {
        F[1] = Y[sy];    
      } else {
        F[1] = X[px];    
      }
    } else {
      F[0] = X[px];    
      if (Y[py] > X[sx]) {
        F[1] = X[sx];    
      } else {
        F[1] = Y[py];    
      }
    }
    return F[1];
  }
//  //base case, too!
//  if (sx-px+1 == 1 && sy-py+1 == 1) {
//    if (X[px] > Y[py]) {
//      return Y[py];    
//    } else {
//      return X[px];    
//    }
//  }

  i = median (X, px, sx);
  j = median (Y, py, sy);

  if (X[i] > Y[j]) {
//    median2 (X, px, i, Y, j, sy);     
    if (sizex % 2 == 0) {
      median2 (X, px, i-1, Y, j, sy);     
    } else {
      median2 (X, px, i, Y, j, sy);     
    }
  } else {
//    median2 (X, i, sx, Y, py, j);     
    if (sizex % 2 == 0) {
      median2 (X, i+1, sx, Y, py, j);     
    } else {
      median2 (X, i, sx, Y, py, j);     
    }
  }
}

int
median (
  int *A,
  int p,
  int s
  )
{
  //A is already sorted!
  int idx;
  
  idx = (p+s)/2;
//  printf ("idx = %d\n", idx);  //for debug
  return idx;
}
