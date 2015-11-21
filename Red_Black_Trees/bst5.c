/*
 * Problem 13-1 in CLRS: Persistent dynamic sets
 * We sometimes find that we need to maintain past versions of
 * a dynamic set as it is updated. We all such a set persistent.
 *
 * The program demonstrates how to operate a persistent binary search tree.
 */

#include <stdio.h>
#include <stdlib.h>

//wo parent
typedef struct _NODE {
  int key;
  struct _NODE *left;
  struct _NODE *right;
} NODE;

//to build the sample tree
void
Tree_Insert (
  NODE **root,
  NODE *z
  );

//for debug
void 
InOrder_Tree_Walk (
  NODE *root      
  );

//print addr of node, not key
void 
InOrder_Tree_Walk_Addr (
  NODE *root      
  );

//return new_root
NODE *
Persistent_Tree_Insert (
  NODE *root,      
  int key      
  );

NODE *
Persistent_Tree_Delete (
  NODE *root,      
  NODE *z     
  );

//helper
NODE *
Tree_Minimum (
  NODE *root      
  );

NODE *
Tree_Search (
  NODE *root,
  int key
  );

NODE *
Copy_Node (
  NODE *x
  );

NODE *
Create_Node (
  int key      
  );

int
main (void)
{
//  int array[] = {4, 3, 8, 2, 7, 10};
//  int n = 6;
//  int array[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
//  int n = 11;
  int array[] = {2, 4, 3, 7, 6, 8, 5};
  int n = 7;
  int i;
  NODE *new;
  NODE *Tree = NULL;
  NODE *z;   //for delete

  //build the sample tree
  for (i = 0; i < n; i++) {
    new = malloc (sizeof (NODE));
    new->key = array[i];
    Tree_Insert (&Tree, new);
  }

  InOrder_Tree_Walk (Tree);
  printf ("\n");

//  //test insert
//  new = Persistent_Tree_Insert (Tree, 5);
//
//  printf ("old tree:\n");
//  InOrder_Tree_Walk (Tree);
//  printf ("\n");
//
//  printf ("new tree:\n");
//  InOrder_Tree_Walk (new);
//  printf ("\n");
//
//  //check the addr
//  printf ("old tree:\n");
//  InOrder_Tree_Walk_Addr (Tree);
//  printf ("\n");
//  printf ("new tree:\n");
//  InOrder_Tree_Walk_Addr (new);
//  printf ("\n");

  //test delete
//  z = Tree_Search (Tree, 6);   //case 4: z->successor == z->right
//  z = Tree_Search (Tree, 7);   //case 1: z->left is NULL
//  z = Tree_Search (Tree, 3);   //case 4: z->successor == z->right
  z = Tree_Search (Tree, 4);   //case 3: z->successor != z->right
  new = Persistent_Tree_Delete (Tree, z);

  //check the key
  printf ("old tree:\n");
  InOrder_Tree_Walk (Tree);
  printf ("\n");
  printf ("new tree:\n");
  InOrder_Tree_Walk (new);
  printf ("\n");

  //check the addr
  printf ("old tree:\n");
  InOrder_Tree_Walk_Addr (Tree);
  printf ("\n");
  printf ("new tree:\n");
  InOrder_Tree_Walk_Addr (new);
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

//print addr of node, not key
void 
InOrder_Tree_Walk_Addr (
  NODE *root      
  )
{
  //base case:
  if (root == NULL) {
    return;
  }
  InOrder_Tree_Walk_Addr (root->left);
  printf ("(%d)%p, ", root->key, root);
  InOrder_Tree_Walk_Addr (root->right);

}

void
Tree_Insert (
  NODE **root,
  NODE *z
  )
{
  NODE *x, *y;

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

//return new_root
NODE *
Persistent_Tree_Insert (
  NODE *root,      
  int key      
  )
{
  NODE *tmp, *p, *new_root, *new_node, *op;

  if (!root) {
    //empty tree
    new_root = Create_Node (key);
  } else {
    tmp = root;
    new_root = Copy_Node (root);
    p = new_root;   //track the new tree
    op = NULL;

    while (tmp) {
      if (key < tmp->key) {
        new_node = Copy_Node (tmp->left);
        p->left = new_node;   //track the new tree
        op = p;
        p = p->left;
        tmp = tmp->left;      //track the old tree
      } else {
        new_node = Copy_Node (tmp->right);
        p->right = new_node;   //track the new tree
        op = p;
        p = p->right;
        tmp = tmp->right;      //track the old tree
      }  
    }  //end while ()
  
    new_node = Create_Node (key);
    if (key < op->key) {
      op->left = new_node;
    } else {
      op->right = new_node;
    }
  }

  return new_root;
}

NODE *
Persistent_Tree_Delete (
  NODE *root,      
  NODE *z     
  )
{
  
  NODE *tmp, *p, *new_root, *new_node, *op;
  NODE *y;             //the successor
  NODE *new_z_right = NULL;   //for case 3

  if (!root) {
    //empty tree
    return NULL;   //nothing to delete
  }

  //search and copy: do not copy z !
  tmp = root;
  new_root = Copy_Node (root);
  p = new_root;   //track the new tree
  op = NULL;

  while (tmp) {
    if (z->key < tmp->key) {
      if (tmp->left == z) {
        printf ("tmp = %d, tmp->left == %d\n", tmp->key, tmp->left->key);
        break;
      }

      new_node = Copy_Node (tmp->left);
      p->left = new_node;   //track the new tree
//      op = p;
      p = p->left;
      tmp = tmp->left;      //track the old tree
    } else if (z->key > tmp->key) {
      if (tmp->right == z) {
        printf ("tmp = %d, tmp->right == %d\n", tmp->key, tmp->right->key);
        break;
      }

      new_node = Copy_Node (tmp->right);
      p->right = new_node;   //track the new tree
//      op = p;
      p = p->right;
      tmp = tmp->right;      //track the old tree
    } else {
      //found z
      break;
    } 
  }  //end while ()

  printf ("delete %d:\n", z->key);
  //p is z's parent
  //tree delete cases:
  if (!z->left) {
    //case 1: Transplant (z, z->right)
    printf ("case 1:\n");
    new_node = Copy_Node (z->right);   //may be NULL
    if (z == p->left) {
      p->left = new_node;
    } else {
      p->right = new_node;
    }
  } else if (!z->right) {
    //case 2: Transplant (z, z->left)
    printf ("case 2:\n");
    new_node = Copy_Node (z->left);
    if (z == p->left) {
      p->left = new_node;
    } else {
      p->right = new_node;
    }
  } else {
    //both z->right and z->left are valid
    y = Tree_Minimum (z->right); 
    if (y != z->right) {
      //case 3: Transplant (y, y->right)
      //search and copy from z to y:
      printf ("case 3:\n");
      tmp = z->right;
      new_z_right = Copy_Node (z->right);
      op = new_z_right;                 //trace the new tree
      //trace until y
      while (tmp->left && tmp->left != y) {
        new_node = Copy_Node (tmp->left);
        op->left = new_node;
        tmp = tmp->left;
        op = op->left;                   //trace the new tree
      }
      //y and z were not copied
      //Transplant (y, y->right)
      new_node = Copy_Node (y->right);
      op->left = new_node;             //replace y in the new tree
    }
    //case 4: Transplant (z, y)
    printf ("case 4:\n");
    printf ("y = %d, p = %d\n", y->key, p->key);
    new_node = Copy_Node (y);
    if (z == p->left) {
      p->left = new_node;
    } else {
      p->right = new_node;
    }
    if (new_z_right) {
      //case 3 falls through
      printf ("new_z_right = %d\n", new_z_right->key);
      new_node->right = new_z_right;
    }
    //z's left child
    new_node->left = z->left;
    
  }

  return new_root;
}

//helper
NODE *
Tree_Minimum (
  NODE *root      
  )
{
  if (!root) {
    return NULL;
  }

  while (root->left) {
    root = root->left;
  }

  return root;
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
Copy_Node (
  NODE *x
  )
{
  NODE *new;

  if (!x) {
    return NULL;
  }

  new = malloc (sizeof (NODE));
  new->key = x->key;
  new->right = x->right;   //copy links
  new->left = x->left;

  return new;
}

NODE *
Create_Node (
  int key      
  )
{
  NODE *new;

  new = malloc (sizeof (NODE));
  new->key = key;
  new->right = NULL;
  new->left = NULL;

  return new;
}
