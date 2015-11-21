/*
 * Chap.13 Red-Black Trees in CLRS:
 * A red-black tree is a binary search tree with one extra bit of storage per node:
 * its color, which can be either Red or Black.
 * By constraining the node colors on any simple path from the root to a leaf,
 * red-black trees ensure that no such path is more than twice as long as any other.
 *
 * The program implements rotation operations, which are local operations
 * in a search tree that preserves the binary-search-tree property.
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"  //definitions of helper functions

#define MAX (a, b)  ((a) > (b) ? (a) : (b))

//for test
typedef struct _PRINT_NODE {
  NODE *node;  
  int pos;     //print indents
} PRINT_NODE;

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

//for test
void
Print_Tree (
  NODE *root,
  int n
  );

void
Print_Tree_v2 (
  NODE *root,
  int n
  );

void
Print_Node_v2 (
  NODE *x,
  int indent
  );

int
main (void)
{
  int array[] = {7, 4, 11, 3, 6, 9, 18, 2, 14, 19, 12, 17, 22, 20};
  int n = 14;
  int i;
  NODE *Tree = NULL;
  NODE *new;

  //build tree
  for (i = 0; i < n; i++) {
    new = malloc (sizeof (NODE));
    new->key = array[i];
    Tree_Insert (&Tree, new);
  }
  //print
  printf ("Tree:\n");
  InOrder_Tree_Walk (Tree);
  printf ("\n");

//  Print_Tree (Tree, n);
  Print_Tree_v2 (Tree, n);

//  //test left-rotate
//  new = Tree_Search (Tree, 11);
//  Left_Rotate (&Tree, new);
////  Print_Tree (Tree, n);
//  Print_Tree_v2 (Tree, n);
//
//  //test right-rotate
//  new = Tree_Search (Tree, 18);
//  Right_Rotate (&Tree, new);
////  Print_Tree (Tree, n);
//  Print_Tree_v2 (Tree, n);

  return 0;
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
  if (y->left) {  //may be NULL
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
  if (x->right) {
    x->right->p = y;
  }
  x->right = y;
  y->p = x;
}

//for test
void
Print_Tree (
  NODE *root,
  int n
  )
{
  NODE *tmp;
  int i;
  PRINT_NODE *array;
  int idx;      //use array as a queue, to store the nodes at the same level
  int start, lstart;
  int j;
  int blank;
  float fblank;
  float bound;
  int k;
  int count;
  int pos;
  int p;

  printf ("Print_Tree:\n");
  array = malloc (sizeof (PRINT_NODE) * n/2);   //last level: at most n/2 nodes
  //level 0: root
  blank = 32;    //indent = 40
  fblank = 32;
  idx = -1;
  lstart = 0;
  start = 0;
  array[++idx].node = root;   //idx = 0
  array[idx].pos = 0;
  count = 1;             //root

  for (i = 1; i < n; i++) {  //height: at most n-1
//    printf ("start = %d, idx = %d\n", start, idx);
    for (j = start; j<= idx; j++) {  //fifo: queue
      //print indent  
      if (array[j].pos > 0) {
        if (j-1 >= start) {
          pos = array[j].pos - array[j-1].pos - 1;
        } else {
          pos = array[j].pos;
        }
      } else {
        pos = 0;
      } 
//      printf ("key = %d, pos = %d\n", array[j].node->key, pos);
//      for (p = 0; p < (/*array[j].pos*/pos << 1); p++) {
//        //print indent 
//        for (k = 0; k < blank; k++) {
//          printf (" ");
//        }
//      }
      bound = fblank * (float)(pos <<1);
      for (k = 0; k < (int)bound; k++) {
        printf (" ");
      }

      //print indent 
      for (k = 0; k < blank; k++) {
        printf (" ");
      }
      printf ("%d", array[j].node->key);
      //print indent  
      for (k = 0; k < blank; k++) {
        printf (" ");
      }
      count++;
    }
    printf ("\n");

    if (count > n) {
      break;    //break for (i)
    }

    //push next level
    lstart = start;
    start = j;
//    printf ("lstart = %d, start = %d\n", lstart, start);
    if (start >= (n/2-1)) {
      //circular
      start = 0;
    }

    pos = 0;
    for (j = lstart; j<= idx; j++) {  //fifo: queue
      tmp = array[j].node;  //pop
      pos = array[j].pos;
      //push
      if (tmp->left) {
        array[start].node = tmp->left;
        array[start].pos = (pos<<1);
//        //for indent
//        if (array[start].pos > 0) {
//          if (start-1 >= 0) {
//            array[start].pos -= array[start-1].pos;
//            array[start].pos -= 1;
//          }
//        }

        start++;
      }
//      pos++; //left child
      if (tmp->right) {
        array[start].node = tmp->right;
        array[start].pos = ((pos<<1) + 1);
//        //for indent
//        if (array[start].pos > 0) {
//          if (start-1 >= 0) {
//            array[start].pos -= array[start-1].pos;
//            array[start].pos -= 1;
//          }
//        }

        start++;
      }
//      pos++; //right child
    }  //end pop and push    
    lstart = idx+1;
    idx = start-1;
    if (lstart > idx) {
      start = 0;
    } else {
      start = lstart;
    }

    blank = blank >> 1;    // blank/2
    if (blank < 1) {
      blank = 1;
    }
    fblank = fblank/2;
  }  //end for (i) levels
}

void
Print_Tree_v2 (
  NODE *root,
  int n
  )
{
  NODE *tmp;
  NODE **array;
  int idx, idx2;      //use array as a queue, to store the nodes at the same level
  int start, start2;
  int count;
  int i, j;
  int indent;
  int size;
  int target;

//  size = n;        //2 levels node in the queue  
  for (i = 1, size = 2; i < n; i++) {
    size <<= 1;    //*2
  }
  //size = 2^n
  array = malloc (sizeof (NODE *) * size);

  indent = 36;
  idx = -1;
  start2 = 0;
  start = 0;
  array[++idx] = root;   //idx = 0
  count = 1;             //root

  Print_Node_v2 (root, indent);
  printf ("\n");
  indent = indent >> 1;      // /2

  for (i = 1; i < n; i++) {  //height: at most n-1
//    printf ("start = %d, idx = %d\n", start, idx);  
//    if (idx >= start) {
//      printf ("i = %d, (idx-start+1) = %d\n", i , idx-start+1);
//    } else {
//      printf ("i = %d, (size-start+idx+1) = %d\n", i , size-start+idx+1);
//    }
    start2 = idx+1;
    idx2 = idx;
    if (start2 >= size) {
      //circular
      start2 = 0;
      idx2 = -1;
    }
//    printf ("start2 = %d, idx2 = %d\n", start2, idx2);  

    target = idx;
    if (idx < start) {
      target = size - 1;
    } 
    for (j = start; j <= target; j++) {
//      //print children
//      tmp = array[j];
//      Print_Node_v2 (tmp->left, indent);
//      Print_Node_v2 (tmp->right, indent);
//      //pop and push
//      if (tmp->left) {
//        if (++idx2 >= size) {
//          //circular
//          idx2 = 0;
//        }  
//        array[idx2] = tmp->left; 
//        count++;
//      }
//      if (tmp->right) {
//        if (++idx2 >= size) {
//          //circular
//          idx2 = 0;
//        }  
//        array[idx2] = tmp->right; 
//        count++;
//      }
      //print children
      tmp = array[j];
      if (tmp) {
        Print_Node_v2 (tmp->left, indent);
        Print_Node_v2 (tmp->right, indent);
        //pop and push
        if (++idx2 >= size) {
          //circular
          idx2 = 0;
        }  
        array[idx2] = tmp->left; 
        if (tmp->left) {
          count++;
        }

        if (++idx2 >= size) {
          //circular
          idx2 = 0;
        }  
        array[idx2] = tmp->right; 
        if (tmp->right) {
          count++;
        }  
      } else {
        Print_Node_v2 (NULL, indent);
        Print_Node_v2 (NULL, indent);
        //pop and push
        if (++idx2 >= size) {
          //circular
          idx2 = 0;
        }  
        array[idx2] = NULL; 

        if (++idx2 >= size) {
          //circular
          idx2 = 0;
        }  
        array[idx2] = NULL; 
      }
    }
    //circular
    if (target != idx) {
//      printf ("overflow: start2 = %d, idx2 = %d\n", start2, idx2);  
      for (j = 0; j <= idx; j++) {
        //print children
        tmp = array[j];
        if (tmp) {
          Print_Node_v2 (tmp->left, indent);
          Print_Node_v2 (tmp->right, indent);
          //pop and push
          if (++idx2 >= size) {
            //circular
            idx2 = 0;
          }  
          array[idx2] = tmp->left; 
          if (tmp->left) {
            count++;
          }

          if (++idx2 >= size) {
            //circular
            idx2 = 0;
          }  
          array[idx2] = tmp->right; 
          if (tmp->right) {
            count++;
          }  
        } else {
          Print_Node_v2 (NULL, indent);
          Print_Node_v2 (NULL, indent);
          //pop and push
          if (++idx2 >= size) {
            //circular
            idx2 = 0;
          }  
          array[idx2] = NULL; 

          if (++idx2 >= size) {
            //circular
            idx2 = 0;
          }  
          array[idx2] = NULL; 
        }

      }
    }  //circular
    printf ("\n");

    //update index
    start = start2;
    idx = idx2;
    indent = indent >> 1;   // /2

    if (count >= n) {
      break;  //break for (i)
    }
  }      

}

void
Print_Node_v2 (
  NODE *x,
  int indent
  )
{
  int k;

//  for (k = 0; k < indent; k++) {
//    printf (" ");
//  }
//  if (x) {
//    printf ("%2d", x->key);
//  } else {
//    printf ("  ");
//  }
  if (x) {
    printf ("%*d", indent, x->key);
  } else {
    for (k = 0; k < indent; k++) {
      printf (" ");
    }
  }

  for (k = 0; k < indent; k++) {
    printf (" ");
  }

}
