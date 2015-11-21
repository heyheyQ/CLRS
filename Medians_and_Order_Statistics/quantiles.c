/*
 * Exercise 9.3-6 in CLRS: 
 * The kth quantiles of an n-element set are the k-1 order statistics
 * that divide the sorted set into k equal-sized sets.
 * The program implements the algorithm to list the kth quantiles of a set
 * using randomized select functions.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "select.h" //the rand-select helper functions

//int array[] = {1, 2, 4, 8, 6, 7, 3, 5};
//int n = 8;
//int k = 4;  //return k-1=3 elements to partition

int array[] = {9, 6, 14, 10, 1, 7, 3, 11, 16, 2, 8, 13, 5, 12, 15, 4};
int n = 16;
int k = 8; 

struct _LIST {
  int data;
  struct _LIST *next;
} LIST;

void
quantiles (
  int *A,
  int p,
  int s,  //idx of A
  int k,
  struct _LIST **head
  );

int
main (void)
{
//  int *ans;
//  int j;
  struct _LIST *h;
  struct _LIST *temp;

  srand (time (NULL));
//  ans = malloc (sizeof (int) * (k-1));
//  memset (ans, 0, sizeof (int) * (k-1));
 
  h = NULL;  //initial
  quantiles (array, 0, n-1, k, &h);

//  for (j = 0; j < k-1; j++) {
//    printf ("%d  ", ans[j]);    
//  }
//  printf ("\n");

  while (h) {
    printf ("%d  ", h->data);
    temp = h;
    h = h->next;
    free (temp);
  }
  printf ("\n");

  return 0;
}

void
quantiles (
  int *A,
  int p,
  int s,  //idx of A
  int k,
  struct _LIST **head
  )
{
  int size;
  int rank;
  int r;
  int i;  //for debug
  struct _LIST *node;

  //base case !
  if (k == 1) {
    return;    
  }

  size = s-p+1;
//  printf ("size/2 = %d\n", size/2);
//  if (size % 2 == 0) {
//    rank = size/2;   
//  } else {
    rank = size/2 + 1;  //??    
//  }
  printf ("size = %d, rank = %d\n", size, rank);

  r = dselect (A, p, s, rank);
  partition (A, p, s, r);
  
  //for debug
  printf ("r = %d\n", r);
  for (i = p; i <= s; i++) {
    printf ("%d  ", A[i]);
  }
  printf ("\n");

//  *Q = A[r];    //update Q
//  printf ("*Q = %d\n", *Q);
  //insert to list
  node = malloc (sizeof (struct _LIST));
  node->data = A[r];
  node->next = *head;
  *head = node;           //insert to head

  quantiles (A, p, r-1, k/2, head);
  quantiles (A, r+1, s, k/2, head);

}

