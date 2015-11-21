/*
 * Section 2.1 of CLRS:
 * The program implements insertion sort.
 */ 

#include <stdio.h>
#include <stdlib.h>

int array[] = {3, 7, 8, 5, 4, 1, 2};
int n = 7;

void
swap (
  int *s1,
  int *s2
  );

void
insertion_sort (
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

  insertion_sort (array, n);

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

  return 0;
}

void
insertion_sort (
  int *A,
  int n
  )
{
  int j, i;

  for (j = 1; j < n; j++) {
    for (i = j-1; i >= 0; i--) {
      if (A[i] < A[i+1]) {
        break;
      }
      swap (&A[i], &A[i+1]);
    }
  }
}

void
swap (
  int *s1,
  int *s2
  )
{
  int temp;

  temp = *s1;
  *s1 = *s2;
  *s2 = temp;
}

