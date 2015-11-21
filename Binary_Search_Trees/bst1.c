/*
 * The program implements helper functions
 * to search for a key stored in a binary search tree.
 *
 * The helper functions include queries as Minimum, Maximum, Successor, and Predecessor.
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"  //definitions of helper functions

//typedef struct _NODE {
//  int key;
//  struct _NODE *p;
//  struct _NODE *left;
//  struct _NODE *right;
//} NODE;
//
//
//void 
//InOrder_Tree_Walk (
//  NODE *root      
//  );
//
//void
//Tree_Insert (
//  NODE **root,
//  NODE *z
//  );
//
//void
//Recur_Tree_Insert (
//  NODE **root,
//  NODE *z
//  );
//
//NODE *
//Tree_Search (
//  NODE *root,
//  int key
//  );
//
//NODE *
//Iter_Tree_Search (
//  NODE *root,
//  int key
//  );
//
//NODE *
//Tree_Minimum (
//  NODE *root      
//  );
//
//NODE *
//Tree_Maximum (
//  NODE *root      
//  );
//
//NODE *
//Tree_Successor (
//  NODE *x    //don't need the root: find in the subtree of x      
//  );
//
//NODE *
//Tree_Predecessor (
//  NODE *x
//  );

//int
//main (void)
//{
//  //test {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9}
//  int array[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
//  int n = 11;
//  int i;
//  NODE *Tree = NULL;
//  NODE *new, *suc;
//  NODE *Tree2 = NULL;
//
//  //build tree
//  for (i = 0; i < n; i++) {
//    new = malloc (sizeof (NODE));
//    new->key = array[i];
//    Tree_Insert (&Tree, new);
//  }
//  //print
//  printf ("Tree1:\n");
//  InOrder_Tree_Walk (Tree);
//  printf ("\n");
//
//
//  //build tree2
//  for (i = 0; i < n; i++) {
//    new = malloc (sizeof (NODE));
//    new->key = array[i];
//    Recur_Tree_Insert (&Tree2, new);
//  }
//  //print
//  printf ("Tree2:\n");
//  InOrder_Tree_Walk (Tree);
//  printf ("\n");
//
//  //test tree-search
////  new = Tree_Search (Tree, 19);
//  new = Iter_Tree_Search (Tree, 13);
//  //for debug
//  if (new) {
//    printf ("search: key = %d, p = 0x%x, left = 0x%x, right = 0x%x\n",
//            new->key, (int)(new->p), (int)(new->left), (int)(new->right));
//    if (new->p) {
//      printf ("p = %d, ", new->p->key);
//    }
//    if (new->left) {
//      printf ("left = %d, ", new->left->key);
//    }
//    if (new->right) {
//      printf ("right = %d, ", new->right->key);
//    }
//    printf ("\n");
//  } else {
//    printf ("search: not found.\n");
//  }
//
//  //test minimum and maximum
//  new = Tree_Minimum (Tree);
//  //for debug
//  if (new) {
//    printf ("minimum: key = %d, p = 0x%x, left = 0x%x, right = 0x%x\n",
//            new->key, (int)(new->p), (int)(new->left), (int)(new->right));
//    if (new->p) {
//      printf ("p = %d, ", new->p->key);
//    }
//    if (new->left) {
//      printf ("left = %d, ", new->left->key);
//    }
//    if (new->right) {
//      printf ("right = %d, ", new->right->key);
//    }
//    printf ("\n");
//  } else {
//    printf ("minimum: not found.\n");
//  }
//
//  new = Tree_Maximum (Tree);
//  //for debug
//  if (new) {
//    printf ("maximum: key = %d, p = 0x%x, left = 0x%x, right = 0x%x\n",
//            new->key, (int)(new->p), (int)(new->left), (int)(new->right));
//    if (new->p) {
//      printf ("p = %d, ", new->p->key);
//    }
//    if (new->left) {
//      printf ("left = %d, ", new->left->key);
//    }
//    if (new->right) {
//      printf ("right = %d, ", new->right->key);
//    }
//    printf ("\n");
//  } else {
//    printf ("maximum: not found.\n");
//  }
//
//  //test tree-successor
//  new = Iter_Tree_Search (Tree, 13);
//  suc = Tree_Successor(new);
//  //for debug
//  if (suc) {
//    printf ("successor: key = %d, p = 0x%x, left = 0x%x, right = 0x%x\n",
//            suc->key, (int)(suc->p), (int)(suc->left), (int)(suc->right));
//    if (suc->p) {
//      printf ("p = %d, ", suc->p->key);
//    }
//    if (suc->left) {
//      printf ("left = %d, ", suc->left->key);
//    }
//    if (suc->right) {
//      printf ("right = %d, ", suc->right->key);
//    }
//    printf ("\n");
//  } else {
//    printf ("successor: not found.\n");
//  }
//
//  //test tree-predecessor
//  new = Iter_Tree_Search (Tree, 17);
//  suc = Tree_Predecessor(new);
//  //for debug
//  if (suc) {
//    printf ("predecessor: key = %d, p = 0x%x, left = 0x%x, right = 0x%x\n",
//            suc->key, (int)(suc->p), (int)(suc->left), (int)(suc->right));
//    if (suc->p) {
//      printf ("p = %d, ", suc->p->key);
//    }
//    if (suc->left) {
//      printf ("left = %d, ", suc->left->key);
//    }
//    if (suc->right) {
//      printf ("right = %d, ", suc->right->key);
//    }
//    printf ("\n");
//  } else {
//    printf ("predecessor: not found.\n");
//  }
//
//  return 0;
//}

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
Tree_Insert (
  NODE **root,
  NODE *z
  )
{
  NODE *x, *y;

//  //for debug
//  if (*root) {
//    printf ("root = %d, z = %d\n", (*root)->key, z->key);
//  } else {
//    printf ("root = NULL, z = %d\n", z->key);
//  }

  y = *root;
  x = NULL;   //x is y's parent
  while (y != NULL) {
    //insert z as a leaf, traverse until leaf
    x = y;
    if (z->key < y->key) {
      y = y->left;
    } else {
      y = y->right;
    }
  }
  //assign z
  z->p = x;
  if (x == NULL) {
    //*root is null, tree is empty
    *root = z;
    return;
  }
  //insert to leaf's parent
  if (z->key < x->key) {
    x->left = z;
  } else {
    x->right = z;
  }
}

void
Recur_Tree_Insert (
  NODE **root,
  NODE *z
  )
{
  //*root is empty
  if (*root == NULL) {
    *root = z;
    return;    //don't recurse
  }

  if (z->key < (*root)->key) {
    //base case:
    if ((*root)->left == NULL) {
      (*root)->left = z;
      z->p = (*root);
      return;
    }    
    Recur_Tree_Insert (&((*root)->left), z);
  } else {
    //base case:
    if ((*root)->right == NULL) {
      (*root)->right = z;
      z->p = (*root);
      return;
    }    
    Recur_Tree_Insert (&((*root)->right), z);
  }
}

NODE *
Tree_Search (
  NODE *root,
  int key
  )
{
  //recursive version:
  //base case:
  if (root == NULL) {
    return NULL;
  }

  if (key < root->key) {
    Tree_Search (root->left, key);
  } else if (key > root->key) {
    Tree_Search (root->right, key);
  } else {
    return root;
  }
}

NODE *
Iter_Tree_Search (
  NODE *root,
  int key
  )
{
  while (root) {
    if (root->key == key) {
      return root;
    }
    if (key < root->key) {
      //smaller than
      root = root->left;
    } else {
      //larger than
      root = root->right;
    }
  }

  return NULL;  //not found
}

NODE *
Tree_Minimum (
  NODE *root      
  )
{
  //if tree is empty:
  if (!root) {
    return NULL;
  }

  //find leftmost node
  while (root->left) {
    root = root->left;
  }
  return root;
}

NODE *
Tree_Maximum (
  NODE *root      
  )
{
  //if tree is empty:
  if (!root) {
    return NULL;
  }

  //find leftmost node
  while (root->right) {
    root = root->right;
  }
  return root;
}

NODE *
Tree_Successor (
  NODE *x    //don't need the root: find in the subtree of x      
  )
{
   //return the smallest node of those larger than x.
   NODE *suc;
   NODE *y;

   if (x->right) {
     suc = Tree_Minimum (x->right); 
   } else {
     //look upward
     y = x->p;
     while (y && x == y->right) {
       //y < x
       //traverse until y > x (x is left child)
       x = y;
       y = y->p;
     }
     suc = y;
   }

   return suc;
}

NODE *
Tree_Predecessor (
  NODE *x
  )
{
   //return the largest node of those smaller than x.
   NODE *suc;
   NODE *y;

   if (x->left) {
     suc = Tree_Maximum (x->left); 
   } else {
     //look upward
     y = x->p;
     while (y && x == y->left) {
       //y > x
       //traverse until y < x (x is right child)
       x = y;
       y = y->p;
     }
     suc = y;
   }

   return suc;
}
