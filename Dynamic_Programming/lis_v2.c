/*
 * Exercise 15.4-6 of CLRS:
 *
 * The program implements a dynamic programming algorithm 
 * to solve the problem of longest increasing subsequence, to find the longest monotonically
 * increasing subsequence of a sequence of n numbers.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

//longest increasing subsequence
int
Lis_Length_v2 (
  char *x
  );

//input
char x[] = "ABCBDAB";
//char x[] = "DABCBDA";

int
main (void) 
{
  printf ("the answer is %d\n", Lis_Length_v2 (x));

  return 0;    
}

//longest increasing subsequence
int
Lis_Length_v2 (
  char *x
  )
{
  //build L[i, j]: in x[j..n], the length of the subsequence > x[i]
  int len;
  int row, col;
  int i, j;
  int *L;
  char *newx;

  len = strlen (x);
  newx = malloc (sizeof (char) * (len+2));
  strcpy ((char *)(newx+1), x);
  newx[0] = (char)0x80;    //minus infinity
//  printf ("newx[0] = %d\n", (int)newx[0]);  //for debug

  L = malloc (sizeof (int) * (len+1) * (len+2));
  row = len + 1;
  col = len + 2;
  //first col = minus infinity
  //last col = 0
  for (i = 0; i < row; i++) {
    L[i*col] = 0x80;   //char = int8
    L[i*col+(col-1)] = 0;
  }
  
  for (j = len; j > 0; j--) {
    for (i = len; i >= 0; i--) {  //bug??
//    for (i = 0; i <= j-1; i++) {
      //fill up L[i, j]
      if (newx[i] >= newx[j]) {
        L[i*col+j] = L[i*col+(j+1)];
      } else {
        L[i*col+j] = MAX(L[j*col+(j+1)]+1, L[i*col+(j+1)]);
      }
    }
  }

  //for debug
  for (i = 0; i < row; i++) {
    for (j = 1; j < col; j++) {
      printf ("%d, ", L[i*col+j]);
    }
    printf ("\n");
  }

  //reconstruct from L[0, 1]
  i = 0;
  j = 1;
  while (L[i*col+j] > 0) {
    if (newx[i] >= newx[j]) {
      j = j+1;    
    } else {
      if (L[j*col+(j+1)] + 1 >= L[i*col+(j+1)]) {
        printf ("%c", newx[j]);
        i = j;
        j = j+1;
      } else {
        j = j+1;    
      }    
    }  
  }
  printf ("\n");

  return L[1];    //L[0, 1]
}

