/*
 * Chap.15 in CLRS:
 * Dynamic Programming
 *
 * The program implements a dynamic programming algorithm to solve the problem of matrix-chain multiplication.
 * Given sequence (A1, A2, ..., An) of n matrices to be multiplied, 
 * compute the product A1A2...An, by deciding the parenthesized pairs which yield the minimum cost of evaluating the product.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>   //memset

#define MIN(a, b) ((a) < (b) ? (a) : (b))
////reconstruct sol
//typedef struct _NODE {
//  int i;
//  int j;
//} NODE;

//int p[] = {10, 100, 5, 50, 1};   //p0~pn
//int n = 4;                       //4 matrix multiplication
int p[] = {30, 35, 15, 5, 10, 20, 25};   //p0~pn
int n = 6;                       //4 matrix multiplication

//optimal cost
int
mulcost (
  int *p,
  int n
  );

//optimal cost and parenthesis
int
mulcost_v2 (
  int *p,
  int n,
  int **s
  );
//recursively print sol
void
Convert_Sol (
  int *s,
  int n,    //s = n*n
  int i,
  int j
  );

void
Convert_Sol_v2 (
  int *s,
  int n,    //s = n*n
  int i,
  int j
  );

////reconstruct sol
//NODE *
//Create_Node (
//  int i,
//  int j
//  );
//
//void
//push_stack (
//  NODE **stack,
//  int depth,
//  int *top,
//  NODE *item
//  );
//
//NODE *
//pop_stack (
//  NODE **stack,
//  int *top
//  );
//
//bool
//IsEmpty (
//  NODE **stack,
//  int top
//  );

int
main (void)
{
  int *sol = NULL;

//  printf ("answer: %d\n", mulcost (p, n));
  printf ("answer: %d\n", mulcost_v2 (p, n, &sol));

  Convert_Sol (sol, n, 1, n);   //i = 1, j = n
  printf ("\n");

  Convert_Sol_v2 (sol, n, 1, n);   //i = 1, j = n
  printf ("\n");

  //clean up
  free (sol);

  return 0;
}

int
mulcost (
  int *p,
  int n
  )
{
  int *m;    //m[i, j]: record cost
  int i, j, k;
  int cost;

  m = malloc (sizeof (int) * n * n);
  memset (m, 0, sizeof (int) * n * n);

  for (i = 1; i < n; i++) {
    //fill i-th column
    for (j = i-1; j >= 0; j--) {
      //compute m[j, i]
      cost = 0x7fffffff;
      //k = j~i-1
      for (k = j; k < i; k++) {
        //m[j, k] + m[k+1, i] + p[j-1]*p[k]*p[i]
        cost = MIN (cost, (m[n*j+k]+m[n*(k+1)+i]+p[j]*p[k+1]*p[i+1]));
      }
      m[n*j+i] = cost;
    }
  }

  //for debug
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      //print m[i, j]
      printf ("%d, ", m[n*i+j]);
    }
    printf ("\n");
  }

  //return m[1, n]
  return m[n-1];
}

//optimal cost and parenthesis
int
mulcost_v2 (
  int *p,
  int n,
  int **s
  )
{
  int *m;    //m[i, j]: record cost
  int i, j, k;
  int cost, q;

  m = malloc (sizeof (int) * n * n);
  memset (m, 0, sizeof (int) * n * n);

  //output
  *s = malloc (sizeof (int) * n * n);
  memset (*s, 0, sizeof (int) * n * n);

  for (i = 1; i < n; i++) {
    //fill i-th column
    for (j = i-1; j >= 0; j--) {
      //compute m[j, i]
      cost = 0x7fffffff;
      //k = j~i-1
      for (k = j; k < i; k++) {
        //m[j, k] + m[k+1, i] + p[j-1]*p[k]*p[i]
//        cost = MIN (cost, (m[n*j+k]+m[n*(k+1)+i]+p[j]*p[k+1]*p[i+1]));
        q = m[n*j+k]+m[n*(k+1)+i]+p[j]*p[k+1]*p[i+1];
        if (q < cost) {
         //s[j, i] = k
         (*s)[n*j+i] = (k+1);   //1-based
         cost = q; 
        }
      }
      m[n*j+i] = cost;
    }
  }

  //for debug
  printf ("cost:\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      //print m[i, j]
      printf ("%d, ", m[n*i+j]);
    }
    printf ("\n");
  }

  printf ("solution:\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      //print s[i, j]
      printf ("%d, ", (*s)[n*i+j]);
    }
    printf ("\n");
  }

  //return m[1, n]
  return m[n-1];
}

//recursively print sol
void
Convert_Sol (
  int *s,
  int n,    //s = n*n
  int i,
  int j
  )
{
//  NODE **stack;   //size = 2*n ??
//  int depth = 2*n;
//  int stack_top = -1;
//  NODE *tmp;
  int k;
//
//  //initialize
//  stack = malloc (sizeof (NODE *) * depth);

  //base case:
  if (i >= j) {
    return;
  }

  //convert the solution:
  //k = s[i, j], print (i, k) and (k+1, j)
  //recursive print (i, k)
  k = s[n*(i-1)+(j-1)];     //k is 1-based
//  printf ("i = %d, j = %d, k = %d\n", i, j, k);

  if (k > i) {
    printf ("(%d, %d), ", i, k);   //left
  }

  if (k+1 < j) {
    printf ("(%d, %d), ", k+1, j);   //right
  }

  Convert_Sol (s, n, i, k);
  Convert_Sol (s, n, k+1, j);

}

void
Convert_Sol_v2 (
  int *s,
  int n,    //s = n*n
  int i,
  int j
  )
{
  int k;

  if (i == j) {
    printf ("A%d", i);
  } else {
    k = s[n*(i-1)+(j-1)];
    printf ("(");
    Convert_Sol_v2 (s, n, i, k);
    Convert_Sol_v2 (s, n, k+1, j);
    printf (")");
  }
}

//NODE *
//Create_Node (
//  int i,
//  int j
//  )
//{
//  NODE *new;
//
//  new = malloc (sizeof (NODE));
//  new->i = i;
//  new->j = j;
//  
//  return new;
//}
//
//void
//push_stack (
//  NODE **stack,
//  int depth,
//  int *top,
//  NODE *item
//  )
//{
//  if (++(*top) >= depth) {
//    printf ("the stack is full.\n");
//    return;
//  }
//
//  stack[*top] = item;
//}
//
//NODE *
//pop_stack (
//  NODE **stack,
//  int *top
//  )
//{
//  if (*top < 0) {
//    printf ("the stack is empty.\n");
//    return NULL;
//  }
//  
//  return stack[(*top)--];
//}
//
//bool
//IsEmpty (
//  NODE **stack,
//  int top
//  )
//{
//  if (top >= 0) {
//    return false;
//  }
//  return true;
//}

