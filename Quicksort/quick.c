/*
 * The program demonstrates quicksort which applies a divide-and-conquer paradigm.
 * (1) choose a pivot to partition the array into 2 subarrays.
 * (2) sort the 2 subarrays by recursive calls to quicksort.
 * (3) there's no need to combine 2 subarrays; the entire array is now sorted.
 */ 

#include <stdio.h>
#include <stdlib.h>

int
partition (
  int *A,
  int p,
  int q
  );

void
quicksort (
  int *A,
  int p,
  int q
  );

//int array[] = {6, 10, 13, 5, 8, 3, 2, 11};
//int n = 8;

int array[] = {11, 6, 10, 13, 5, 8, 3, 2, 1};
int n = 9;

int
main (void)
{
  int k;

  //before sorting
  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

  quicksort (array, 0, n-1);  //sort in place
  
  //after sorting
  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

  return 0;
}

int
partition (
  int *A,
  int p,
  int q
  )
{
  //range: A[p]~A[q]
  //return: pivot r
  int i, j;
  int pivot;
  int temp;  //for swap

  pivot = A[p];  //first element
  i = p;
  for (j = p+1; j <= q; j++) {
    if (A[j] <= pivot) {
      //swap A[i+1] and A[p]
      i = i + 1;
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }
  //swap A[p] and A[i]
  A[p] = A[i];
  A[i] = pivot;

  return i;
}


void
quicksort (
  int *A,
  int p,
  int q
  )
{
  //initial: p = 0, q = n-1
  int r;
  int b;

  //base case !
  if (q <= p) {
    return;
  }

  r = partition (A, p, q);
  printf ("p = %d, q = %d, r = %d\n", p, q, r);
  //recursively solve
  quicksort (A, p, r-1);
  quicksort (A, r+1, q);
}


