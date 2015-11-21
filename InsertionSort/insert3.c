/*
 * The program implements an insertion sort algorithm
 * which sorts an array of linked list items.
 */ 

#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE {
  int data;
  struct _NODE *link;
} NODE;

//return listhead
NODE *
insertion3 (
  NODE *A,
  int n
  );

//int array[] = {3, 7, 8, 5, 4, 1, 2};
//int n = 7;
NODE array[] = {{3, NULL}, {7, NULL}, {8, NULL}, {5, NULL}, {4, NULL}, {1, NULL}, {2, NULL}};
int n = 7;

int
main (void)
{
  int k;
  NODE *listhead;
  NODE *item;

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k].data);
  }
  printf ("\n");

  listhead = insertion3 (array, n);

  item = listhead;
  while (item) {
    printf ("%d  ", item->data);
    item = item->link;
  }
  printf ("\n");

  return 0;
}

NODE *
insertion3 (
  NODE *A,
  int n
  )
{
  NODE *head = &A[0];
  NODE *tmp;
  int j;

  for (j = 1; j < n; j++) {
    //append the smallest to the head
    if (A[j].data < head->data) {
      A[j].link = head; 
      head = &A[j];
      continue;
    }
  
    tmp = head;
    while (tmp->link && A[j].data > tmp->link->data) {
      tmp = tmp->link;  
    }
    A[j].link = tmp->link;
    tmp->link = &A[j];
  }
  return head;
}

