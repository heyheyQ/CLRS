/*
 * Exercise 9.3-7 in CLRS: 
 * The program implements the algorithm that, given a set S of n distinct numbers
 * and a positive integer k <= n, determines the k numbers in S that are closest
 * to the median of S, using randomized select functions.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "select.h" //the rand-select helper functions


int array[] = {9, 6, 14, 10, 1, 7, 3, 11, 16, 2, 8, 13, 5, 12, 15, 4};
int n = 16;
int m = 5;   //m elements are closest to the median

int
main (void)
{
  int rank;
  int rank2;
  int q;
  int median;
  int j;  //for debug
  int p, s;
  int idx1, idx2;

  if (n % 2 == 0) {
    rank = n/2;   //including q itself, <= n/2 elements
  } else {
    rank = n/2 + 1;
  }
  q = dselect (array, 0, n-1, rank);
//  printf ("array is at 0x%x\n", array);
  partition (array, 0, n-1, q);
  
  //for debug
  printf ("q = %d, array[q] = %d\n", q, array[q]);
  for (j = 0; j < n; j++) {
    printf ("%d  ", array[j]);
  }
  printf ("\n");
  median = q;

  rank2 = rank - m/2;
  p = 0;
  s = median-1;
  q = dselect (array, p, s, rank2);
  partition (array, p, s, q);
  //for debug
  printf ("q = %d, array[q] = %d\n", q, array[q]);
  for (j = 0; j < n; j++) {
    printf ("%d  ", array[j]);
  }
  printf ("\n");
  idx1 = q;

  p = median+1;
  s = n-1;
  if (m % 2  == 0) {
    rank2 = m/2;
  } else {
    rank2 = m/2 + 1; 
  }

  q = dselect (array, p, s, rank2);
  partition (array, p, s, q);
  //for debug
  printf ("q = %d, array[q] = %d\n", q, array[q]);
  for (j = 0; j < n; j++) {
    printf ("%d  ", array[j]);
  }
  printf ("\n");
  idx2 = q;

  printf ("answer:\n");
  for (j = idx1; j <= idx2; j++) {
    printf ("%d  ", array[j]);
  }
  printf ("\n");
  printf ("median = %d\n", array[median]);

  return 0;
}
