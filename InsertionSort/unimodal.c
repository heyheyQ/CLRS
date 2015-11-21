/*
 * An array A[1..n] is unimodal if it consists of an increasing sequence
 * followed by a decreasing sequence.
 * The program finds the unique locally maximum element A[m], such that A[m-1] < A[m] amd A[m+1] < A[m].
 */ 


#include <stdio.h>
#include <stdlib.h>

//int src[] = {1, 3, 5, 10, 7, 4};
//int n = 6;  //size of array

//int src[] = {7, 12, 31, 23, 18, 6, 3};
//int n = 7;  //size of array

//int src[] = {1, 3, 4, 5, 10, 7};
//int n = 6;  //size of array

int src[] = {23, 31, 18, 9, 7, 6, 3};
int n = 7;  //size of array

int
main (void)
{
  int low = 0;
  int up = n - 1;
  int mid;
  int found = -1;
  int cnt = 0;   //performance recording

  while (found < 0) {
    mid = (low + up)/2 + 1;  //should be 3 at first 
    printf ("mid = %d\n", mid);
//bug 
   if (mid <= 0) {
     found = 1;
     mid = 0;
     break;
   } else if (mid >= (n-1)) {
     found = 1;
     mid = (n-1);
     break;
   } 
    
    cnt++;

    if (src[mid - 1] > src[mid]) {
      low = 0;
      up = mid - 1;
    } else if (src[mid + 1] > src[mid]) {
      low = mid + 1;
      up = n;
    } else {
      found = 1;
      break;
    }
//bug
    if (low >= up) {
      found = 1;
      mid = up;
    } else if (up <= low) {
      found = 1;
      mid = low;
    }
  }

  printf ("mid = %d, maximum : %d, cnt = %d\n", mid, src[mid], cnt);
  return 0;
}
