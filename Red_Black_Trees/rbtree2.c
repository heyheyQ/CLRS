/*
 * The program demonstrates red-black tree operations:
 * 
 * Rb-insert: inserting a node into an n-node red-black tree.
 * Rb-transplant, Rb-delete: deleting a node from a red-black tree.
 *
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _RBNODE {
  int key;
  struct _RBNODE *p;
  struct _RBNODE *left;
  struct _RBNODE *right;
  bool color;   //true: red, false: black
} RBNODE;

#define BLACK    false
#define RED      true

void
Left_Rotate (
  RBNODE **root,      
  RBNODE *x      
  );

void
Right_Rotate (
  RBNODE **root,      
  RBNODE *y      
  );

void 
InOrder_Tree_Walk (
  RBNODE *root      
  );

void
Tree_Insert (
  RBNODE **root,
  RBNODE *z
  );

//replace subtree
void
Transplant (
  RBNODE **root,
  RBNODE *u,
  RBNODE *v
  );

void
RbTree_Insert (
  RBNODE **root,
  RBNODE *z
  );

RBNODE *
Tree_Search (
  RBNODE *root,
  int key
  );

RBNODE *
Tree_Maximum (
  RBNODE *root
  );

void
RbTree_Delete (
  RBNODE **root,
  RBNODE *z
  );

void
RbTree_Fixup (
  RBNODE **root,
  RBNODE *x
  );

//global variable
RBNODE *NIL;   //sentinel

int
main (void)
{
//  int array[] = {41, 38, 31, 12, 19, 8};
//  int delarray[] = {8, 12, 19, 31, 38, 41};
//  int n = 6;
  int array[] = {11, 2, 14, 1, 7, 15, 5, 8, 4};
  int delarray[] = {8, 2, 4, 7, 1, 15, 5, 11, 14};
  int n = 9;

  int i, j;
  RBNODE *new;
  RBNODE *Tree = NULL;

  //initialize
  NIL = malloc (sizeof (RBNODE));
  NIL->key = 0x80000000;   //minus infinity
  NIL->color = BLACK;

  //test insert
  for (i = 0; i < n; i++) {
    new = malloc (sizeof (RBNODE));  
    new->key = array[i];
//    printf ("Insert: %d\n", new->key);
    RbTree_Insert (&Tree, new);
    //for debug
    InOrder_Tree_Walk (Tree);
    printf ("\n");

    //test
    if (i == 2) {
      printf ("--------------------------------------------------\n");  
      printf ("delete: %d\n", new->key);
      RbTree_Delete (&Tree, new);
      //for debug
      InOrder_Tree_Walk (Tree);
      printf ("\n");
      break;
    }
//    printf ("NIL now has color: %c\n", NIL->color ? 'r' : 'b');
  }

  return;

  InOrder_Tree_Walk (Tree);
  printf ("\n");

//  //for debug
//  for (i = 0; i < n; i++) {
//    new = Tree_Search (Tree, array[i]);    
//    printf ("%d has parent %d\n", new->key, new->p->key);
//  }  

  printf ("--------------------------------------------------------\n");

  //test delete
  for (i = 0; i < n; i++) {
    new = Tree_Search (Tree, delarray[i]);    
    printf ("delete: %d\n", new->key);
    RbTree_Delete (&Tree, new);
    //for debug
    InOrder_Tree_Walk (Tree);
    printf ("\n");
    //for debug
    for (j = 0; j < n; j++) {
      new = Tree_Search (Tree, array[j]);    
      if (new) {
        printf ("%d has parent %d\n", new->key, new->p->key);
      }
    }  
  }

  return 0;
}

void
Left_Rotate (
  RBNODE **root,      
  RBNODE *x      
  )
{
  RBNODE *y;

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
  RBNODE **root,      
  RBNODE *y      
  )
{
  RBNODE *x;

  x = y->left;
  Transplant (root, y, x);  //replace y with x
  y->left = x->right;
  if (x->right != NIL) {
    x->right->p = y;
  }
  x->right = y;
  y->p = x;
  printf ("Right_Rotate: y = %d, y->p = %d\n", y->key, y->p->key);
}

void 
InOrder_Tree_Walk (
  RBNODE *root      
  )
{
  //base case:
//  if (root == NULL) {
  if (root == NIL) {    //for rbtree
    return;
  }
  InOrder_Tree_Walk (root->left);
  printf ("%d (%c), ", root->key, root->color ? 'r' : 'b');
  InOrder_Tree_Walk (root->right);
}

void
Tree_Insert (
  RBNODE **root,
  RBNODE *z
  )
{
  RBNODE *x, *y;

  //assign root
  if (!(*root)) {
    *root = z;
    (*root)->p = NIL;   //for rbtree
//    printf ("(root)Tree_Insert: [%d]->p = [%d]\n", z->key, z->p->key);
    //for rbtree
    z->left = NIL;
    z->right = NIL;
    return;
  }
  //traverse
  y = *root;
  x = NIL;   //x is y's parent
  while (y != NIL) {
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

//  printf ("Tree_Insert: [%d]->p = [%d]\n", z->key, z->p->key);
  //insert to leaf's parent
  if (z->key < x->key) {
    x->left = z;
  } else {
    x->right = z;
  }
  //for rbtree
  z->left = NIL;
  z->right = NIL;
  z->color = RED;  //important!
}

void
Transplant (
  RBNODE **root,
  RBNODE *u,
  RBNODE *v
  )
{
  //case: u is root
//  if (!u->p) {
  if (u->p == NIL) {  //root
    v->p = NIL;  
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

void
RbTree_Insert (
  RBNODE **root,
  RBNODE *z
  )
{
  Tree_Insert (root, z);
  //restore RbTree property
  while (z->p->color == RED) {
    if (z->p == z->p->p->left) {
      if (z->p->p->right->color == RED) {
        //case 1: re-color and level up    
        printf ("case 1:\n");
        printf ("z->p is now %d, z->p->p is now %d\n", z->p->key, z->p->p->key);
        z->p->color = BLACK;
        z->p->p->right->color = BLACK;   //z->p's sibling
        z->p->p->color = RED;
        z = z->p->p;     //level up
        continue;
      } else if (z == z->p->right) {
        //case 2: zig-zag, left-rotate(z->p)      
        printf ("case 2:\n");
        z = z->p;
        Left_Rotate (root, z);
        //then fall through case 3
      }   
      //case 3: recolor and right-rotate(z->p->p)
      printf ("case 3:\n");
      printf ("z is now %d, z->p is now %d\n", z->key, z->p->key);
      z->p->color = BLACK;
      z->p->p->color = RED;
//      printf ("NIL now has color: %c\n", NIL->color ? 'r' : 'b');
      Right_Rotate (root, z->p->p);
      //done, cause z->p is now black.  
        
    } else {
      //symmetry    
      if (z->p->p->left->color == RED) {
        //case 1: re-color and level up    
        printf ("(right)case 1:\n");
        z->p->color = BLACK;
        z->p->p->left->color = BLACK;   //z->p's sibling
        z->p->p->color = RED;
        z = z->p->p;     //level up
        continue;
      } else if (z == z->p->left) {
        //case 2: zig-zag, left-rotate(z->p)      
        printf ("(right)case 2:\n");
        z = z->p;
        Right_Rotate (root, z);
        //then fall through case 3
      }   
      //case 3: recolor and right-rotate(z->p->p)
      printf ("(right)case 3:\n");
      z->p->color = BLACK;
      z->p->p->color = RED;
      Left_Rotate (root, z->p->p);
      //done, cause z->p is now black.  
        
    }    
      
  }
  //preserve
  (*root)->color = BLACK;

}

RBNODE *
Tree_Search (
  RBNODE *root,
  int key
  )
{
  //base case:
  if (root == NIL) {
    return NULL;  //not found    
  }

  if (key < root->key) {
    Tree_Search (root->left, key);    
  } else if (key > root->key) {
    Tree_Search (root->right, key);  
  } else {
    return root;    
  }
}

RBNODE *
Tree_Minimum (
  RBNODE *root
  )
{
  if (root == NIL) {
    return NULL;    
  }

  while (root->left != NIL) {
    root = root->left;    
  }
  return root;
}

void
RbTree_Delete (
  RBNODE **root,
  RBNODE *z
  )
{
  RBNODE *y, *x;
  bool y_org_color;

  y = z;
  y_org_color = y->color;

  if (z->left == NIL) {
    //case 1:    
    printf ("case 1:\n");
    x = z->right;
    printf ("z = %d, z->right = %d, z->p = %d\n", 
            z->key, z->right->key, z->p->key);
    Transplant (root, z, z->right);
  } else if (z->right == NIL) {
    //case 2:  
    printf ("case 2:\n");
    x = z->left;
    Transplant (root, z, z->left);
  } else {
    y = Tree_Minimum (z->right);   //successor  
    y_org_color = y->color;
    x = y->right;   //for both case 3 and 4.  
    if (y->p != z) {
      //case 3:  
//      x = y->right;   //successor has no left child  
      printf ("case 3:\n");
      Transplant (root, y, y->right);
      y->right = z->right;
      z->right->p = y;
      //fall through case 4.
    }
    //case 4:
    printf ("case 4:\n");
    Transplant (root, z, y);
    y->left = z->left;
    y->left->p = y;
    y->color = z->color;    //important!
  }

  //fix-up
  if (y_org_color == BLACK) {
      printf ("fix-up:\n");  
    RbTree_Fixup (root, x);    
  }
}

void
RbTree_Fixup (
  RBNODE **root,
  RBNODE *x
  )
{
  RBNODE *w;  //the sibling of x

  while (x != (*root) && x->color == BLACK) {
    if (x == x->p->left) {
      w = x->p->right;    
      printf ("x is %d, w is %d\n", x->key, w->key);
      if (w->color == RED) {
        //case 1:    
        printf ("fix-up: case 1.\n");
        w->color = BLACK;
        x->p->color = RED;
        Left_Rotate (root, x->p);
        w = x->p->right;          //new w, important!
        //falls through
      }   

      //w is black now
      if (w->left->color == BLACK && w->right->color == BLACK) {
        //case 2: level-up
        printf ("fix-up: case 2.\n");
        w->color = RED;
        x = x->p;   //if x->p was red, loop terminates
        continue;
      } else if (w->right->color == BLACK) {
        //w->left is red  
        printf ("fix-up: case 3.\n");
        w->color = RED;
        w->left->color = BLACK;   //make it to be case 4.
        Right_Rotate (root, w);
        w = x->p->right;          //new w, important!
        //fall through
      }
      //w->right is red
      printf ("fix-up: case 4.\n");
      w->color = x->p->color;
      x->p->color = BLACK;
      w->right->color = BLACK;    //for the case x->p was red, balance the bh
      Left_Rotate (root, x->p);   //increase the bh of x
      x = *root;                  //loop terminates
        
    } else {
      //symmetry  
      w = x->p->left;    
      printf ("(right): x is %d, w is %d\n", x->key, w->key);
      if (w->color == RED) {
        //case 1:    
        printf ("(right)fix-up: case 1.\n");
        w->color = BLACK;
        x->p->color = RED;
        Right_Rotate (root, x->p);
        w = x->p->left;          //new w, important!
        //falls through
      }   

      //w is black now
      if (w->left->color == BLACK && w->right->color == BLACK) {
        //case 2: level-up
        printf ("(right)fix-up: case 2.\n");
        w->color = RED;
        x = x->p;   //if x->p was red, loop terminates
        continue;
      } else if (w->left->color == BLACK) {
        //w->left is red  
        printf ("(right)fix-up: case 3.\n");
        w->color = RED;
        w->right->color = BLACK;   //make it to be case 4.
        Left_Rotate (root, w);
        w = x->p->left;          //new w, important!
        //fall through
      }
      //w->right is red
      printf ("(right)fix-up: case 4.\n");
      w->color = x->p->color;
      x->p->color = BLACK;
      w->left->color = BLACK;    //for the case x->p was red, balance the bh
      Right_Rotate (root, x->p);   //increase the bh of x
      x = *root;                  //loop terminates
        
    }    
          
  }         
        
  x->color = BLACK;   //x is root ?
}
