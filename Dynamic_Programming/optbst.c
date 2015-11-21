/*
 * Chap.15 in CLRS:
 * Dynamic Programming
 *
 * The program implements a dynamic programming algorithm 
 * to solve the problem of optimal binary search trees.
 * Given a sequence K = {k1, k2, ..., kn} of n distinct keys in sorted order,
 * for each key ki, we have a probability pi that a search will be for ki;
 * we also have n+1 "dummy keys" d0, d1, ..., dn representing values not in K, 
 * for each dummy key di, we have a probability qi that a search will correspond to di.
 * For a given set of probabilities, we wish to construct a binary search tree 
 * whose expected search cost is smallest.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

//float p[] = {0.15, 0.10, 0.05, 0.10, 0.20};
//float q[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
//int n = 5;
float p[] = {0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};
float q[] = {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};
int n = 7;

void
optbst (
  float *p,
  float *q,
  int n,
  float **e,    //output
  int **root    //output
  );

//wrapper
void
construct_optbst (
  int *root,
  int n            //(n+1)*(n+1)
  );

void
Recur_Print (
  int *root,
  int n,
  int parent,
  int i,
  int j
  );

int
main (void)
{
  float *ecost;
  int *root;
//  int col, row;
//
//  col = n+1;   //i = 1~n+1
//  row = n+1;   //j = 0~n

  optbst (p, q, n, &ecost, &root);
  
  printf ("ans = %.2f, root = %d\n", ecost[n], root[n]);

  construct_optbst (root, n);

  //clean up
  free (ecost);
  free (root);

  return 0;
}

void
optbst (
  float *p,     //p[1]~p[n]
  float *q,     //q[0]~q[n]
  int n,
  float **e,    //output
  int **root    //output
  )
{
  //build table e[i, j]:
  //the ans is e[1, 5]
  //e[i, j] = min (e[i, r-1]+e[r+1, j]) + w[i, j], r=i~j
  
  //w[i, j]: helping table
  //w[i, j] = w[i, j-1]+p[j]+q[j]
  //base case: w[i, i-1] = q[i-1]

  float *w;
  int wrow, wcol;
  int i, j;
  float *ee;
  int erow, ecol;
  int *rr;       //record the decisions
  int ridx;
  float emin;
  int rmin;
  float etmp;

  wrow = n+1;    //i = 1~n+1
  wcol = n+1;    //j = 0~n

  w = malloc (sizeof (float) * wrow * wcol);
  //construct w
  //base case:
  for (i = 1; i <= n+1; i++) {
    //row i: 1-based  
    w[(i-1)*wcol+(i-1)] = q[i-1];
  }
  for (i = 1; i <= n+1; i++) {
    for (j = i; j <= n; j++) {
      //w[i, j] = w[i, j-1]+p[j]+q[j]
      //row i: 1-based
      w[(i-1)*wcol+j] = w[(i-1)*wcol+(j-1)]+p[(j-1)]+q[j];  //p[]: 1-based
    }
  }

  //for debug
  for (i = 1; i <= n+1; i++) {
    for (j = 0; j <= n; j++) {
      printf ("%.2f, ", w[(i-1)*wcol+j]);
    }
    printf ("\n");
  }
  printf ("\n");
 
  erow = n+1;    //i = 1~n+1
  ecol = n+1;    //j = 0~n

  ee = malloc (sizeof (float) * erow * ecol);
  rr = malloc (sizeof (int) * erow * ecol);
  //construct ee and rr
  //base case:
  //ee[i, i-1] = q[i-1]
  for (i = 1; i <= n+1; i++) {
    //row i: 1-based
    ee[(i-1)*ecol+(i-1)] = q[i-1];
  }
//bug, wrong order to fill up
//  for (i = 1; i <= n+1; i++) {
//    for (j = i; j <= n; j++) {
//      //ee[i, j] = min(ee[i, r-1]+ee[r+1, j]) + w[i,j], r = i~j
//      //row i: 1-based
//      emin = (float)0x7fffffff;
//      printf ("emin = %.2f\n", emin);   //for debug
//      for (ridx = i; ridx <= j; ridx++) {
////        emin = MIN ((ee[(i-1)*ecol+(ridx-1)]+ee[ridx*ecol+j]), emin);
//        etmp = ee[(i-1)*ecol+(ridx-1)]+ee[ridx*ecol+j];
//        printf ("etmp = %.2f, ridx = %d\n", etmp, ridx);   //for debug
//        if (etmp < emin) {
//          rmin = ridx;
//          emin = etmp;
//        }
//      }
//      //fill up ee[i, j]
//      ee[(i-1)*ecol+j] = emin + w[(i-1)*wcol+j];
//      rr[(i-1)*ecol+j] = rmin;
//    }
//  }

  for (j = 1; j <= n; j++) {
    for (i = j; i >= 1; i--) {
      //fill up by columns
      emin = (float)0x7fffffff;
      rmin = i;
      for (ridx = i; ridx <= j; ridx++) {
//      for (ridx = j; ridx >= i; ridx--) {
        etmp = ee[(i-1)*ecol+(ridx-1)]+ee[ridx*ecol+j] + w[(i-1)*wcol+j];
        printf ("etmp = %.2f, ridx = %d\n", etmp, ridx);   //for debug
        if (etmp < emin) {
          rmin = ridx;
          emin = etmp;
        }
      }
      //fill up ee[i, j]
      ee[(i-1)*ecol+j] = emin;
      rr[(i-1)*ecol+j] = rmin;
    }
  }

  //ans = ee[1, n]
  *e = ee;
  *root = rr;

  //for debug
  for (i = 1; i <= n+1; i++) {
    for (j = 0; j <= n; j++) {
      printf ("%.2f, ", ee[(i-1)*ecol+j]);
    }
    printf ("\n");
  }
  printf ("\n");
 
  for (i = 1; i <= n+1; i++) {
    for (j = 0; j <= n; j++) {
      printf ("%d, ", rr[(i-1)*ecol+j]);
    }
    printf ("\n");
  }

  //clean up
  free (w);
}

//wrapper
void
construct_optbst (
  int *root,
  int n            //(n+1)*(n+1)
  )
{
  int i, j;
  int col;
  int parent;

  col = n+1;
  //start from root[1, n]:
  //root[i, j]: i is 1-based, j is 0-based
  i = 1;
  j = n;

  parent = root[(i-1)*col+j];
  printf ("k%d is the root.\n", parent);
  Recur_Print (root, n, parent, i, j);

}

void
Recur_Print (
  int *root,
  int n,
  int parent,
  int i,
  int j
  )
{  
  int col;
  int nextp;

  col = n+1;

  if (parent-1 == i-1) {
    //base case
    printf ("d%d is the left child of k%d.\n", i-1, parent);
  } else {
    nextp = root[(i-1)*col+(parent-1)];
    printf ("k%d is the left child of k%d.\n", nextp, parent);
    Recur_Print (root, n, nextp, i, parent-1);
  }

  if (parent == j) {
    //base case
    printf ("d%d is the right child of k%d.\n", j, parent);
  } else {
    nextp = root[(parent)*col+j];
    printf ("k%d is the right child of k%d.\n", nextp, parent);
    Recur_Print (root, n, nextp, parent+1, j);
  }
}
