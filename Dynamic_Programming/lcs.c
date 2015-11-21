/*
 * Chap.15 in CLRS:
 * Dynamic Programming
 *
 * The program implements a dynamic programming algorithm to solve the longest common subsequence problem.
 * For example, if X={A, B, C, B, D, A, B} and Y={B, D, C, A, B, A}, 
 * the sequence {B, C, A} is a common subsequence of both X and Y.
 * Given two sequences X = {x1, x2, ..., xm} and Y = {y1, y2, ..., yn},
 * we wish to find a maximum-length common subsequence of X and Y.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>   //memset

#define MAX(a, b) ((a) > (b) ? (a) : (b))

char x[] = "ABCBDAB";
char y[] = "BDCABA";

int
Lcs (
  char *x,
  char *y
  );

int
Lcs_v2 (
  char *x,
  char *y
  );

//recursively reconstruct
void
StartFromHere (
  char *x,
  char *y,
  int  *c,
  char *b,
  int  row,
  int  col,      //dimension of c and b
  int  i,
  int  j,
  char *prefix,
  int  len       //initial len of prefix
  );

//for test
int
Lcs_v3 (
  char *x,
  char *y
  );

void
Print_Lcs (
  char *x,
  char *b,
  int row,
  int col,
  int i,
  int j
  );


int
main (void)
{

//  printf ("the length of LCS = %d\n", Lcs (x, y));
//  printf ("the length of LCS = %d\n", Lcs_v2 (x, y));
  printf ("the length of LCS = %d\n", Lcs_v3 (x, y));
  return 0;
}

//return c[row, col]
int
Lcs (
  char *x,
  char *y
  )
{
  int row, col;
  int *c;
  int i, j;

  row = strlen (y) + 1;    //0~strlen(y)
  col = strlen (x) + 1;    //0~strlen(x)
  printf ("row = %d, col = %d\n", row, col);

  c = malloc (sizeof (int) * row * col);
  memset (c, 0, sizeof (int) * row * col);

  //row-based to fill up
  for (j = 1; j < row; j++) {    //y[j]
    for (i = 1; i < col; i++) {  //x[i]
      //fill up c[j, i]
      if (x[i-1] == y[j-1]) {
        //c[j, i] = c[j-1, i-1] + 1
        c[col*j+i] = c[col*(j-1)+(i-1)] + 1;
      } else {
        //c[j, i] = max (c[j-1, i], c[j, i-1])
        c[col*j+i] = MAX(c[col*(j-1)+i], c[col*j+(i-1)]);
      }
    
    }
  }

  //for debug
  for (j = 0; j < row; j++) {
    for (i = 0; i < col; i++) {
      printf ("%d, ", c[col*j+i]);    
    }    
    printf ("\n");  
  }

  return c[col*(row-1)+(col-1)];
}

int
Lcs_v2 (
  char *x,
  char *y
  )
{
  int row, col;
  int *c;
  int i, j;
  char *table;    //row*col
  int size;
  char *prefix;

  row = strlen (y) + 1;    //0~strlen(y)
  col = strlen (x) + 1;    //0~strlen(x)
//  printf ("row = %d, col = %d\n", row, col);

  c = malloc (sizeof (int) * row * col);
  memset (c, 0, sizeof (int) * row * col);
  //to reconstruct the sol.
  table = malloc (sizeof (char) * row * col);
  memset (table, 0, sizeof (char) * row * col);

  //row-based to fill up
  for (j = 1; j < row; j++) {    //y[j]
    for (i = 1; i < col; i++) {  //x[i]
      //fill up c[j, i]
      if (x[i-1] == y[j-1]) {
        //c[j, i] = c[j-1, i-1] + 1
        c[col*j+i] = c[col*(j-1)+(i-1)] + 1;
        table[col*j+i] = 'd';      //diagonal    
      } else {
        //c[j, i] = max (c[j-1, i], c[j, i-1])
//        c[col*j+i] = MAX(c[col*(j-1)+i], c[col*j+(i-1)]);
        if (c[col*(j-1)+i] > c[col*j+(i-1)]) {
          c[col*j+i] = c[col*(j-1)+i];
          table[col*j+i] = 'n';    //north    
        } else if (c[col*(j-1)+i] < c[col*j+(i-1)]) {
          c[col*j+i] = c[col*j+(i-1)];
          table[col*j+i] = 'w';    //west    
        } else {
          //equal, n and w are both available    
          c[col*j+i] = c[col*(j-1)+i];
          table[col*j+i] = 'e';    //equal    
        }
      }
    
    }
  }

//  //for debug
//  for (j = 0; j < row; j++) {
//    for (i = 0; i < col; i++) {
//      printf ("%d, ", c[col*j+i]);    
//    }    
//    printf ("\n");  
//  }
//  for (j = 0; j < row; j++) {
//    for (i = 0; i < col; i++) {
//      printf ("%c, ", table[col*j+i]);    
//    }    
//    printf ("\n");  
//  }

  //test
  size = c[col*(row-1)+(col-1)];
  prefix = malloc (sizeof (char) * (size+1));
  memset (prefix, 0, sizeof (char) * (size+1));
  StartFromHere (x, y, c, table, row, col, row-1, col-1, prefix, 0);


//  return c[col*(row-1)+(col-1)];
  return size;

}

//recursively reconstruct
void
StartFromHere (
  char *x,
  char *y,
  int  *c,
  char *b,
  int  row,
  int  col,      //dimension of c and b
  int  i,
  int  j,
  char *prefix,
  int  len       //initial len of prefix
  )
{
  char tmp[2];
  int len2;
  int k;
  char w;
//  int olen;

  memset (tmp, 0, sizeof (char) * 2);
//  olen = len;    //from the upper level

  while (c[col*i+j] != 0) {
    w = b[col*i+j];  
    switch (w) {
      case 'd':
        tmp[0] = x[j-1];    //or y[i-1]
        len++;
        prefix = strcat (prefix, tmp);
        i--;
        j--;
        break;
      case 'n':
        i--;
        break;
      case 'w':
        j--;
        break;
      case 'e':
        StartFromHere (x, y, c, b, row, col, i-1, j, prefix, len);
        prefix[len] = '\0';   //restore the cat in lower level
        StartFromHere (x, y, c, b, row, col, i, j-1, prefix, len);
        return;
//        break;
        
    }    
  }    

  //print
  len2 = strlen (prefix);
  for (k = len2-1; k >= 0; k--) {
    printf ("%c", prefix[k]);    
  }
  printf ("\n");
}

//for test
int
Lcs_v3 (
  char *x,
  char *y
  )
{
  int row, col;
  int *c;
  int i, j;
  char *table;    //row*col
  int size;

  row = strlen (y) + 1;    //0~strlen(y)
  col = strlen (x) + 1;    //0~strlen(x)

  c = malloc (sizeof (int) * row * col);
  memset (c, 0, sizeof (int) * row * col);
  //to reconstruct the sol.
  table = malloc (sizeof (char) * row * col);
  memset (table, 0, sizeof (char) * row * col);

  //row-based to fill up
  for (j = 1; j < row; j++) {    //y[j]
    for (i = 1; i < col; i++) {  //x[i]
      //fill up c[j, i]
      if (x[i-1] == y[j-1]) {
        //c[j, i] = c[j-1, i-1] + 1
        c[col*j+i] = c[col*(j-1)+(i-1)] + 1;
        table[col*j+i] = 'd';      //diagonal    
      } else {
        if (c[col*(j-1)+i] >= c[col*j+(i-1)]) {
          c[col*j+i] = c[col*(j-1)+i];
          table[col*j+i] = 'n';    //north    
        } else {
          c[col*j+i] = c[col*j+(i-1)];
          table[col*j+i] = 'w';    //west    
        }
      }
    
    }
  }

  //test
  size = c[col*(row-1)+(col-1)];
  Print_Lcs (x, table, row, col, row-1, col-1);


//  return c[col*(row-1)+(col-1)];
  return size;
}

void
Print_Lcs (
  char *x,
  char *b,
  int row,
  int col,
  int i,
  int j
  )
{
  if (i == 0 || j == 0) {  
    return;    
  }        

  if (b[col*i+j] == 'd') {
    Print_Lcs (x, b, row, col, i-1, j-1);
    printf ("%c", x[j-1]);
  } else if (b[col*i+j] == 'n') {
    Print_Lcs (x, b, row, col, i-1, j);
  } else {
    Print_Lcs (x, b, row, col, i, j-1);
  }
        
}
