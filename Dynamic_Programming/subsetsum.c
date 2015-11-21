/*
 * The program implements a brute force algorithm to solve the subset-sum problem.
 * Given a set S = {x1, x2, ..., xn} of positive integers and a positive integer t,
 * decide whether there exists a subset of S that adds up exactly to the target value t.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void
push_stack (
  int *stack,
  int depth,
  int *top,
  int key
  );

int
pop_stack (
  int *stack,
  int *top
  );

bool
IsEmpty (
  int *stack,
  int top
  );

//for debug
void
print_stack (
  int *stack,
  int top
  );

//main procedure
void
SubsetSum (
  int *x,
  int t,
  int i,
  int n,
  int *stack,
  int top
  );

void
wrapper (
  int *x,
  int t,
  int n,
  int *stack,
  int top
  );

//inputs
int x[] = {8, 6, 7, 5, 3, 10, 9};
int t = 15;
int n = 7;

int
main (void) 
{
  int *stack;
  int stack_top;

  stack = malloc (sizeof (int) * n);
  memset (stack, 0, sizeof (int) * n);
  stack_top = -1;

  //test
//  SubsetSum (x, t, 0, n, stack, stack_top);
  wrapper (x, t, n, stack, stack_top);

  return 0;    
}

void
push_stack (
  int *stack,
  int depth,
  int *top,
  int key
  )
{
  if (++(*top) >= depth) {
    printf ("the stack is full.\n");
    return;
  }

  stack[*top] = key;
}

int
pop_stack (
  int *stack,
  int *top
  )
{
  if (*top < 0) {
    printf ("the stack is empty.\n");
    return -1;
  }
  
  return stack[(*top)--];
}

bool
IsEmpty (
  int *stack,
  int top
  )
{
  if (top >= 0) {
    return false;
  }
  return true;
}

//for debug
void
print_stack (
  int *stack,
  int top
  )
{
  int key;

  while (!IsEmpty (stack, top)) {
    key = pop_stack (stack, &top);
    printf ("%d, ", key);
  }
  printf ("\n");
  
}

//main procedure
void
SubsetSum (
  int *x,
  int t,
  int i,
  int n,
  int *stack,
  int top
  )
{
  int j;

  push_stack (stack, n, &top, x[i]);
  t = t-x[i];
  //base case:  
  if (t < 0) {
    return;
  }
  if (t == 0) {
    print_stack (stack, top);
    return;
  }

  for (j = i+1; j < n; j++) {
//    printf ("top = %d, i = %d, j = %d, t = %d\n", top, i, j, t);  //for debug  
    SubsetSum (x, t, j, n, stack, top);
  }
}

void
wrapper (
  int *x,
  int t,
  int n,
  int *stack,
  int top
  )
{
  int i;
  for (i = 0; i < n; i++) {
    SubsetSum (x, t, i, n, stack, top);
  }
}
