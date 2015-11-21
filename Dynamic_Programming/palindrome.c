/*
 * Problem 15-2 of CLRS:
 *
 * The program implements a dynamic programming algorithm 
 * to solve the problem of longest palindrome subsequence.
 * A palindrome is a nonempty string over some alphabet that reads the same forward and backward.
 * Give an efficient algorithm to find the longest palindrome that is a subsequence 
 * of a given input string.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>   //memset

#define MAX(a, b) ((a) > (b) ? (a) : (b))

//char x[] = "character";
char x[] = "1524332451";

int
palindrome (
  char *x      
  );

int
lcs (
  char *x,
  char *y
  );

void
reconstruct (
  char *x,
  int *l,
  int row,
  int col
  );

void
reconstruct_v2 (
  char *x,
  int *l,
  int row,
  int col
  );

int
main (void)
{
  printf ("length of palindrome = %d\n", palindrome (x));

  return 0;
}

int
palindrome (
  char *x      
  )
{
  int len;
  char *y;
  int i;

  len = strlen (x);
  y = malloc (sizeof (char) * (len+1));
  for (i = 0; i < len; i++) {
    y[i] = x[len-1-i];
  }
  y[i] = '\0';

  return lcs(x, y);
}

int
lcs (
  char *x,
  char *y
  )
{
  int *l;
  int len;
  int row, col;
  int i, j;

  len = strlen (x);
  row = len + 1;
  len = strlen (y);
  col = len + 1;

  printf ("x: %s, y: %s\n", x, y);

  l = malloc (sizeof (int) * row * col);
  memset (l, 0, sizeof (int) * row * col);

  for (i = 1; i < row; i++) {
    for (j = 1; j < col; j++) {
      if (x[i-1] == y[j-1]) {
        l[i*col+j] = l[(i-1)*col+(j-1)] + 1;
      } else {
        l[i*col+j] = MAX (l[(i-1)*col+j], l[i*col+(j-1)]);
      }
    }
  }

  //for debug
  for (i = 1; i < row; i++) {
    for (j = 1; j < col; j++) {
      printf ("%d, ", l[i*col+j]);
    }
    printf ("\n");
  }

  reconstruct (x, l, row, col);
  reconstruct_v2 (x, l, row, col);

  return l[(row-1)*col+(col-1)];
}

void
reconstruct (
  char *x,
  int *l,
  int row,
  int col
  )
{
  int i, j;

  i = row-1;
  j = col-1; 
  while (l[i*col+j] != 0) {
    if (l[i*col+j] == l[(i-1)*col+j]) {
      i = i-1;
    } else if (l[i*col+j] == l[i*col+(j-1)]) {
      j = j-1;
    } else if (l[i*col+j] == l[(i-1)*col+(j-1)] + 1) {
      printf ("%c", x[i-1]);
      i = i-1;
      j = j-1;
    }
  }
  printf ("\n");
}

void
reconstruct_v2 (
  char *x,
  int *l,
  int row,
  int col
  )
{
  int i, j;

  i = row-1;
  j = col-1; 
  while (l[i*col+j] != 0) {
    if (l[i*col+j] == l[i*col+(j-1)]) {
      j = j-1;
    } else if (l[i*col+j] == l[(i-1)*col+j]) {
      i = i-1;
    } else if (l[i*col+j] == l[(i-1)*col+(j-1)] + 1) {
      printf ("%c", x[i-1]);
      i = i-1;
      j = j-1;
    }
  }
  printf ("\n");
}
