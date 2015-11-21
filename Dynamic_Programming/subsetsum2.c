/*
 * The program implements a dynamic programming algorithm to solve the subset-sum problem.
 * Given a set S = {x1, x2, ..., xn} of positive integers and a positive integer t,
 * decide whether there exists a subset of S that adds up exactly to the target value t.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//inputs
int x[] = {8, 6, 7, 5, 3, 10, 9};
int t = 15;
int n = 7;

//true: there are subsets sum to t
//false: there is no subsets sum to t
bool
SubsetSum_v2 (
  int *x,
  int t,
  int n
  );

void
reconstruct (
  int *x,      
  bool *ss,
  int col,
  int tt,     //the row to start tracing
  int *stack,
  int depth,
  int stack_top
  );

//helper
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

int
main (void) 
{
  printf ("the ans is %c\n", SubsetSum_v2 (x, t, n) ? 't' : 'f');  

  return 0;    
}

//true: there are subsets sum to t
//false: there is no subsets sum to t
bool
SubsetSum_v2 (
  int *x,
  int t,
  int n
  )
{
  //build table ss[t, i]:
  //true: in x[1..i], there is subset sum to t
  //false: in x[1..i], there is no subset sum to t
  //ans: x[t, n]

  int row, col;
  int i, tt;
  bool *ss;
  bool a, b;
  int *stack;
  int stack_top = -1;

  row = t+1;
  col = n+1;   //col 0 is adundant
  ss = malloc (sizeof (bool) * row * col);
  //build stack
  stack = malloc (sizeof (int) * n);

  for (i = 0; i < col; i++) {
    ss[i] = true;     //ss[0, i] is true
  }
  for (tt = 1; tt < row; tt++) {
    ss[tt*col] = false;   //ss[t, 0] is false, except for ss[0, 0]
  }

  for (tt = 1; tt < row; tt++) {
    for (i = 1; i < col; i++) {
      //idx of x[] is 0-based
      //ss[t, i] = ss[t-x[i], i-1] v ss[t, i-1]
      a = (tt-x[i-1] < 0) ? false : ss[(tt-x[i-1])*col+(i-1)];
      b = ss[tt*col+(i-1)];
//      printf ("a = %c, b = %c\n", (a ? 't' : 'f'), (b ? 't' : 'f'));
      ss[tt*col+i] = a | b;
    }
  }

  //for debug
  for (tt = 0; tt < row; tt++) {
    for (i = 0; i < col; i++) {
      printf ("%c, ", ss[tt*col+i] ? 't' : 'f');
    }
    printf ("\n");
  }

  //reconstruct
  reconstruct (x, ss, col, t, stack, n, stack_top);

  return ss[t*col+n];
}

void
reconstruct (
  int *x,      
  bool *ss,
  int col,
  int tt,     //the row to start tracing
  int *stack,
  int depth,
  int stack_top
  )
{
  int i;  
//  bool found;

  //base case:
  if (tt == 0) {
    printf ("subset:\n");
    print_stack (stack, stack_top);
//    printf ("\n");  
    return;
  }
  if (tt < 0) {
    return;
  }

//  found = false;
  for (i = 1; i < col; i++) {
    if (ss[tt*col+i]) {
//      printf ("%d, ", x[i-1]);  
//      found = true;
      push_stack (stack, depth, &stack_top, x[i-1]);
      reconstruct (x, ss, col, tt-x[i-1], stack, depth, stack_top);
      pop_stack (stack, &stack_top);   //restore at this level
    }
  }

//  //for debug
//  printf ("tt = %d\n", tt);
//  print_stack (stack, stack_top);

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

