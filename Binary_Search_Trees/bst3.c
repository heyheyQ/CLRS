/*
 * The program implements an algorithm to search for a key stored in
 * a binary search tree and to delete the node found from the tree.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _NODE {
  int key;
  struct _NODE *succ;
  struct _NODE *left;
  struct _NODE *right;
} NODE;

void
Succ_Tree_Insert (
  NODE **root,
  NODE *z
  );

void 
Succ_InOrder_Tree_Walk (
  NODE *root      
  );

NODE *
Succ_Tree_Minimum (
  NODE *root      
  );

NODE *
Succ_Tree_Search (
  NODE *root,
  int key
  );

NODE *
Parent (
  NODE *root,
  NODE *x
  );

void
Succ_Transplant (
  NODE **root,   //may be empty tree
  NODE *u,
  NODE *v
  );

void
Succ_Tree_Delete (
  NODE **root,
  NODE *x
  );

void
Print_Node (      
  NODE *new
  );

int
main (void)
{
//  int array[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
//  int n = 11;
  int array[] = {15, 6, 18, 3, 8, 17, 20, 2, 4, 7, 13, 9};
  int n = 12;
  int i;
  NODE *Tree = NULL;
  NODE *new, *p;

  //build tree
  for (i = 0; i < n; i++) {
    new = malloc (sizeof (NODE));
    new->key = array[i];
    Succ_Tree_Insert (&Tree, new);
  }
  //print
  Succ_InOrder_Tree_Walk (Tree);

//  for (i = 0; i < n; i++) {
//    //test search
//    new = Succ_Tree_Search (Tree, array[i]);
////    new = Succ_Tree_Search (Tree, 16);
//    //for debug
//    Print_Node (new);
//  }
//
//  //test parent  
//  for (i = 0; i < n; i++) {
//    new = Succ_Tree_Search (Tree, array[i]);
//    printf ("parent of %d: ", array[i]);
//    p = Parent (Tree, new);
//    Print_Node (p);
//  }    

  //test delete
  new = Succ_Tree_Search (Tree, 13);
  Succ_Tree_Delete (&Tree, new);
  //print
  Succ_InOrder_Tree_Walk (Tree);

  //test delete
  new = Succ_Tree_Search (Tree, 8);
  Succ_Tree_Delete (&Tree, new);
  //print
  Succ_InOrder_Tree_Walk (Tree);

  return 0;
}

void
Succ_Tree_Insert (
  NODE **root,
  NODE *z
  )
{
  NODE *p, *x;
  NODE *lpre;  //for left child case

  if (!(*root)) {
    //empty tree
    *root = z;
    return;
  }

  p = NULL;
  x = *root;
  lpre = NULL;  //for left child case
  while (x) {
    p = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      lpre = x;   //for left child case
      x = x->right;
    }
  }

  //insert
  if (z->key < p->key) {
    p->left = z;
    z->succ = p;  //important!
//    printf ("lpre: 0x%x\n", (int)lpre);
    if (lpre) {
      //if z is minimum: no one's succ
      lpre->succ = z;  //important!
    }
  } else {
    p->right = z;
    z->succ = p->succ;  //important!
    p->succ = z;       //important!
  }
}

void 
Succ_InOrder_Tree_Walk (
  NODE *root      
  )
{
  NODE *min;

  min = Succ_Tree_Minimum (root);

  while (min) {
    printf ("%d, ", min->key);
    min = min->succ;
  }
  printf ("\n");
}

NODE *
Succ_Tree_Minimum (
  NODE *root      
  )
{
  NODE *min;

  min = root;
  while (min->left) {
    min = min->left;
  }
  return min;
}

NODE *
Succ_Tree_Search (
  NODE *root,
  int key
  )
{
  while (root) {
    if (key < root->key) {
      root = root->left;
    } else if (key > root->key) {
      root = root->right;
    } else {
      //found
      break;
    }
  }
  return root;
}

NODE *
Parent (
  NODE *root,
  NODE *x
  )
{
  NODE *tmp, *ptmp;
  NODE *prev;

//  printf ("find parent of %d\n", x->key);
  tmp = NULL;
  ptmp = NULL;
  if (x->right) {
    tmp = x->right->succ;
  } else {
    tmp = x->succ;
  }

  if (tmp) {
    //tmp may still be child of x
    //tmp = tmp->succ until tmp goes above x
    prev = NULL;
    while (tmp) {
      if (tmp->left) {
        if (tmp->left != prev) {
          //prev == tmp->left: means go down again.
          break;
        }
      }  
      prev = tmp;
      tmp = tmp->succ;
    }
    if (!tmp) {
      return NULL;
    }

    ptmp = tmp;
    tmp = tmp->left;  //only once
  } else {
    //for the cases: x is maximum or x->right is minimum
    //traverse from root
    ptmp = NULL;
    tmp = root;
  }
  while (tmp != x) {
    ptmp = tmp;
    tmp = tmp->right;
  }

  return ptmp;
}

void
Succ_Transplant (
  NODE **root,
  NODE *u,
  NODE *v
  )
{
  NODE *p;
  p = Parent ((*root), u);
  printf ("parent of %d:\n", u->key);
  Print_Node (p);

  if (!p) {
    //u is root
    *root = v;
    return;
  }

  if (p->left == u) {
    p->left = v;
  } else {
    p->right = v;    
  }
  //does't update childs of u and v
}

void
Succ_Tree_Delete (
  NODE **root,
  NODE *x
  )
{
   NODE *z, *p;

   printf ("start to find z:\n");
   printf ("x is now:\n");
   Print_Node (x);
   //find z, such that z->succ=x, update z->succ=x->succ
   z = NULL;
   p = NULL;
   if (x->left) {
     //z may be in x's left subtree    
     printf ("case z-1:\n");
     z = x->left;
     while (z && z->succ != x) {
       z = z->right;    
     }
   }
   if (!z) {
     //z is not in x's left subtree    
     p = Parent ((*root), x);
     printf ("parent of %d:\n", x->key);
     Print_Node (p);
     if (!p) {
       printf ("case z-2:\n");
       return;  //x is root and has no left child??    
     }

     if (p->right == x) {
       printf ("case z-3:\n");
       z = p;    
     } else {
       //p->left == x  
       //z->right->left->left->......->left = x
       printf ("case z-4:\n");
       do {
         z = p;
         p = Parent ((*root), z);
       } while (p && p->left == z);    
       z = p;
     }
   }
   printf ("z is:\n");
   Print_Node (z);
   //end of finding z

   if (!x->left) {
     //either x->right == NULL or not
     printf ("case 1:\n");
     Succ_Transplant (root, x, x->right);
   } else if (!x->right) {
     //x->left only
     printf ("case 2:\n");
     Succ_Transplant (root, x, x->left);
   } else {
     //both x->left and x->right are valid    
     if (x->succ != x->right) {
       //replace x->succ with x->succ->right
       //x->succ is in x's right subtree, and x->succ has no left child.
       printf ("case 3:\n");
       Succ_Transplant (root, x->succ, x->succ->right);
       x->succ->right = x->right;
     }
     //replace x with x->succ
     printf ("case 4:\n");
     Succ_Transplant (root, x, x->succ);
     x->succ->left = x->left;
   }       

//   printf ("start to find z:\n");
//   printf ("x is now:\n");
//   Print_Node (x);
//   //find z, such that z->succ=x, update z->succ=x->succ
//   z = NULL;
//   p = NULL;
//   if (x->left != NULL) {
//     //z may be in x's left subtree    
//     printf ("case z-1:\n");
//     z = x->left;
//     while (z && z->succ != x) {
//       z = z->right;    
//     }
//   }
//   if (z == NULL) {
//     //z is not in x's left subtree    
//     p = Parent ((*root), x);
//     printf ("parent of %d:\n", x->key);
//     Print_Node (p);
//     if (!p) {
//       printf ("case z-2:\n");
//       return;  //x is root and has no left child??    
//     }
//
//     if (p->right == x) {
//       printf ("case z-3:\n");
//       z = p;    
//     } else {
//       printf ("case z-4:\n");
//       do {
//         z = p;
//         p = Parent ((*root), z);
//       } while (p->right == z);    
//     }
//   }
   if (z) {
     z->succ = x->succ;  //x is deleted completely
   } else {
     //z may be null: when x is the minimum
     x->succ = NULL;   //x is deleted, break the bound      
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
    if (new->succ) {
      printf ("succ = %d, ", new->succ->key);
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
