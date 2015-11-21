/*
 * The heap data structure is an array object that we can view as a nearly complete binary tree.
 * In a max-heap, the max-heap property is that for every node i other than the root, 
 * A[parent(i)] >= A[i].
 * The program demonstrates the max-heap-insert, heap-extract-max, heap-increase-key, 
 * and heap-maximum procedures, which allow the heap data structure to implement a priority-queue.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>  //floor, ceil

#define LEFT(i) (2*i)
#define RIGHT(i) (2*i+1)
#define HEIGHT(i) (floor(log2(i)))
#define PARENT(i) ((int)(i/2))

struct HEAP {
  int A[100];
  int arraysize;  //100
  int heapsize;   //<=100
  int height;     //updated with the heapsize
};

void
swap (
  int *s1,
  int *s2
  );

void
maxheapify (
  struct HEAP *h,      
  int i
  );

int
heap_maximum (
  struct HEAP *h      
  );

int
heap_extract_max (
  struct HEAP *h      
  );

void
heap_increase_key (
  struct HEAP *h,
  int i,  //index to array
  int key
  );

void
max_heap_insert (
  struct HEAP *h,
  int key
  );

//global var
struct HEAP mheap = { \
    {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1}, \
    100, \
    12, \
    HEIGHT(12) \
};

int
main (void)
{
  int k;

  for (k = 0; k < mheap.heapsize; k++) {
    printf ("%d  ", mheap.A[k]);
  }
  printf ("\n");

  printf ("heapsize = %d, height = %d\n", mheap.heapsize, mheap.height);

  printf ("max = %d\n", heap_maximum (&mheap));
//  printf ("max = %d\n", heap_extract_max (&mheap));
//  heap_increase_key (&mheap, 9, 14);
  max_heap_insert (&mheap, 10);

  for (k = 0; k < mheap.heapsize; k++) {
    printf ("%d  ", mheap.A[k]);
  }
  printf ("\n");

  printf ("heapsize = %d, height = %d\n", mheap.heapsize, mheap.height);

  return 0;
}

int
heap_maximum (
  struct HEAP *h      
  )
{
  return h->A[0];
}

int
heap_extract_max (
  struct HEAP *h      
  )
{
  int max;
  max = h->A[0];

  swap (&(h->A[0]), &(h->A[h->heapsize-1]));
  h->heapsize-=1;
  h->height = HEIGHT (h->heapsize);  //updated!

  maxheapify (h, 1);  //1: root

  return max;
}

void
heap_increase_key (
  struct HEAP *h,
  int i,  //index to array
  int key
  )
{
  int parent;

  if (i > h->heapsize || i < 1) {
    //invalid i
    return;
  }
  if (key < h->A[i-1]) {
    //invalid key
    return;
  }

  h->A[i-1] = key;  //updated!
  parent = PARENT (i);
  while ((parent >= 1) && (h->A[i-1] > h->A[parent-1])) {
    swap (&(h->A[i-1]), &(h->A[parent-1])); 
    i = parent;
    parent = PARENT (i);
  }

}

void
max_heap_insert (
  struct HEAP *h,
  int key
  )
{
//  short test;
//  test = 0x7FFF;
//  printf ("%d\n", test);  //for debug
//  test = 0x8000;
//  printf ("%d\n", test);  //for debug
//  test = 0x8001;
//  printf ("%d\n", test);  //for debug

  h->A[h->heapsize] = (int)0x80000000;
//  printf ("%d\n", h->A[h->heapsize]);  //for debug
  h->heapsize++;
  heap_increase_key (h, h->heapsize, key);
}

void
maxheapify (
  struct HEAP *h,      
  int i
  )
{
  int largest, l, r;
  largest = i;

  //base case!
  if (HEIGHT ((float)i) == h->height) {
    return;
  }
  //leaf
  if (LEFT(i) > h->heapsize && RIGHT(i) > h->heapsize) {
    return;
  }

  l = LEFT (i);
  if (l <= h->heapsize) {
    if (h->A[l-1] > h->A[largest-1]) {
      largest = l;
    }
  }
  r = RIGHT (i);
  if (r <= h->heapsize) {
    if (h->A[r-1] > h->A[largest-1]) {
      largest = r;    
    }
  }
  //swap
  if (largest != i) {
    swap (&(h->A[largest-1]), &(h->A[i-1]));
    //execute only when (largest != i), important!
    maxheapify (h, largest); //only recursively solve on the modified subtree.
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

