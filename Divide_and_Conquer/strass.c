/*
 * The program demonstrates the Strassen's method 
 * for multiplication of two square matrices. 
 * The method reduces the number of recursive multiplications from eight to seven. 
 */


#include <stdio.h>
#include <stdlib.h>

//int size = 2;
//int array1[][2] = {{1, 3}, {6, 8}};
//int array2[][2] = {{7, 5}, {4, 2}};
//int answer[][2] = {{0, 0}, {0, 0}};

//int size = 4;
//int array1[][4] = {{1, 2, 3, 4}, {3, 2, 1, 4}, {4, 3, 2, 1}, {1, 3, 4, 2}};
//int array2[][4] = {{0, 1, 2, 2}, {4, 0, 2, 1}, {3, 2, 1, 4}, {0, 1, 2, 3}};
//int answer[][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

int size = 8;
int array1[][8] = {{1, -1, 2, -2, 0, 3, 1, -2}, {0, 3, 2, -2, 1, -1, 0, -3}, {1, 2, 0, 3, -1, -2, 3, 1}, {0, 1, 1, -2, 2, 2, -3, 0}, {3, -3, 0, 1, 2, 3, 2, 1}, {1, 1, 2, 3, 1, 0, 2, -2}, {0, 2, 0, 1, -1, 3, -3, 1}, {1, 2, -2, 3, -2, 1, -1, 0}};
int array2[][8] = {{3, 3, -2, 4, 0, 4, 2, 1}, {0, -4, 3, 1, 2, -2, 1, 2}, {1, 2, 4, 3, -2, 2, 0, 1}, {4, -2, -3, 1, 4, 3, 2, 3}, {0, 4, -4, 0, 3, 2, 1, -2}, {2, -2, 1, 2, 3, -3, 0, 4}, {4, -4, 1, 3, 2, 0, 1, -1}, {1, 2, 3, -1, 0, 3, -4, 4}};
int answer[][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};

void
mults (
  int *A,
  int *B,
  int n,
  int *C
);

void
add (
  int *A,
  int *B,
  int n,
  int *C
);

void
sub (
  int *A,
  int *B,
  int n,
  int *C
);

void
copy (
  int *src,
  int *dst,
  int n
);

int
main (void)
{
  int *p1;
  int *p2;
  int *p3;
  int i;

  p1 = &array1[0][0];
  p2 = &array2[0][0];
  p3 = &answer[0][0];

  mults (p1, p2, size, p3);

  printf ("answer:");
  for (i = 0; i < size*size; i++) {
    if (i % size == 0) {
      printf ("\n  ");
    }
    printf ("%d  ", p3[i]);
  }
  printf ("\n");

  return 0;
}

void
mults (
  int *A,
  int *B,
  int n,
  int *C
)
{
  int *Sptr[10];
  int *Aptr[4];  //A11, A12, A21, A22
  int *Bptr[4];  //B11, B12, B21, B22
  int *Cptr[4];  //C11, C12, C21, C22
  int *Pptr[7];
  int i, j, idx;

  //base case: n = 1
  if (n == 1) {
    *C = (*A) * (*B);
    return;
  }

  for (i = 0; i < 10; i++) {
    Sptr[i] = (int *)malloc (sizeof (int) * (n/2) * (n/2));
  }

  for (i = 0; i < 4; i++) {
    Aptr[i] = (int *)malloc (sizeof (int) * (n/2) * (n/2));
    Bptr[i] = (int *)malloc (sizeof (int) * (n/2) * (n/2));
    Cptr[i] = (int *)malloc (sizeof (int) * (n/2) * (n/2));
  }
 
  for (i = 0; i < 7; i++) {
    Pptr[i] = (int *)malloc (sizeof (int) * (n/2) * (n/2));
  }

  //copy
  idx = 0;
  for (i = 0; i < n/2; i++) {
    for (j = 0; j < n/2; j++) {
      Aptr[0][idx] = A[i*n + j];
      Aptr[1][idx] = A[i*n + j + n/2];
      Aptr[2][idx] = A[(i + n/2)*n + j];
      Aptr[3][idx] = A[(i + n/2)*n + j + n/2];
      Bptr[0][idx] = B[i*n + j];
      Bptr[1][idx] = B[i*n + j + n/2];
      Bptr[2][idx] = B[(i + n/2)*n + j];
      Bptr[3][idx] = B[(i + n/2)*n + j + n/2];
      idx++;
    }
  }

  //for debug
  for (j = 0; j < 4; j++) {
    printf ("Aptr[%d]:", j);
    for (i = 0; i < n/2*n/2; i++) {
      if (i % (n/2) == 0) {
        printf ("\n  ");
      }
      printf ("%d  ", Aptr[j][i]);
    }
    printf ("\n");
  }
  for (j = 0; j < 4; j++) {
    printf ("Bptr[%d]:", j);
    for (i = 0; i < n/2*n/2; i++) {
      if (i % (n/2) == 0) {
        printf ("\n  ");
      }
      printf ("%d  ", Bptr[j][i]);
    }
    printf ("\n");
  }

  //S matrices
  sub (Bptr[1], Bptr[3], n/2, Sptr[0]);
  add (Aptr[0], Aptr[1], n/2, Sptr[1]);
  add (Aptr[2], Aptr[3], n/2, Sptr[2]);
  sub (Bptr[2], Bptr[0], n/2, Sptr[3]);
  add (Aptr[0], Aptr[3], n/2, Sptr[4]);
  add (Bptr[0], Bptr[3], n/2, Sptr[5]);
  sub (Aptr[1], Aptr[3], n/2, Sptr[6]);
  add (Bptr[2], Bptr[3], n/2, Sptr[7]);
  sub (Aptr[0], Aptr[2], n/2, Sptr[8]);
  add (Bptr[0], Bptr[1], n/2, Sptr[9]);
  
  //for debug
  for (j = 0; j < 10; j++) {
    printf ("Sptr[%d]:", j);
    for (i = 0; i < n/2*n/2; i++) {
      if (i % (n/2) == 0) {
        printf ("\n  ");
      }
      printf ("%d  ", Sptr[j][i]);
    }
    printf ("\n");
  }

  //recursive
  mults (Aptr[0], Sptr[0], n/2, Pptr[0]);
  mults (Sptr[1], Bptr[3], n/2, Pptr[1]);
  mults (Sptr[2], Bptr[0], n/2, Pptr[2]);
  mults (Aptr[3], Sptr[3], n/2, Pptr[3]);
  mults (Sptr[4], Sptr[5], n/2, Pptr[4]);
  mults (Sptr[6], Sptr[7], n/2, Pptr[5]);
  mults (Sptr[8], Sptr[9], n/2, Pptr[6]);

  //C sub-matrices
  add (Pptr[4], Pptr[3], n/2, Cptr[0]);
  sub (Cptr[0], Pptr[1], n/2, Cptr[0]);
  add (Cptr[0], Pptr[5], n/2, Cptr[0]);

  add (Pptr[0], Pptr[1], n/2, Cptr[1]);

  add (Pptr[2], Pptr[3], n/2, Cptr[2]);

  add (Pptr[4], Pptr[0], n/2, Cptr[3]);
  sub (Cptr[3], Pptr[2], n/2, Cptr[3]);
  sub (Cptr[3], Pptr[6], n/2, Cptr[3]);

  //copy back to C
  copy (Cptr[0], &C[0], n/2);
  copy (Cptr[1], &C[n/2], n/2);
  copy (Cptr[2], &C[(n*n/2)], n/2);
  copy (Cptr[3], &C[(n*n/2)+(n/2)], n/2);

  //free memory
  for (i = 0; i < 10; i++) {
    free (Sptr[i]);
  }

  for (i = 0; i < 4; i++) {
    free (Aptr[i]);
    free (Bptr[i]);
    free (Cptr[i]);
  }
 
  for (i = 0; i < 7; i++) {
    free (Pptr[i]);
  }
  return;
}

void
add (
  int *A,
  int *B,
  int n,
  int *C
)
{
  int i;

  for (i = 0; i < n*n; i++) {
    C[i] = A[i] + B[i];
  }
}

void
sub (
  int *A,
  int *B,
  int n,
  int *C
)
{
  int i;

  for (i = 0; i < n*n; i++) {
    C[i] = A[i] - B[i];
  }
}

void
copy (
  int *src,    //n*n
  int *dst,    //2n*2n
  int n
)
{
  int i, j;
  int sidx, didx;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
       sidx = i*n + j;  //idx of src
       didx = i*2*n + j;  //idx of dst
       dst[didx] = src[sidx];
    }
  }
}


