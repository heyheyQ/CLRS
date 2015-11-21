/*
 * Chap.15 in CLRS:
 * Dynamic Programming
 *
 * The program implements a dynamic programming algorithm to solve the rod-cutting problem.
 * Given a rod of length n inches and a table of prices pi for i = 1, 2, ..., n,
 * determine the maximum revenue rn obtainable by cutting up the rod and selling the pieces.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //memset

//price for length 0~10
int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

#define MAX(a, b) ((a) > (b) ? (a) : (b))

//recursive version
int 
Cut_Rod (
  int *p,
  int n
  );

//top-down version
int
Cut_Rod_TopDown (
  int *p,
  int n
  );

int 
TopDownHelper (
  int *p,
  int n,
  int *r    //1-d array for memoziation
  );

int
Cut_Rod_TopDown_v2 (
  int *p,
  int n,
  int **pieces,
  int *k                //size of pieces
  );

int 
TopDownHelper_v2 (
  int *p,
  int n,
  int *r,              //1-d array for memoziation
  int *pieces          //1-d array for choices recording
  );

//bottom-up version
int
Cut_Rod_BottomUp (
  int *p,
  int n
  );

int
Cut_Rod_BottomUp_v2 (
  int *p,
  int n,
  int **pieces,
  int *k                //size of pieces
  );

int
main (void)
{
  int n;
  int *pieces;
  int psize;
  int ans;
  int i;

  //test
  n = 9;
  printf ("Recursive:\n");
  printf ("when n = %d, answer = %d\n", n, Cut_Rod (p, n));
  printf ("Top-Down:\n");
  printf ("when n = %d, answer = %d\n", n, Cut_Rod_TopDown (p, n));
  printf ("Bottom-Up:\n");
  printf ("when n = %d, answer = %d\n", n, Cut_Rod_TopDown (p, n));

  pieces = NULL;
  psize = 0;
  ans = Cut_Rod_BottomUp_v2 (p, n, &pieces, &psize);
  printf ("Bottom-Up v2:\n");
  printf ("when n = %d, answer = %d\n", n, ans);
  for (i = 0; i < psize; i++) {
    printf ("%d, ", pieces[i]);    
  }
  printf ("\n");

  //clean up
  free (pieces);
  psize = 0;

  printf ("Bottom-Up v2:\n");
  printf ("when n = %d, answer = %d\n", n, Cut_Rod_TopDown_v2 (p, n, &pieces, &psize));
  printf ("optimal cuts:\n");
  for (i = 0; i < psize; i++) {
    printf ("%d, ", pieces[i]);    
  }
  printf ("\n");

  //clean up
  free (pieces);
  psize = 0;

  return 0;
}

//recursive version
int 
Cut_Rod (
  int *p,
  int n
  )
{
  //r(n) = max (p[i] + r(n-i)), for i = 1~n
  int i;
  int q;

  //base case:
  if (n == 0) {
    return 0;
  }

  q = 0x80000000;    //initial max value
  for (i = 1; i <= n; i++) {
    q = MAX(q, p[i]+Cut_Rod (p, n-i));
  }

  return q;
}

//top-down version
int
Cut_Rod_TopDown (
  int *p,
  int n
  )
{
  int *r;
  int i;
  int q;

  r = malloc (sizeof (int) * (n+1));   //optimal cost for lenght 0~n
  memset (r, 0, sizeof (int) * (n+1));
  for (i = 1; i <= n; i++) {
    r[i] = 0x80000000;   //minus infinity
  }

//  //for debug
//  q = TopDownHelper (p, n, r);
//  for (i = 0; i <= n; i++) {
//    printf ("%d, ", r[i]);
//  }
//  printf ("\n");
//
//  return q;
  return TopDownHelper (p, n, r);
}

int 
TopDownHelper (
  int *p,
  int n,
  int *r    //1-d array for memoziation
  )
{
  int i;
  int q;

  //base case:
  if (r[n] >= 0) {
    return r[n];     //already solved, just return the value.
  }

  //top-down recursion
  q = 0x80000000;
  for (i = 1; i <= n; i++) {
//    q = MAX(q, p[i]+r[n-i]);  //wrong, cause r[n-i] may not be solved yet.
    q = MAX(q, p[i] + TopDownHelper (p, n-i, r));
  }

  r[n] = q;   //store the result
  return r[n];
}

int
Cut_Rod_TopDown_v2 (
  int *p,
  int n,
  int **pieces,
  int *k                //size of pieces
  )
{
  int *r;
  int i;
  int q;
  int *pout;
  int *pout2;
  int psize;
  int tmp;

  //initialize
  r = malloc (sizeof (int) * (n+1));   //optimal cost for lenght 0~n
  memset (r, 0, sizeof (int) * (n+1));
  for (i = 1; i <= n; i++) {
    r[i] = 0x80000000;   //minus infinity
  }

  pout = malloc (sizeof (int) * n);   //cut to n pieces maximum
  memset (pout, 0, sizeof (int) * n);

  //for debug
  q = TopDownHelper_v2 (p, n, r, pout);
  printf ("revenue:\n");
  for (i = 0; i <= n; i++) {
    printf ("%d, ", r[i]);
  }
  printf ("\n");
  printf ("cut size:\n");
  for (i = 0; i < n; i++) {
    printf ("%d, ", pout[i]);
  }
  printf ("\n");

//  //output
  pout2 = malloc (sizeof (int) * n);   //cut to n pieces maximum
  memset (pout2, 0, sizeof (int) * n);
  psize = 0;
  for (i = n; i > 0; ) {
    pout2[psize++] = pout[i-1];
    tmp = pout[i-1];
    i = i-tmp;
  }

  *pieces = pout2;
  *k = psize;

  //clean up
  free (pout);

  return q;
//  return TopDownHelper (p, n, r);
}

int 
TopDownHelper_v2 (
  int *p,
  int n,
  int *r,              //1-d array for memoziation
  int *pieces          //1-d array for choices recording
  )
{
  int i;
  int q;
  int tmp;

  //base case:
  if (r[n] >= 0) {
    return r[n];     //already solved, just return the value.
  }

  //top-down recursion
  q = 0x80000000;
  for (i = 1; i <= n; i++) {
//    q = MAX(q, p[i]+r[n-i]);  //wrong, cause r[n-i] may not be solved yet.
//    q = MAX(q, p[i] + TopDownHelper (p, n-i, r));
    tmp = p[i] + TopDownHelper_v2 (p, n-i, r, pieces);
    if (tmp > q) {
      q = tmp;
      pieces[n-1] = i;
    }
  }

  r[n] = q;   //store the result
  return r[n];
}

//bottom-up version
int
Cut_Rod_BottomUp (
  int *p,
  int n
  )
{
  int *r;
  int i, j;
  int q;

  //initialize
  r = malloc (sizeof (int) * (n+1));
  memset (r, 0, sizeof (int) * (n+1));
  for (i = 1; i <= n; i++) {
    r[i] = 0x80000000;   //minus infinity
  }

  q = 0x80000000;
  for (i = 1; i <= n; i++) {
    //build the table: r[1]~r[n]
    for (j = 1; j <= i; j++) {
      r[i] = MAX(r[i], p[j] + r[i-j]);    //r[i-j] has been solved before r[i] for j >= 1, important!
    }
  }

  //for debug
  for (i = 0; i <= n; i++) {
    printf ("%d, ", r[i]);
  }
  printf ("\n");

  return r[n];
}

int
Cut_Rod_BottomUp_v2 (
  int *p,
  int n,
  int **pieces,
  int *k                //size of pieces
  )
{
  int *r;
  int i, j;
  int q;
  int *pout;
  int kout;
  int *pout2;
  int last;

  //initialize
  r = malloc (sizeof (int) * (n+1));
  memset (r, 0, sizeof (int) * (n+1));
  for (i = 1; i <= n; i++) {
    r[i] = 0x80000000;   //minus infinity
  }

  //record "choices"
  pout = malloc (sizeof (int) * n);   //max: n slices
  memset (pout, 0, sizeof (int) * n);
  kout = 0;  

  q = 0x80000000;
  for (i = 1; i <= n; i++) {
    //build the table: r[1]~r[n]
    for (j = 1; j <= i; j++) {
//      r[i] = MAX(r[i], p[j] + r[i-j]);    //r[i-j] has been solved before r[i] for j >= 1, important!
      if ((p[j] + r[i-j]) > r[i]) {
        r[i] = p[j] + r[i-j];
        pout[kout] = j;
//        printf ("i = %d, j = %d, kout = %d\n", i, j, kout);
      }
    }
    kout++;     //idx of choices
  }

//  //for debug
//  for (i = 0; i < kout; i++) {
//    printf ("%d, ", pout[i]);    
//  }
//  printf ("\n");

  //output
  pout2 = malloc (sizeof (int) * kout);
  memset (pout2, 0, sizeof (int) * kout);

  for (i = n, j = 0; i > 0; ) {
    pout2[j] = pout[i-1];   //first cut
    last = pout2[j];
    j++;
    i = i-last;
  }

//  *pieces = pout;  //bug
//  *k = kout;

  *pieces = pout2;
  *k = j;

  //clean up
  free (pout);

  return r[n];
}
