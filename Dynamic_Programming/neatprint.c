/*
 * Problem 15-4 of CLRS:
 *
 * The program implements a dynamic programming algorithm to solve the printing neatly problem.
 * The input text is a sequence of n words of lengths l1, l2, ..., ln, measured in characters.
 * We want to print this paragraph neatly on a number of lines that hold a maximum of M characters each.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>   //memset

#define MIN(a, b) ((a) < (b) ? (a) : (b))

char *s[] = {"Hello", "swettie", "horrible", "we", "are", "family", "exciting"};

int n = 7;
int m = 17;

int
neatprint (
  char **s,
  int *l,
  int n,
  int m
  );

int
main (void)
{
  int k;
  int *l;

  l = malloc (sizeof (int) * n);   //lengh of words
  for (k = 0; k < n; k++) {
    l[k] = strlen (s[k]);
  }

  //for debug
  printf ("length of words:\n");
  for (k = 0; k < n; k++) {
    printf ("%d, ", l[k]);
  }
  printf ("\n");

  //test
  printf ("the ans is %d whitespaces minimum.\n", neatprint (s, l, n, m));

  //clean up
  free (l);

  return 0;
}

int
neatprint (
  char **s,
  int *l,
  int n,
  int m
  )
{
  //build cost[i, j], c[i, j]
  int *cost;
  int i, j, r;
  int col;
  int sum;
  int *c;
  int *colmin;   //for reconstruct
  int min;
  int *stack;
  int stack_top;

  col = n;
  cost = malloc (sizeof (int) * n * n);
  memset (cost, 0, sizeof (int) * n * n);
  //cost[i, j] = M-(j-i)-sum(li~ij)
  //base case:
  for (i = 0; i < n; i++) {
    cost[i*col+i] = m-l[i];
  }

  for (i = 0; i < n; i++) {
    for (j = i+1; j < n; j++) {
      sum = cost[i*col+(j-1)]-l[j]-1;
      if (sum < 0) {
        sum = 0x7fffffff;
      }
      cost[i*col+j] = sum;
    }
  }

  c = malloc (sizeof (int) * n * n);
  memset (c, 0, sizeof (int) * n * n);
  //c[i, j] = min(c[r, i-1]+cost[i, j]), r = 0~i-1
  //base case: row 0
  for (j = 0; j < n; j++) {
    c[j] = cost[j];
  }

  for (i = 1; i < n; i++) {
    for (j = i; j < n; j++) {
      sum = 0x7fffffff;
      for (r = 0; r < (i-1); r++) {
        sum = MIN(sum, c[r*col+(i-1)]);     
      }
      if (sum != 0x7fffffff && cost[i*col+j] != 0x7fffffff) {
        c[i*col+j] = sum + cost[i*col+j]; 
      } else {
        c[i*col+j] = 0x7fffffff; 
      }
    }
  }

  //find the min at col[n-1]
  sum = 0x7fffffff;
  for (i = 0; i < n; i++) {
    sum = MIN(sum, c[i*col+(col-1)]);
  }

  //reconstruct
  colmin = malloc (sizeof (int) * 2 * n);
  //row 0: minimum of the row
  //row 1: the idx for reconstruct
  for (j = 0; j < n; j++) {
    min = 0x7fffffff;
    for (i = 0; i <= j; i++) {
      if (c[i*col+j] < min) {
        min = c[i*col+j];
        colmin[1*col+j] = i-1;
      }
      colmin[j] = min;
    }
  }

  //for debug
  printf ("for reconstruct:\n");
  for (i = 0; i < n; i++) {
    printf ("%d, ", colmin[1*col+i]);
  }
  printf ("\n");

  //push to stack
  stack = malloc (sizeof (int) * n);
  stack_top = -1;
  for (j = n-1; colmin[1*col+j] > 0; ) {
    stack[++stack_top] = colmin[1*col+j];
    j = colmin[1*col+j];
  }

//  //for debug
//  printf ("In the stack:\n");
//  for (i = stack_top; i >= 0; i--) {
//    printf ("%d, ", stack[i]);
//  }
//  printf ("\n");

  //print in lines: word(i)~word(j)
//  for (i = 0; i < n; ) {
//    j = stack[stack_top--];
//    for (r = i; r < j; r++) {
//      printf ("%s ", s[r]);
//    }
//    printf ("%s\n", s[r]);
//
//    i = j+1;
//  }

  i = 0;
  while (stack_top >= 0) {
    j = stack[stack_top--];
    for (r = i; r < j; r++) {
      printf ("%s ", s[r]);
    }
    printf ("%s\n", s[r]);

    i = j+1;
  }

  for (r = i; r < (n-1); r++) {
    printf ("%s ", s[r]);
  }
  printf ("%s\n", s[r]);

  //clean up
  free (cost);
  free (c);
  free (colmin);
  free (stack);

  return sum;
}

