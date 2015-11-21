/*
 * Exercise 15.4-5 of CLRS:
 *
 * The program implements a brute force algorithm 
 * to solve the problem of longest increasing subsequence, to find the longest monotonically
 * increasing subsequence of a sequence of n numbers.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

//longest increasing subsequence
int
Lis_Length (
  char *x
  );

//input
//char x[] = "ABCBDAB";
char x[] = "DABCBDA";

int
main (void) 
{
  printf ("the answer is %d\n", Lis_Length (x));

  return 0;    
}

//longest increasing subsequence
int
Lis_Length (
  char *x
  )
{
  int len;
  int *dp;
  int i, j;
  int max;
  int last;     //the last char of lis
//  int *stack;
//  int stack_top = -1;
  char *ans;
  char tmp[2];
  
  last = -1;    //initialize

  len = strlen (x);
  dp = malloc (sizeof (int) * len);
  memset (dp, 0, sizeof (int) * len);
//  stack = malloc (sizeof (int) * len);
//  memset (stack, 0, sizeof (int) * len);
  ans = malloc (sizeof (char) * len);
  memset (ans, 0, sizeof (char) * len);
  memset (tmp, 0, sizeof (char) * 2);

  //initialize
  dp[0] = 1;
  for (i = 1; i < len; i++) {
    //fill up dp[i]
    max = 0x80000000;
    for (j = 0; j < i; j++) {
      if (x[i] > x[j] && (last == -1 || j == last)) {  //append to the lis
        max = MAX(max, dp[j]+1);
        //first time
        if (last == -1) {
//          push_stack (stack, len, &stack_top, j);  //to reconstruct
          tmp[0] = x[j];
          strcat (ans, tmp);
        }
        last = i;         //update
//        push_stack (stack, len, &stack_top, last);  //to reconstruct
        tmp[0] = x[last];
        strcat (ans, tmp);
      } else {
        max = MAX(max, dp[j]);
      }
    }
    dp[i] = max;
  }

  //for debug
  for (i = 0; i < len; i++) {
    printf ("%d, ", dp[i]);
  }
  printf ("\n");
//  printf ("last = %d\n", last);

//  //reconstruct
//  while (!IsEmpty (stack, stack_top)) {
//    j = pop_stack (stack, &stack_top);
//    printf ("%c", x[j]);
//  }
//  printf ("\n");
  printf ("ans: %s\n", ans);

  return dp[len-1];
}

