/*
 * Exercise 12.1-3 of CLRS:
 * The program implements a nonrecursive algorithm that performs
 * an inorder tree walk, using a stack as an auxiliary data structure.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _NODE {
  int key;
  struct _NODE *p;
  struct _NODE *left;
  struct _NODE *right;
} NODE;

void
Iter_InOrder_Tree_Walk (
  NODE *root,
  int n             //used to build stack
  );

void 
push (
  NODE **stack,
  int *top,
  int n,
  NODE *node
  );

NODE *
pop (
  NODE **stack,
  int *top
  );

bool
IsStackEmpty (
  NODE **stack,
  int top
  );

//for debug
void
printstack (
  NODE **stack,
  int top
  );

//use array to implement stack
int
main (void)
{
//  NODE *new[6];   //{2, 5, 8, 5, 7, 6}
//  int n = 6;
//
//  //build example 1
//  new[0] = malloc (sizeof (NODE));
//  new[0]->key = 2;
//  new[0]->left = NULL;
//  new[0]->right = NULL;
//  new[1] = malloc (sizeof (NODE));
//  new[1]->key = 5;
//  new[1]->left = new[0];
//  new[0]->p = new[1];
//  new[2] = malloc (sizeof (NODE));
//  new[2]->key = 5;
//  new[2]->left = NULL;
//  new[2]->right = NULL;
//  new[1]->right = new[2];
//  new[2]->p = new[1];
//  new[3] = malloc (sizeof (NODE));
//  new[3]->key = 6;
//  new[3]->left = new[1];
//  new[1]->p = new[3];
//  new[3]->p = NULL;    //root
//  new[4] = malloc (sizeof (NODE));
//  new[4]->key = 7;
//  new[3]->right = new[4];
//  new[4]->p = new[3];
//  new[4]->left = NULL;
//  new[5] = malloc (sizeof (NODE));
//  new[5]->key = 8;
//  new[4]->right = new[5];
//  new[5]->p = new[4];
//  new[5]->left = NULL;
//  new[5]->right = NULL;

  NODE *new[7];
  int n = 7;
  int i;
  //build example 2
  for (i = 0; i < n; i++) {
    new[i] = malloc (sizeof (NODE));
//    memset (&new[i], 0, sizeof (NODE));
  }
  new[0]->key = 1;
  new[1]->key = 4;
  new[2]->key = 5;
  new[0]->left = NULL;
  new[0]->right = NULL;
  new[0]->p = new[1];
  new[1]->left = new[0];
  new[1]->right = NULL;
  new[1]->p = new[2];
  new[2]->left = new[1];
  new[2]->right = NULL;
  new[2]->p = new[3];
  new[3]->key = 10;
  new[4]->key = 16;
  new[5]->key = 17;
  new[3]->left = new[2];
  new[3]->right = new[4];
  new[3]->p = new[5];
  new[4]->left = NULL;
  new[4]->right = NULL;
  new[4]->p = new[3];
  new[5]->left = new[3];
  new[5]->right = new[6];
  new[5]->p = NULL;  //root
  new[6]->key = 21;
  new[6]->left = NULL;
  new[6]->right = NULL;
  new[6]->p = new[5];

  //test
  Iter_InOrder_Tree_Walk (new[5], n);
  printf ("\n");

  return 0;
}

void
Iter_InOrder_Tree_Walk (
  NODE *root,
  int n             //used to build stack
  )
{
  //build the stack
  int top = -1;
  NODE **stack;
  NODE *item;
  bool bright;

  n = 2*n;  //size n is not enough ??
  stack = malloc (sizeof (NODE *) * (n));  //stack[i] is NODE *

  while (root->left) {
    push (stack, &top, n, root->right);
    push (stack, &top, n, root);
    root = root->left;
  }
  push (stack, &top, n, root->right);
  printf ("answer: %d, \n", root->key);

  //for debug
  printstack (stack, top);

  bright = true;
  do {
    item = pop (stack, &top);
    if (item) {
//      printf ("item->key = %d\n", item->key);
      if (!bright) {
        //root, print directly
        printf ("answer: %d, \n", item->key);
      } else {
        //iteratively
//        //for debug
//        printstack (stack, top);
        while (item) {
          push (stack, &top, n, item->right);
          push (stack, &top, n, item);
          item = item->left; 
        }
//        //for debug
//        printstack (stack, top);
      }
    }  //end if (item)

    bright = !bright;  //switch

//    //for debug
//    printstack (stack, top);
  } while (!IsStackEmpty (stack, top));

}

void 
push (
  NODE **stack,
  int *top,
  int n,
  NODE *node
  )
{
  if (++(*top) >= n) {
    printf ("error: stack is full.\n");
    return;
  }
  stack[*top] = node;

//  //for debug
//  if (stack[*top]) {
//    printf ("push: key = %d\n", stack[*top]->key);
//  } else {
//    printf ("push: NULL\n");
//  }

  return;
}

NODE *
pop (
  NODE **stack,
  int *top
  )
{
  if (*top < (int)0) {
    printf ("error: stack is empty.\n");
    return NULL;
  }

//  //for debug
//  printf ("pop: ");
//  if (stack[(*top)]) {
//    printf ("key = %d\n", stack[(*top)]->key);
//  } else {
//    printf ("NULL\n");
//  }

  return stack[(*top)--];
}

bool
IsStackEmpty (
  NODE **stack,
  int top
  )
{
  //for debug
//  printf ("IsStackEmpty: top = %d\n", top);

  return (top >= 0) ? false : true;
}

//for debug
void
printstack (
  NODE **stack,
  int top
  )
{
  printf ("In stack: top = %d\n", top);  
  if (IsStackEmpty (stack, top)) {
    return;
  }
  //print content of the stack
  do {

    if (stack[top]) {  
      printf ("%d, ", stack[top--]->key);
    } else {
      top--;
      printf ("NULL, ");
    }
  } while (top >= 0);
  printf ("\n");
}

