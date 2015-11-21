/*
 * The program recursively computes the product of two square matrices
 * using a divide-and-conquer algorithm.
 */

#include <stdio.h>
#include <stdlib.h>

//int size = 2;
//int array1[][2] = {{1, 2}, {3, 4}};
//int array2[][2] = {{5, 6}, {7, 8}};
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
mult (
  int *A,
  int *B,
  int n,
  int *C
);

int
main (void)
{
  int i;
  int *ptr1; 
  int *ptr2; 
  int *ptr3;

  ptr1 = array1;
  ptr2 = array2;
  ptr3 = answer;

  mult (ptr1, ptr2, size, ptr3);

  printf ("Result:\n");
  for (i = 0; i < size*size; i++) {
    printf ("%d  ", ptr3[i]);  
  }
  printf ("\n");

  return 0;
}

void
mult (
  int *A,
  int *B,
  int n,
  int *C
)
{
  printf ("A is at 0x%x, B is at 0x%x, C is at 0x%x, n = %d\n", A, B, C, n);

  if (n == 1) {
    *C += (*A) * (*B);
    printf ("*A = %d, *B = %d, *C = %d\n", *A, *B, *C);
    return;
  }

  mult (&A[0], &B[0], n/2, &C[0]);
  mult (&A[n/2], &B[(size)*(n/2)], n/2, &C[0]);
  mult (&A[0], &B[n/2], n/2, &C[n/2]);
  mult (&A[n/2], &B[(size)*(n/2)+n/2], n/2, &C[n/2]);
  mult (&A[(size)*(n/2)], &B[0], n/2, &C[(size)*(n/2)]);
  mult (&A[(size)*(n/2)+n/2], &B[(size)*(n/2)], n/2, &C[(size)*(n/2)]);
  mult (&A[(size)*(n/2)], &B[n/2], n/2, &C[(size)*(n/2)+n/2]);
  mult (&A[(size)*(n/2)+n/2], &B[(size)*(n/2)+n/2], n/2, &C[(size)*(n/2)+n/2]);

}
