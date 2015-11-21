/*
 * The program implements an insertion sort algorithm
 * using binary-search to find where to insert an element.
 */ 

#include <stdio.h>
#include <stdlib.h>

//int array[] = {3, 7, 8, 5, 4, 1, 2};
//int n = 7;

//int array[] = {11, 6, 10, 13, 5, 8, 3, 2, 1};
//int n = 9;

int array[] = {3, 2, 1, 3, 5, 6, 7, 8};
int n = 8;

int
binary_search (
  int *A,
  int p,
  int s,
  int key
  );

void
insertion2 (
  int *A,
  int n
  );

int
main (void)
{
  int k;

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

  insertion2 (array, n);

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

  return 0;
}

int
binary_search (
  int *A,
  int p,
  int s,
  int key
  )
{
  int mid;
  while (s >= p) {
    mid = (s+p)/2;
    if (A[mid] > key) {
      //search left
      s = mid-1;
    } else if (A[mid] < key) {
      //search right
      p = mid+1;
    } else {
      return mid+1;  //stable
    }
  }
  return p;  //s < p
}

void
insertion2 (
  int *A,
  int n
  )
{
  int j, i, x;
  int item;

  for (j = 1; j < n; j++) {
    item = A[j];
    x = binary_search (A, 0, j-1, item);  
    for (i = j-1; i >= x; i--) {
      A[i+1] = A[i]; 
    }
    A[i+1] = item;
  }
}

