/*
 * minheap.c implements the helper functions
 * for min-heap.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>  //log2

#include "minheap.h"

//#define LEFT(i) (2*i)
//#define RIGHT(i) (2*i+1)
//#define HEIGHT(i) (floor(log2(i)))
////#define PARENT(i) ((int)(i/2))  //wrong when index is 0-based
//#define PARENT(i) ((i % 2 == 0) ? (i/2 - 1) : ((int)(i/2)))

//struct HEAP {
//  int A[100];
//  int arraysize;  //100
//  int heapsize;   //<=100
//  int height;     //updated with the heapsize
//};

void
swap (
  int *s1,
  int *s2
  );

//global var
struct HEAP mheap = { \
    {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1}, \
    100, \
    12, \
    HEIGHT(12) \
};

//void
//minheapify (
//  struct HEAP *h,
//  int root
//  );
//
//void
//buildminheap (
//  struct HEAP *h      
//  );
//
//int
//heap_minimum (
//  struct HEAP *h      
//  );
//
//int
//heap_extract_min (
//  struct HEAP *h      
//  );
//
//void
//minheap_decrease_key (
//  struct HEAP *h,      
//  int i,  //index to array: 0-based
//  int key
//  );
//
//void
//minheap_insert (
//  struct HEAP *h,      
//  int key
//  );
//
//void
//printheap (
//  struct HEAP *h      
//  );

//int
//main (void)
//{
//  printheap (&mheap);
//  buildminheap (&mheap);
//  printheap (&mheap);
//
//  printf ("minimum = %d\n", heap_minimum(&mheap));
//  printheap (&mheap);
//  printf ("minimum = %d\n", heap_extract_min(&mheap));
//  printheap (&mheap);
//
//  minheap_decrease_key (&mheap, 10, 3);
//  printheap (&mheap);
//
//  minheap_insert (&mheap, 0);  //key = 0
//  printheap (&mheap);
//  //functions tests
//
//  return 0;
//}

void
minheapify (
  struct HEAP *h,
  int root    //index is 1-based
  )
{
  int smallest;

//  printf ("root = %d, h->A[root] = %d\n", root, h->A[root]);
  //base case 1:
  if (HEIGHT (root) == h->height) {
    //leaf
    return;
  }

  smallest = root;

  if (LEFT (root) <= h->heapsize) {
    if (h->A[LEFT (root)-1] < h->A[smallest-1]) {
      smallest = LEFT (root);
    }
  }

  if (RIGHT (root) <= h->heapsize) {
    if (h->A[RIGHT (root)-1] < h->A[smallest-1]) {
      smallest = RIGHT (root);
    }
  }

  if (smallest != root) {
//    printf ("h->A[smallest] = %d\n", h->A[smallest]);
    swap (&h->A[root-1], &h->A[smallest-1]);
    minheapify (h, smallest);
  }

//  //base case 2:
//  if (LEFT (root) > heapsize || RIGHT (root) > heapsize) {
//    return;
//  }
}

void
buildminheap (
  struct HEAP *h      
  )
{
  int leaf;
  int i;

  leaf = h->heapsize/2;
//  printf ("leaf = %d\n", leaf);
//  for (i = leaf-1; i >= 0; i--) {  //index is 0-based
  for (i = leaf; i > 0; i--) {       //index is 1-based
    minheapify (h, i);
  }

}

int
heap_minimum (
  struct HEAP *h      
  )
{
  return h->A[0];
}

int
heap_extract_min (
  struct HEAP *h      
  )
{
  int min;

  min = h->A[0];
  swap (&h->A[0], &h->A[(h->heapsize-1)]);
  h->heapsize -= 1;
  h->height = HEIGHT (h->heapsize);  //update!

//  minheapify (h, 0);
  minheapify (h, 1);   //index is 1-based

  return min;
}

void
minheap_decrease_key (
  struct HEAP *h,      
  int i,  //index to array: 1-based
  int key
  )
{
  int j;

  if (i > h->heapsize) {
    //invalid index
    return;
  }
  if (h->A[i-1] < key) {
    //invalid key
    return;
  }

  h->A[i-1] = key;
  //update root
  j = i;
//  while (j > 0) {
  while (j > 1) {    //index is 1-based
//    printf ("parent = %d\n", h->A[PARENT (j)]);
    if (h->A[PARENT (j)-1] < h->A[j-1]) {
      break;
    }
    //swap with parent
    swap (&h->A[PARENT (j)-1], &h->A[j-1]);
    j = PARENT (j);
  }

}

void
minheap_insert (
  struct HEAP *h,      
  int key
  )
{
  //add a new element
  if (++h->heapsize > h->arraysize) {
    h->heapsize--;
    return;   //no more space
  }

  h->height = HEIGHT (h->heapsize);  //update!
  h->A[(h->heapsize-1)] = 0x7fffffff;   //maximum
//  minheap_decrease_key (h, h->heapsize-1, key);
  minheap_decrease_key (h, h->heapsize, key);  //index is 1-based

}

void
printheap (
  struct HEAP *h      
  )
{
  int i;

  for (i = 0; i < h->heapsize; i++) {
    printf ("%d  ", h->A[i]);
  }
  printf ("\n");
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

