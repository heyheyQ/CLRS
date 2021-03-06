/*
 * The heap data structure is an array object that we can view as a nearly complete binary tree.
 * In a max-heap, the max-heap property is that for every node i other than the root, 
 * A[parent(i)] >= A[i].
 * The program demonstrates the max-heapify procedure, 
 * which maintains the max-heap property of an array.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>  //log2

#define LEFT(i) (2*i)
#define RIGHT(i) (2*i+1)
#define HEIGHT(i) (floor(log2(i)))

void
swap (
  int *s1,
  int *s2
  );

void
maxheapify (
  int *A,
  int i
  );

int array[] = {3, 6, 7, 2, 4, 1, 5};  //0~6 => 1~7
int n = 7;                            //global var: heapsize
float h = 0;

int
main (void)
{
  int k;
//  float h = 0;
  h = HEIGHT ((float)n);
  printf ("h = %f\n", h);

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

  maxheapify (array, 1);

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

  return 0; 
}

void
maxheapify (
  int *A,
  int i
  )
{
  int largest, l, r;
  largest = i;

  //base case!
  if (HEIGHT ((float)i) == h) {
    return;
  }

  l = LEFT (i);
  if (l <= n) {
    if (A[l-1] > A[largest-1]) {
      largest = l;
    }
  }
  r = RIGHT (i);
  if (r <= n) {
    if (A[r-1] > A[largest-1]) {
      largest = r;    
    }
  }
  //swap
  if (largest != i) {
    swap (&A[largest-1], &A[i-1]);
  }

  printf ("largest = %d\n", largest);
  maxheapify (A, largest); //only recursively solve on the modified subtree.
  //wrong!!
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

