/*
 * The program implements the randomized select algorithm 
 * to select the ith smallest of n elements. 
 * select.c contains the helper functions to solve order statistics problems.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "select.h"

// move the definitions to select.h
//void
//swap (
//  int *a,
//  int *b
//  );
//
//int
//randpart (
//  int *A,
//  int p,
//  int s
//  );
//
//int
//randselect (
//  int *A,
//  int p,
//  int s,
//  int rank
//  );
//
//int array[] = {11, 6, 10, 13, 5, 8, 3, 2, 1};
//int n = 9;
//
//int
//main (void)
//{
//  int result = 0;
//
//  srand (time (NULL));
//
//  result = randselect (array, 0, n-1, 5);
//
//  printf ("result = %d\n", result);
//  return 0;
//}

int
randpart (
  int *A,
  int p,
  int s
  )
{
  int pivot;
  int num;
  int i, r;
  int key;

  if (s <= p) {
    return -1;
  }

  num = s-p+1;
  pivot = p + rand ()%num;

  swap (&A[p], &A[pivot]);
  key = A[p];
  for (i = p+1, r = p; i <= s; i++) {
    if (A[i] < key) {
      swap (&A[i], &A[++r]);
    }
  }
  swap (&A[p], &A[r]);  //important!!
  return r;
}

int
randselect (
  int *A,
  int p,
  int s,
  int rank
  )
{
  int i;
  int irank;

  i = randpart (A, p, s);
  irank = i-p+1;
  if (rank < irank) {
    //recursively select on left
    randselect (A, p, i, rank);
  } else if (rank > irank) {
    rank -= irank;
    randselect (A, i+1, s, rank);
  } else {
    //found!
    return A[i];
  }
}

void
swap (
  int *a,
  int *b
  )
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

int
dselect (
  int *A,
  int p,
  int s,
  int rank
  )
{
  int i;
  int irank;
  int j;   //for debug

  i = randpart (A, p, s);
  irank = i-p+1;
  //for debug
//  printf ("in dselect: rank = %d, irank = %d\n", rank, irank);
//  printf ("in dselect: i = %d, A[i] = %d\n", i, A[i]);
//  for (j = p; j <= s; j++) {
//    printf ("%d  ", A[j]);
//  }
//  printf ("\n");

  if (rank < irank) {
    //recursively select on left
    dselect (A, p, i, rank);
  } else if (rank > irank) {
    rank -= irank;
    dselect (A, i+1, s, rank);
  } else {
    //found!
//    return A[i];
//    printf ("in dselect: i = %d, A[i] = %d\n", i, A[i]);
    return i;
  }
}

void
partition (
  int *A,
  int p,
  int s,
  int idx    //partitioning around A[idx]
  )
{
  int i, r;
  int key;

  if (idx < p || idx > s) {
    //invalid idx
    return;
  }
//  printf ("A is at 0x%x\n", A);
  printf ("p = %d, s = %d, idx = %d\n", p, s, idx);
  //for debug
  for (i = p; i <= s; i++) {
    printf ("%d  ", A[i]);
  }
  printf ("\n");

  key = A[idx];
  printf ("key = %d\n", key);
  swap (&A[p], &A[idx]);
  for (i = p+1, r = p; i <= s; i++) {
    if (A[i] < key) {
      swap (&A[i], &A[++r]);
    } 
  }
  swap (&A[p], &A[r]);
  //A[p] ~ A[r]  : <= key
  //A[r+1] ~ A[s]: > key
  printf ("in partition: r = %d\n", r);
  return;
}

