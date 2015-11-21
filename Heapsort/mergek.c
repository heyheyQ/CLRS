/*
 * Exercise 6.5-9 in CLRS:
 * The programs implements an algorithm to merge k sorted lists into one sorted list
 * using a min-heap.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "minheap.h" //the helper functions for min-heap

//merge k sorted slots:
//int array[] = {7, 9, 10, 11, 15, \
//2, 4, 13, 17, 19, \
//1, 3, 5, 6, 8};

int array[] = {11, 12, 13, 14, 15, \
6, 7, 8, 9, 10, \
1, 2, 3, 4, 5};

int part[] = {0, 5, 10};  //index of the start of the slots
int k = 3;   //sizeof (part)/sizeof (int)
int n = 15;  //each slot has n/k elements

struct HEAP *pheap;

int
main (void)
{
  int j;
  int num;
  int *bound;
  
  num = n/k;
  //initial
  pheap = malloc (sizeof (struct HEAP));
  memset (pheap, 0, sizeof (struct HEAP));
  pheap->arraysize = 100;
  for (j = 0; j < pheap->arraysize; j++) {
    pheap->A[j] = 0x7fffffff;
  }

  bound = malloc (sizeof (int)*k);
  for (j = 0; j < k; j++) {
    bound[j] = (j+1)*num;
  }

  printf ("printheap: ");
  printheap (pheap);
  //first round
  for (j = 0; j < k; j++) {
    if (part[j] < bound[j]) {
      minheap_insert (pheap, array[part[j]++]);
      printf ("printheap: ");
      printheap (pheap);
    } 
  }

  printheap (pheap);

  while (pheap->heapsize > 0) {
    printf ("%d  ", heap_extract_min (pheap)); 
//    //for debug
//    printf ("min: %d\n", heap_extract_min (pheap)); 
//    printf ("printheap: ");
//    printheap (pheap);
    
    for (j = 0; j < k; j++) {
      if (part[j] < bound[j]) {
        minheap_insert (pheap, array[part[j]++]);  //should only insert the next element in slot k, where the extract_min from!!
      } 
    }
  }
  printf ("\n");

//  while (pheap->heapsize > 0) {
//    for (j = 0; j < k; j++) {
//      if (pheap->heapsize <= 0) break; 
//      printf ("%d  ", heap_extract_min (pheap)); 
//      if (part[j] < bound[j]) {
//        minheap_insert (pheap, array[part[j]++]);
//      } 
//    }    
//  }
//  printf ("\n");

  return 0;
}

