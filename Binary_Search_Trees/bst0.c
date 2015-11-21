/*
 * Exercise 12.1-4 of CLRS:
 * The program implements recursive algorithms that perform
 * preorder and postorder tree walks on a tree of n nodes.
 */ 

#include <stdio.h>
#include <stdlib.h>


typedef struct _NODE {
  int key;
  struct _NODE *p;
  struct _NODE *left;
  struct _NODE *right;
} NODE;

void 
InOrder_Tree_Walk (
  NODE *root      
  );

void 
PreOrder_Tree_Walk (
  NODE *root      
  );

void 
PostOrder_Tree_Walk (
  NODE *root      
  );

int
main (void)
{
//  NODE *new[6];   //{2, 5, 8, 5, 7, 6}
//  //build example
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

//  //test
//  InOrder_Tree_Walk (new[5]);
//  printf ("\n");

//  //test
//  PreOrder_Tree_Walk (new[3]);
//  printf ("\n");

  //test
  PostOrder_Tree_Walk (new[5]);
  printf ("\n");

  return 0;
}

void 
InOrder_Tree_Walk (
  NODE *root      
  )
{
  //base case:
  if (root == NULL) {
    return;
  }
  InOrder_Tree_Walk (root->left);
  printf ("%d, ", root->key);
  InOrder_Tree_Walk (root->right);
}

void 
PreOrder_Tree_Walk (
  NODE *root      
  )
{
  //base case:
  if (root == NULL) {
    return;
  }
  printf ("%d, ", root->key);
  PreOrder_Tree_Walk (root->left);
  PreOrder_Tree_Walk (root->right);
}

void 
PostOrder_Tree_Walk (
  NODE *root      
  )
{
  //base case:
  if (root == NULL) {
    return;
  }
  PostOrder_Tree_Walk (root->left);
  PostOrder_Tree_Walk (root->right);
  printf ("%d, ", root->key);
}
