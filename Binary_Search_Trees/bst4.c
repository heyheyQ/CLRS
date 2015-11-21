/*
 * The program demonstrates how tree-insert operation works.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _NODE {
  char *key;             //may be NULL: empty node  
  struct _NODE *p;
  struct _NODE *left;
  struct _NODE *right;
} NODE;

void
InsertToRight (
  NODE *p,
  NODE *new
  );

void
InsertToLeft (
  NODE *p,
  NODE *new
  );

void
PrintByOrder (
  NODE *root      
  );

//helper
void
Print_Node (      
  NODE *new
  );

int
main (void)
{
  char *input[] = {"1011", "10", "011", "100", "0"};
  int n = 5;
  int i;
  char *s;
  NODE Root;
  NODE *new, *p;

  Root.key = NULL;   //empty node
  Root.p = NULL;
  Root.left = NULL;
  Root.right = NULL;

  //for test
  printf ("inputs: \n");
  for (i = 0; i < n; i++) {
    printf ("%s ", input[i]);
    printf ("(len = %d)\n", strlen (input[i]));
  }    

  for (i = 0; i < n; i++) {
//    printf ("%s\n", input[i]);
    s = input[i];
    p = &Root;
    //insert input[i] to the tree
    while (*(s+1) != '\0') {
//      printf ("*s = %c\n", *s);
      if (*s == '1') {
        if (!p->right) {
          new = malloc (sizeof (NODE));
          new->key = NULL;   //empty node
          InsertToRight (p, new);
        }
        p = p->right; 
      } else {
        //*s == '0'
        if (!p->left) {
          new = malloc (sizeof (NODE));
          new->key = NULL;   //empty node
          InsertToLeft (p, new);
        }
        p = p->left;
      }
      s++;   //increment !
 //     printf ("*(s+1) = %c\n", *(s+1));
    }  //end while ()
 //   printf ("while 1 done.\n");
 //   printf ("parent: \n");
 //   Print_Node (p);

    //create valid node for input[i]
    if (*s == '1') {
      if (!p->right) {
        new = malloc (sizeof (NODE));
        InsertToRight (p, new);
      }
      p->right->key = malloc (strlen(input[i])+1);  //assume distinct key
      strcpy (p->right->key, input[i]);
    } else {
      //*s == '0'
      if (!p->left) {
        new = malloc (sizeof (NODE));
        InsertToLeft (p, new);
      }
      p->left->key = malloc (strlen(input[i])+1);  //assume distinct key
      strcpy (p->left->key, input[i]);
    }
  
  }  //end for (i)

  printf ("result:\n");
  PrintByOrder (&Root);
  printf ("\n");

  return 0;
}

void
InsertToRight (
  NODE *p,
  NODE *new
  )
{
  if (!p) {
    return;
  }

  p->right = new;
  new->p = p;
}

void
InsertToLeft (
  NODE *p,
  NODE *new
  )
{
  if (!p) {
    return;
  }

  p->left = new;
  new->p = p;
}

void
PrintByOrder (
  NODE *root      
  )
{
  //base case
  if (!root) {
    return;
  }
  if (root->key) {
    printf ("%s, ", root->key);
  }
  PrintByOrder (root->left);
  PrintByOrder (root->right);

}

void
Print_Node (      
  NODE *new
  )
{
  if (new) {
    if (new->key) {
      printf ("key = %s, ", new->key);
    }
    if (new->p) {
      printf ("p = 0x%x, ", (int)new->p);
    }
    if (new->left) {
      printf ("left = 0x%x, ", (int)new->left);
    }
    if (new->right) {
      printf ("right = 0x%x, ", (int)new->right);
    }
    printf ("\n");
  } else {
    printf ("NULL node.\n");
  }
}
