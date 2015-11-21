#ifndef _SELECT_H
#define _SELECT_H

/*
 * The header file defines randomized select helper functions
 * which are used to solve order statistics problems.
 */ 

void
swap (
  int *a,
  int *b
  );

int
randpart (
  int *A,
  int p,
  int s
  );

int
randselect (
  int *A,
  int p,
  int s,
  int rank
  );

//return index
int
dselect (
  int *A,
  int p,
  int s,
  int rank
  );

//determinstic partition
void
partition (
  int *A,
  int p,
  int s,
  int idx    //partitioning around A[idx]
  );

#endif
