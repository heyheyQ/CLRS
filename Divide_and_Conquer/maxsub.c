/*
 * The program recursively finds the maximum-subarray 
 * which has the greatest sum of any contiguous subarray of the given array
 * using a divide-and-conquer algorithm.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//int A[] = {7, 9, 5, -1};
//int n = 4;  //size of array

//int A[] = {-4, 1, 2, -4, 3};
//int n = 5;

//int A[] = {13, -3, -25, 20, -3, -16, -23, 18, 20};
//int n = 9;
//int A[] = {-7, 12, -5, -22, 15, -4, 7};
//int n = 7;

int A[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
int n = 16;

void
submax (
  unsigned int high,
  unsigned int low,
  unsigned int mid,
  unsigned int *i,
  unsigned int *j,
  int *sum
);

int
main (void)
{
  unsigned int fi, fj, mid; 
  int fsum;

  fi = 0;
  fj = 0;
  fsum = 0;
  mid = (unsigned int)(ceil((float)(n-1)/(float)2));
  printf ("in main: mid = %d\n", mid);
  submax (n-1, 0, mid, &fi, &fj, &fsum);

  printf ("result: fi = %d, fj = %d, fsum = %d\n", fi, fj, fsum);
  return 0;
}


void
submax (
  unsigned int high,
  unsigned int low,
  unsigned int mid,
  unsigned int *i,
  unsigned int *j,
  int *sum
)
{
  unsigned int li, lj, ri, rj;
  int lsum, rsum;
  int tmpsum;
  int k;

  *i = 0;
  *j = 0;
  *sum = 0;
  tmpsum = 0;
  k = 0;

  printf ("high = %d, low = %d, mid = %d\n", high, low, mid);
  //base case:
  // (1) n == 1
  if (high == low && high == mid) {
    *i = mid; 
    *j = mid; 
    *sum = A[mid]; 
    return;
  }

  if (high - low == 1) {
    *sum = A[low];
    *i = low;
    *j = low;
    if (A[high] > *sum) {
      *sum = A[high];
      *i = high;
      *j = high;
    }
    if (A[low] + A[high] > *sum) {
      *sum = A[low] + A[high];
      *i = low;
      *j = high;
    }
    return;
  }

  //left divide
  li = 0;  
  lj = 0;  
  lsum = 0;  
  submax (mid, low, (unsigned int)(ceil((float)(mid+low)/(float)2)), &li, &lj, &lsum);
  printf ("li = %d, lj = %d, lsum = %d\n", li, lj, lsum);

  //right divide
  ri = 0;  
  rj = 0;  
  rsum = 0;  
  submax (high, (mid+1), (unsigned int)(floor((float)(high+mid+1)/(float)2)), &ri, &rj, &rsum);
  printf ("ri = %d, rj = %d, rsum = %d\n", ri, rj, rsum);

  //merge: cross sum ? 
  *sum = lsum;
  *i = li;
  *j = lj;
  if (rsum > *sum) {
    *sum = rsum;
    *i = ri;
    *j = rj;

    //cross sum
    tmpsum = 0;
    for (k = rj; k >= (int)li; k--) {
      printf ("k = %d\n", k);
      tmpsum += A[k];
      if (tmpsum > *sum) {
       *sum = tmpsum;
       *i = k;
      }
    }
  } else {
    //cross sum
    tmpsum = 0;
    for (k = li; k <= rj; k++) {
      printf ("k = %d\n", k);
      tmpsum += A[k];
      if (tmpsum > *sum) {
       *sum = tmpsum;
       *j = k;
      }
    }
  }
  printf ("merge: mid = %d, *i = %d, *j = %d, *sum = %d\n", mid, *i, *j, *sum);

  return;
}
