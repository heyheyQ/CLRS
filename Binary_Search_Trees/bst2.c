/*
 * The program implements helper functions
 * to maintain the binary-search-tree property.
 *
 * The helper functions include Transplant which replaces one
 * subtree as a child of its parent with another subtree.
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"  //definitions of helper functions

////replace subtree
//void
//Transplant (
//  NODE **root,
//  NODE *u,
//  NODE *v
//  );
//
//void
//Tree_Delete (
//  NODE **root,
//  NODE *z
//  );

//use predecessor instead of successor
void
Tree_Delete_v2 (
  NODE **root,
  NODE *z
  );

void
Print_Node (      
  NODE *new
  );

//int
//main (void)
//{
////  int array[] = {12, 5, 18, 2, 9, 15, 19, 17};
////  int n = 8;
//  int array[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
//  int n = 11;
//  int i;
//  NODE *Tree = NULL;
//  NODE *new;
//
//  //build tree
//  for (i = 0; i < n; i++) {
//    new = malloc (sizeof (NODE));
//    new->key = array[i];
//    Tree_Insert (&Tree, new);
//  }
//  //print
//  printf ("Tree:\n");
//  InOrder_Tree_Walk (Tree);
//  printf ("\n");
//
////  //test insert
////  new = malloc (sizeof (NODE));
////  new->key = 13;
////  Tree_Insert (&Tree, new);
////  //print
////  printf ("Tree:\n");
////  InOrder_Tree_Walk (Tree);
////  printf ("\n");
//
//  //test delete
//  //search first
//  new = Tree_Search (Tree, 13);
//  //for debug
//  Print_Node (new);
////  if (new) {
////    printf ("search: key = %d, p = 0x%x, left = 0x%x, right = 0x%x\n",
////            new->key, (int)(new->p), (int)(new->left), (int)(new->right));
////    if (new->p) {
////      printf ("p = %d, ", new->p->key);
////    }
////    if (new->left) {
////      printf ("left = %d, ", new->left->key);
////    }
////    if (new->right) {
////      printf ("right = %d, ", new->right->key);
////    }
////    printf ("\n");
////  } else {
////    printf ("search: not found.\n");
////  }
//  Tree_Delete (&Tree, new);
//  //print
//  printf ("After delete %d:\n", new->key);
//  InOrder_Tree_Walk (Tree);
//  printf ("\n");
//  free (new);
//
//  //test delete v2
//  new = Tree_Search (Tree, 15);
//  Tree_Delete_v2 (&Tree, new);
//  //print
//  printf ("After deletev2 %d:\n", new->key);
//  InOrder_Tree_Walk (Tree);
//  printf ("\n");
//  free (new);
//
//  for (i = 0; i < n; i++) {
//    new = Tree_Search (Tree, array[i]);
//    Print_Node (new);
//  }
//
//  return 0;
//}

void
Transplant (
  NODE **root,
  NODE *u,
  NODE *v
  )
{
  //case: u is root
  if (!u->p) {
    v->p = NULL;  
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
Tree_Delete (
  NODE **root,
  NODE *z
  )
{
  NODE *y;

  if (!z->left) {
    //either z->right is null (no child)
    //or z->right only (replace z with z->right)
    printf ("case 1:\n");
    Transplant (root, z, z->right);
  } else if (!z->right) {
    //z->left only, replace z with z->left
    printf ("case 2:\n");
    Transplant (root, z, z->left);
  } else {
    //z->left and z->right are valid,
    //find successor(z):
    y = Tree_Successor (z);  //y must in the right subtree of z
    printf ("successor of %d is:\n", z->key);
    Print_Node (y);
//    //for debug
//    if (y) {
//      printf ("successor: key = %d, p = 0x%x, left = 0x%x, right = 0x%x\n",
//              y->key, (int)(y->p), (int)(y->left), (int)(y->right));
//      if (y->p) {
//        printf ("p = %d, ", y->p->key);
//      }
//      if (y->left) {
//        printf ("left = %d, ", y->left->key);
//      }
//      if (y->right) {
//        printf ("right = %d, ", y->right->key);
//      }
//      printf ("\n");
//    } else {
//      printf ("successor: not found.\n");
//    }

    //and y has no left childs !!
    if (y->p != z) {
      printf ("case 3:\n");
      //replace y with y->right
      //update childs manually:
      //Transplant () updates parents only
      Transplant (root, y, y->right);
      y->right = z->right;
      z->right->p = y;
    }
    printf ("case 4:\n");
    //if y == z->right, replace z with y directly
    Transplant (root, z, y);
    //z has left childs, update their parents
    y->left = z->left;
    z->left->p = y;
  }
}

//use predecessor instead of successor
void
Tree_Delete_v2 (
  NODE **root,
  NODE *z
  )
{
  NODE *y;

  if (!z->left) {
    //either z->right is null (no child)
    //or z->right only (replace z with z->right)
    printf ("case 1:\n");
    Transplant (root, z, z->right);
  } else if (!z->right) {
    //z->left only, replace z with z->left
    printf ("case 2:\n");
    Transplant (root, z, z->left);
  } else {
    //both z->right and z->left are valid
    y = Tree_Predecessor (z);
    printf ("Predecessor of %d is:\n", z->key);
    Print_Node (y);
    if (y != z->left) {
      //replace y with y->left
      //y has no right child
      Transplant (root, y, y->left);
      y->left = z->left;
      z->left->p = y;
    }
    //if y == z->left, replace z with y directly
    Transplant (root, z, y);
    y->right = z->right;
    z->right->p = y;
  }
}

void
Print_Node (      
  NODE *new
  )
{
  if (new) {
//    printf ("search: key = %d, p = 0x%x, left = 0x%x, right = 0x%x\n",
//            new->key, (int)(new->p), (int)(new->left), (int)(new->right));
    printf ("key = %d, ", new->key);
    if (new->p) {
      printf ("p = %d, ", new->p->key);
    }
    if (new->left) {
      printf ("left = %d, ", new->left->key);
    }
    if (new->right) {
      printf ("right = %d, ", new->right->key);
    }
    printf ("\n");
  } else {
    printf ("NULL node.\n");
  }
}
