/*
 * The program implements an insertion sort algorithm
 * which sorts an linked-list.
 */ 

#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE {
  int data;
  struct _NODE *link;
} NODE;

void
insertion4 (
  NODE **head  //listhead changed when return      
  );

int
main (void)
{
  int k, j;
//  int n = 5;
//  int array[] = {3, 6, 8, 7, 4};
//  int n = 7;
//  int array[] = {3, 7, 8, 5, 4, 1, 2};
  int array[] = {11, 6, 10, 13, 5, 8, 3, 2, 1};
  int n = 9;
  NODE *listhead;
  NODE *item;

  //initialize list
  listhead = NULL;
  for (k = 0; k < n; k++) {
    item = malloc (sizeof (NODE));
    item->data = array[n-1-k];
    item->link = listhead;    //append to head
    listhead = item;
  }
  //print list
  item = listhead;
  while (item) {
    printf ("%d  ", item->data);
    item = item->link;
  }
  printf ("\n");

  insertion4 (&listhead);

  item = listhead;
  while (item) {
    printf ("%d  ", item->data);
    item = item->link;
  }
  printf ("\n");

  return 0;
}

void
insertion4 (
  NODE **head  //listhead changed when return      
  )
{
  NODE *prev;

  prev = *head;

  while (prev->link) {
    //prev->link->data: key
    NODE *tmp, *ptmp;
    
    printf ("prev->link = %d\n", prev->link->data);
    //compare with head
    if (prev->link->data < (*head)->data) {
      //insert to head
      tmp = prev->link->link;
      prev->link->link = (*head);
      *head = prev->link;
      prev->link = tmp; //update to next, and break the tie 
      continue;
    }

    tmp = *head;
    ptmp = NULL;
    while (tmp != prev->link &&
           prev->link->data > tmp->data) {
      ptmp = tmp;
      tmp = tmp->link;
    }

    if (tmp != prev->link) {
      //insert key, update link
//      printf ("tmp = %d\n", tmp->data);
//      printf ("ptmp = %d\n", ptmp->data);
//      printf ("prev = %d\n", prev->data);
//      printf ("prev->link = %d\n", prev->link->data);
      ptmp->link = prev->link;
//      printf ("(1) done\n");
      prev->link = (prev->link)->link;  //break the tie
//      printf ("(2) done\n");
      ptmp->link->link = tmp;         //insert between ptmp and tmp
//      printf ("(3) done\n");
//      printf ("(updated)prev->link = %d\n", prev->link->data);
    } else {
      prev = prev->link;
    }
  }
}

