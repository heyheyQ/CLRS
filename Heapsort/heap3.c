/*
 * The heap data structure is an array object that we can view as a nearly complete binary tree.
 * In a max-heap, the max-heap property is that for every node i other than the root, 
 * A[parent(i)] >= A[i].
 * The program demonstrates the heapsort procedure, 
 * which runs in O(nlgn) time, sorts an array in place.
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

void
buildmaxheap (
  int *A,
  int heapsize
  );

void
heapsort (
  int *A  //heapsize is global var
  );

//int array[] = {5, 3, 17, 10, 84, 19, 6, 22, 9};
//int n = 9;                            //global var: heapsize
int array[] = {5, 3, 17, 10, 84, 19, 6, 22, 9, 96};
int n = 10;                            //global var: heapsize
int size;  //heapsize
float h = 0;

int
main (void)
{
  int k;
//  float h = 0;
  h = HEIGHT ((float)n);
  size = n;
  printf ("h = %f\n", h);

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

//  maxheapify (array, 1);
//  buildmaxheap (array, n);
  heapsort (array);

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

  return 0; 
}

void
heapsort (
  int *A
  )
{
//wrong!
//  do {
//    buildmaxheap (A, size);
//    swap (&A[0], &A[size-1]);
//    size--;
//  } while (size > 2);
  int k;

  buildmaxheap (A, n);  //after this, every subtree is a max-heap!
  //for debug
  for (k = 0; k < n; k++) {
    printf ("%d  ", A[k]);
  }
  printf ("\n");

  swap (&A[0], &A[n-1]);
  //after swap, all the subtrees are max-heaps except for the root!
  size = n-1;
  //for debug
  for (k = 0; k < n; k++) {
    printf ("%d  ", A[k]);
  }
  printf ("\n");

  while (size > 2) {
    maxheapify (A, 1);  //1: root  
    //after swap, all the subtrees are max-heaps except for the root!
    swap (&A[0], &A[size-1]);
    size--;
    //for debug
    for (k = 0; k < n; k++) {
      printf ("%d  ", A[k]);
    }
    printf ("\n");

  }
}

void
buildmaxheap (
  int *A,
  int heapsize
  )
{
  int leaf, i;
  leaf = (int)floor((float)heapsize/2);

//  printf ("leaf = %d\n", leaf);
  for (i = leaf; i > 0; i--) {
//    printf ("A[%d] = %d\n", i, A[i-1]);
    maxheapify (A, i);
  }
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
  //leaf
  if (LEFT(i) > size && RIGHT(i) > size) {  //size: global var, heapsize
    return;
  }

  l = LEFT (i);
  if (l <= size) {
    if (A[l-1] > A[largest-1]) {
      largest = l;
    }
  }
  r = RIGHT (i);
  if (r <= size) {
    if (A[r-1] > A[largest-1]) {
      largest = r;    
    }
  }
  //swap
  if (largest != i) {
    swap (&A[largest-1], &A[i-1]);
//    printf ("largest: A[i] = %d\n", A[i-1]);
    //execute only when (largest != i), important!
    maxheapify (A, largest); //only recursively solve on the modified subtree.
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



