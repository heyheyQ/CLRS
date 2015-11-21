/*
 * Problem 2-3. Weighted Median
 * For n distinct elements x1, x2, ..., xn with positive weights w1, w2, ..., wn
 * such that sum(wi, i=1~n) = 1, the weighted median is the element xk satisfying
 * sum(wi, xi<xk) < 1/2 and sum(wi, xi>xk) <= 1/2.
 * The program computes the weighted median of n elements using sorting.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "select.h"


int array[] = {3, 6, 5, 4, 1, 7, 2};
//float weights[] = {1/20, 3/28, 1/7, 1/7, 1/5, 3/28, 1/4};
//enhanced weights[]: weights(A[i]) = W[A[i]]
float weights[] = {0, (float)1/5, (float)1/4, (float)1/20, (float)1/7, (float)1/7, (float)3/28, (float)3/28};
int n = 7;

int
weight_median (
  int *A,
  float *W,
  int p,
  int s,
  float la,     //accumulated left sum
  float lb      //accumulated right sum
  );

int
main (void)
{
  int result = 0;

  result = weight_median (array, weights, 0, n-1, (float)0, (float)0);

  printf ("result = %d\n", result);

  return 0;
}

int
weight_median (
  int *A,
  float *W,
  int p,
  int s,
  float la,     //accumulated left sum
  float lb      //accumulated right sum
  )
{
  int size;
  int rank;
  int i;
  int j;
  float ola, olb;
  ola = la;
  olb = lb;
  printf ("original: ola = %f, olb = %f\n", ola, olb);

  size = s-p+1;
  if (size % 2 == 0) {
    rank = size/2;
  } else {
    rank = size/2 + 1;
  }

  i = dselect (A, p, s, rank);
//  partition (A, p, s, i);
  printf ("i = %d, A[i] = %d\n", i, A[i]);
  //for debug
  for (j = p; j <= s; j++) {
    printf ("%d  ", A[j]);
  }
  printf ("\n");

  for (j = p; j <= s; j++) {
    if (A[j] < A[i]) {
      la += W[A[j]];
    } else if (A[j] > A[i]) {
      lb += W[A[j]];
    }
  }
  printf ("la = %f, lb = %f\n", la, lb);

  //binary-search to right or left
  if (la >= (float)1/2) {
    weight_median (A, W, p, i-1, ola, (lb+W[A[i]]));
  } else if (lb > (float)1/2) {
    weight_median (A, W, i+1, s, (la+W[A[i]]), olb);
  } else {
    //found!
    return A[i];
  }

}

