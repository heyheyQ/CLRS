/*
 * Problem 13-3 in CLRS: AVL trees
 * An AVL tree is a binary search tree that is height balanced:
 * for each node x, the heights of the left and right subtrees of x 
 * differ by at most 1.
 *
 * The program implements an AVL tree by maintaining an extra attribute 
 * in each node: x.h is the height of node x.
 */

#include <stdio.h>
#include <stdlib.h>

//with height
typedef struct _NODE {
  int key;
  int h;
  struct _NODE *p;
  struct _NODE *left;
  struct _NODE *right;
} NODE;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void
AVL_Insert (
  NODE **root,
  NODE *x,
  NODE *z
  );

void
Balance (
  NODE **root,      
  NODE *x     //balance the height of x->left and x->right      
  );

void
Left_Rotate (
  NODE **root,      
  NODE *x      
  );

void
Right_Rotate (
  NODE **root,      
  NODE *y      
  );

//replace subtree
void
Transplant (
  NODE **root,
  NODE *u,
  NODE *v
  );

//helper
NODE *
Create_Node (
  int key      
  );

void 
InOrder_Tree_Walk (
  NODE *root      
  );

void
Update_Height (
  NODE *x      
  );

//global variable
NODE *NIL;   //sentinel, height = -1

int
main (void)
{
//  int array[] = {10, 5, 16, 4, 1, 21, 17};
//  int n = 7;
//  int array[] = {10, 7, 15, 6, 12, 16, 11, 14, 17, 13};
//  int n = 10;
  int array[] = {2, 4, 7, 6, 8, 5};
  int n = 6;
  int i;
  NODE *new;
  NODE *Tree = NULL;

  //initialize
  NIL = malloc (sizeof (NODE));
  NIL->key = 0x80000000;   //minus infinity
  NIL->h = -1;

  //test:
  for (i = 0; i < n; i++) {
    new = Create_Node (array[i]);
    AVL_Insert (&Tree, Tree, new);
    //for debug
    printf ("root is %d:\n", Tree->key);
    InOrder_Tree_Walk (Tree);
    printf ("\n");
  }

  printf ("root is %d:\n", Tree->key);
  InOrder_Tree_Walk (Tree);
  printf ("\n");

  return 0;
}

void
AVL_Insert (
  NODE **root,
  NODE *x,
  NODE *z
  )
{
  if (!(*root)) {
    *root = z;
    (*root)->left = NIL;
    (*root)->right = NIL;
    return;
  } else {
    if (z->key < (x)->key) {
      //base case:
      if ((x)->left == NIL) {
        (x)->left = z;
        z->p = (x);
        //balance:
        Balance (root, x);

        //update height
        Update_Height (x);
        return;
      }  //base case

      //recurrence
      AVL_Insert (root, (x)->left, z);
      //balance:
      Balance (root, x);

      //update height: lower level updates may change the higher level
      Update_Height (x);

    } else {
      //symmetry
      //base case:
      if ((x)->right == NIL) {
        (x)->right = z;
        z->p = (x);
        //balance:
        Balance (root, x);

        //update height
        Update_Height (x);
        return;
      }  //base case

      //recurrence
      AVL_Insert (root, (x)->right, z);
      //balance:
      Balance (root, x);

      //update height: lower level updates may change the higher level
      Update_Height (x);

    }
  
  }
}

void
Balance (
  NODE **root,      
  NODE *x     //balance the height of x->left and x->right      
  )
{
  int h_right, h_left;
  NODE *ptr;

  h_left = x->left->h;
  h_right = x->right->h;

  if (h_right < h_left) {
    //rotate ?
    if ((h_left - h_right) > 1) {
//      printf ("right-rotate (%d)\n", x->key);  
//      Right_Rotate (root, x);  //wrong!
      //when right-rotate, first consider x->left->right
      if ((x->left->right->h) > (x->left->left->h)) {
        printf ("first, left-rotate (%d)\n", x->left->key);  
        ptr = x->left;
        Left_Rotate (root, x->left);
//        Update_Height (x->left);
//        Update_Height (x->left->p);   //it was x->left->right
        Update_Height (ptr);
        Update_Height (ptr->p);   //it was x->left->right
      }

      printf ("right-rotate (%d)\n", x->key);  
      Right_Rotate (root, x);
      Update_Height (x);
      Update_Height (x->p);   //it was x->left
    }
  
  } else {
    //symmetry
    //rotate ?
    if ((h_right - h_left) > 1) {
//      printf ("left-rotate (%d)\n", x->key);  
//      Left_Rotate (root, x);  //wrong!
      //when left-rotate, first consider x->right->left
      if ((x->right->left->h) > (x->right->right->h)) {
        printf ("first, right-rotate (%d)\n", x->right->key);  
        ptr = x->right;
        Right_Rotate (root, x->right);
        printf ("root is now: %d\n", (*root)->key);
//        Update_Height (x->right);
//        Update_Height (x->right->p);   //it was x->right->left
        Update_Height (ptr);
        Update_Height (ptr->p);   //it was x->right->left
      }

      printf ("left-rotate (%d)\n", x->key);  
      Left_Rotate (root, x);
      printf ("root is now: %d\n", (*root)->key);
      Update_Height (x);
      Update_Height (x->p);   //it was x->right
    }
  
  }

}

void
Left_Rotate (
  NODE **root,      
  NODE *x      
  )
{
  NODE *y;

  y = x->right;
  Transplant (root, x, y);  //replace x with y
  x->right = y->left;
  if (y->left != NIL) {  //may be NULL
    y->left->p = x;
  }
  y->left = x;
  x->p = y;
}

void
Right_Rotate (
  NODE **root,      
  NODE *y      
  )
{
  NODE *x;

  x = y->left;
  Transplant (root, y, x);  //replace y with x
  y->left = x->right;
  if (x->right != NIL) {
    x->right->p = y;
  }
  x->right = y;
  y->p = x;
}

//replace subtree
void
Transplant (
  NODE **root,
  NODE *u,
  NODE *v
  )
{
  //case: u is root
  if (!u->p) {
    v->p = NULL;    //important!  
    *root = v;
    return;
  }

  if (u == u->p->left) {
    u->p->left = v;
  } else {
    u->p->right = v;
  }

  //update v->p
  //v may be NULL !
  if (v) {
    v->p = u->p;
  }

}

NODE *
Create_Node (
  int key      
  )
{
  NODE *new;

  new = malloc (sizeof (NODE));
  new->key = key;
  new->h = 0;
  new->p = NULL;
  new->right = NIL;
  new->left = NIL;

  return new;
}

void 
InOrder_Tree_Walk (
  NODE *root      
  )
{
  //base case:
  if (root == NIL) {
    return;
  }
  InOrder_Tree_Walk (root->left);
  printf ("%d(h = %d, p = %d), ", root->key, root->h, (root->p ? root->p->key : -1));
  InOrder_Tree_Walk (root->right);
}

void
Update_Height (
  NODE *x      
  )
{
  x->h = MAX ((x->left->h), (x->right->h)) + 1;
}

