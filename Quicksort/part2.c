/*
 * The program demonstrates a randomized version of quicksort.
 * The pivot element to partition the array is randomly chose.
 *
 */ 

#include <stdio.h>
#include <stdlib.h>  //srand, rand
#include <time.h>

struct PAIR{
  int q;
  int t;
};

void
swap (
  int *s1,
  int *s2
  );

struct PAIR
part2 (
  int *A,
  int p,
  int r
  );

struct PAIR
randpart2 (
  int *A,
  int p,
  int r
  );

void
quick2 (
  int *A,
  int p,
  int r
  );

int array[] = {6, 5, 4, 6, 7, 9, 6, 2, 3};
int n = 9;

//int array[] = {13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21};
//int n = 12;

int
main (void)
{
  int k;
  struct PAIR output = {-1, -1};

  srand (time (NULL));

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

//  output = part2 (array, 0, n-1); 
//  printf ("output: q = %d, t = %d\n", output.q, output.t);
//  output = randpart2 (array, 0, n-1); 
//  printf ("output: q = %d, t = %d\n", output.q, output.t);
  quick2 (array, 0, n-1);

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);
  }
  printf ("\n");

  return 0;
}

void
swap (
  int *s1,
  int *s2
  )
{
  int temp;

  temp = *s1;
  *s1 = *s2;
  *s2 = temp;
}

struct PAIR
part2 (
  int *A,
  int p,
  int r
  )
{
  int x;
  int i, j, q, t;
  struct PAIR val = {-1, -1};
  int k;
  q = -1;
  t = -1;
  x = A[p];

  for (i = p, j = p+1; j <= r; j++) {
    if (A[j] < x) {
      if (q >= 0 && t >=0) {
        swap (&A[q], &A[t+1]);
        swap (&A[q], &A[j]);
        q = q+1;
        t = t+1;
      } else {
        //regular case
        i = i+1;
        swap (&A[i], &A[j]);
//        //for debug
//        printf ("i = %d, j = %d\n", i, j);
//        for (k = 0; k < n; k++) {
//          printf ("%d  ", A[k]);
//        }
//        printf ("\n");

      }
    } else if (A[j] == x) {
      if (q < 0 && t < 0) {
        q = j;
        t = j;    //don't use i after this
      } else {
        t = t+1; 
        swap (&A[t], &A[j]);
      } 
    }   
  }  //end for (j)
  
  if (q < 0 && t < 0) {
    //no repeated value, return q = t = i
    swap (&A[i], &A[p]);
    val.q = i;
    val.t = i;
  } else {
    q = q-1;
    swap (&A[q], &A[p]);
    val.q = q;
    val.t = t;
  }

  return val;
}

struct PAIR
randpart2 (
  int *A,
  int p,
  int r
  )
{
  int x;
  int i, j, q, t;
  struct PAIR val = {-1, -1};
//  int k;
  int size, idxp;

  q = -1;
  t = -1;
//  x = A[p];
  size = r-p+1;
  idxp = rand () % size;  //0~(size-1)
  idxp = p + idxp;        //important!
  printf ("idxp = %d, A[%d] = %d\n", idxp, idxp, A[idxp]);
  swap (&A[p], &A[idxp]);
  x = A[p];               //randomized

  for (i = p, j = p+1; j <= r; j++) {
    if (A[j] < x) {
      if (q >= 0 && t >=0) {
        swap (&A[q], &A[t+1]);
        swap (&A[q], &A[j]);
        q = q+1;
        t = t+1;
      } else {
        //regular case
        i = i+1;
        swap (&A[i], &A[j]);
//        //for debug
//        printf ("i = %d, j = %d\n", i, j);
//        for (k = 0; k < n; k++) {
//          printf ("%d  ", A[k]);
//        }
//        printf ("\n");

      }
    } else if (A[j] == x) {
      if (q < 0 && t < 0) {
        q = j;
        t = j;    //don't use i after this
      } else {
        t = t+1; 
        swap (&A[t], &A[j]);
      } 
    }   
  }  //end for (j)
  
  if (q < 0 && t < 0) {
    //no repeated value, return q = t = i
    swap (&A[i], &A[p]);
    val.q = i;
    val.t = i;
  } else {
    q = q-1;
    swap (&A[q], &A[p]);
    val.q = q;
    val.t = t;
  }

  return val;
}

void
quick2 (
  int *A,
  int p,
  int r
  )
{
  struct PAIR idx = {-1, -1};
  int k;
  //base case:
  if (r <= p) {
    return;
  }

  //for debug
  printf ("Before randpart2:\n");
  for (k = p; k <=r; k++) {
    printf ("%d  ", A[k]);
  }
  printf ("\n");

  idx = randpart2 (A, p, r);
//  idx = part2 (A, p, r);

  //for debug
  printf ("After randpart2:\n");
  for (k = p; k <=r; k++) {
    printf ("%d  ", A[k]);
  }
  printf ("\n");

  if (idx.q < p || idx.q > r || idx.t < p || idx.t > r) {
    //error
    return;
  }
  quick2 (A, p, idx.q-1);
  quick2 (A, idx.t+1, r);
}

