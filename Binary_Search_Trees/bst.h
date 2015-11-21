#ifndef _BST_H_
#define _BST_H_

/*
 * bst.h defines helper functions
 * to search for a key stored in a binary search tree.
 *
 * The helper functions include queries as Minimum, Maximum, Successor, and Predecessor.
 */ 

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
Tree_Insert (
  NODE **root,
  NODE *z
  );

void
Recur_Tree_Insert (
  NODE **root,
  NODE *z
  );

NODE *
Tree_Search (
  NODE *root,
  int key
  );

NODE *
Iter_Tree_Search (
  NODE *root,
  int key
  );

NODE *
Tree_Minimum (
  NODE *root      
  );

NODE *
Tree_Maximum (
  NODE *root      
  );

NODE *
Tree_Successor (
  NODE *x    //don't need the root: find in the subtree of x      
  );

NODE *
Tree_Predecessor (
  NODE *x
  );

//replace subtree
void
Transplant (
  NODE **root,
  NODE *u,
  NODE *v
  );

void
Tree_Delete (
  NODE **root,
  NODE *z
  );

#endif 
