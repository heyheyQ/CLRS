/*
 * Problem 7-4 in CLRS:
 * Stack depth for quicksort.
 * The quicksort algorithm of Section 7.1 contains two recursive calls to itself.
 * After quicksort calls partition, it recursively sorts the left subarray 
 * and then it recursively sorts the right subarray.
 * The second recursive call in quicksort is not really necessary;
 * we can avoid it by using an iterative control structure.
 *
 * The program implements an iterative quicksort algorithm.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _NODE {
  int p;
  int s;
  struct _NODE *link;
} NODE;

bool
IsListEmpty (
  NODE *head      
  );

//push
void
AddToHead (
  NODE **head,
  NODE *item
  );

//pop
NODE *
RemoveFromHead (
  NODE **head      
  );

//return the index of the median
int
median (
  int *A,
  int p,
  int s,
  int mid
  );

int
partition (
  int *A,
  int p,
  int q
  );

void
swap (
  int *s1,
  int *s2
  );

void
iquick (
  int *A,
  int n
  );

//example inputs
//int array[] = {12, 2, 16, 30, 8, 28, 4, 10, 20, 6, 18};
//int n = 11;

int array[] = {9, 8, 7, 6, 5, 5, 4, 3, 2, 1};
int n = 10;

int
main (void)
{
  int k;

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);    
  }
  printf ("\n");

  iquick (array, n);

  for (k = 0; k < n; k++) {
    printf ("%d  ", array[k]);    
  }
  printf ("\n");

  return 0;
}

bool
IsListEmpty (
  NODE *head      
  )
{
  if (head == NULL) {
    return true;
  }
  return false;
}

//push
void
AddToHead (
  NODE **head,
  NODE *item
  )
{
  item->link = (*head);
  *head = item;
}

//pop
NODE *
RemoveFromHead (
  NODE **head      
  )
{
  NODE *tmp;

  if (!(*head)) {
    return NULL;
  }

  tmp = *head;
  *head = (*head)->link;

  return tmp;
}

int
median (
  int *A,
  int p,
  int s,
  int mid
  )
{
  if (A[p] < A[s]) {
    if (A[mid] < A[p]) {
      //A[mid] < A[p] < A[s]
      return p;
    } else if (A[mid] < A[s]) {
      //A[p] < A[mid] < A[s]
      return mid;
    } else {
      //A[p] < A[s] <= A[mid]
      return s;
    }
  } else {
    if (A[mid] < A[s]) {
      //A[mid] < A[s] <= A[p]
      return s;
    } else if (A[mid] < A[p]){
      //A[s] < A[mid] <= A[p]
      return mid;
    } else {
      //A[s] <= A[p] <= A[mid]
      return p;
    }
  }        
}

int
partition (
  int *A,
  int p,
  int q
  )
{
  //range: A[p]~A[q]
  //return: pivot r
  int i, j;
  int pivot;
  int temp;  //for swap

  pivot = A[p];  //first element
  i = p;
  for (j = p+1; j <= q; j++) {
    if (A[j] <= pivot) {
      //swap A[i+1] and A[p]
      i = i + 1;
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }
  //swap A[p] and A[i]
  A[p] = A[i];
  A[i] = pivot;

  return i;
}

void
swap (
  int *s1,
  int *s2
  )
{
  int temp;

  temp = *s1;
  *s1 = *s2;
  *s2 = temp;
}

void
iquick (
  int *A,
  int n
  )
{
  int p, s, mid, pivot, r;
  NODE *listhead = NULL;
  NODE *item;
  int k;  //for debug

  p = 0;
  s = n-1;

  while (s > p || !IsListEmpty (listhead)) {
    if (s <= p) {
      item = RemoveFromHead (&listhead);    
      p = item->p;
      s = item->s;
      printf ("pop: p = %d, s = %d\n", p, s);
      free (item);
    } 

    mid = (p+s)/2;
    pivot = median (A, p, mid, s);
    swap (&A[p], &A[pivot]);
    r = partition (A, p, s);
    //for debug
    printf ("A[r] = %d\n", A[r]);
    for (k = p; k <= s; k++) {
      printf ("%d  ", A[k]);    
    }
    printf ("\n");

    if (r+1 < s) {
      //push right part indices    
      item = malloc (sizeof (NODE));
      item->p = r+1;
      item->s = s;
      item->link = NULL;
      printf ("push: p = %d, s = %d\n", item->p, item->s);
      AddToHead (&listhead, item);
      //for debug
      item = listhead;
      printf ("list:\n");
      while (item) {
        printf ("(p,s) = (%d,%d)\n", item->p, item->s);
        item = item->link;
      }
      printf ("\n");
    }
    //iterate on the left part
    p = p;
    s = r-1;

    printf ("next: p = %d, s = %d\n", p, s);
  }
}


