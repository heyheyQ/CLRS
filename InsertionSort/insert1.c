/*
 * The program implements an insertion sort algorithm
 * which sorts an array in either ascending or descending order.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int array[] = {3, 7, 8, 5, 4, 1, 2};
int n = 7;

void
swap (
  int *s1,
  int *s2
  );

bool
ascending (
  int x,
  int y
  );

bool
descending (
  int x,
  int y
  );

void
insertion1 (
  int *A,
  int n,
  bool (*f)(int, int)
  );

int
main (void)
{
  int k;

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

  insertion1 (array, n, descending);

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

  return 0;
}

bool
ascending (
  int x,
  int y
  )
{
  if (x > y) {
    return true;
  }
  return false;
}

bool
descending (
  int x,
  int y
  )
{
  if (x < y) {
    return true;
  }
  return false;
}

void
insertion1 (
  int *A,
  int n,
  bool (*f)(int, int)
  )
{
  int j, i;
  int item;

  for (j = 1; j < n; j++) {
    item = A[j];
    for (i = j-1; i >= 0 && f(A[i], item); i--) {
      A[i+1] = A[i];
    } 
    A[i+1] = item;
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

