#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H

/*
 * minheap.h defines the helper functions
 * for min-heap.
 */ 

#define LEFT(i) (2*i)     //works only when index is 1-based
#define RIGHT(i) (2*i+1)  //works only when index is 1-based
#define HEIGHT(i) (floor(log2(i)))
#define PARENT(i) ((int)(i/2))  //wrong when index is 0-based
//#define PARENT(i) ((i % 2 == 0) ? (i/2 - 1) : ((int)(i/2)))  //when index is 0-based

struct HEAP {
  int A[100];
  int arraysize;  //100
  int heapsize;   //<=100
  int height;     //updated with the heapsize
};


void
minheapify (
  struct HEAP *h,
  int root
  );

void
buildminheap (
  struct HEAP *h      
  );

int
heap_minimum (
  struct HEAP *h      
  );

int
heap_extract_min (
  struct HEAP *h      
  );

void
minheap_decrease_key (
  struct HEAP *h,      
  int i,  //index to array: 0-based
  int key
  );

void
minheap_insert (
  struct HEAP *h,      
  int key
  );

void
printheap (
  struct HEAP *h      
  );

#endif
