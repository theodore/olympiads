#include<stdio.h>
#define NMAX 6002


short int seq[NMAX]; // The sequence of integers
short int t[NMAX][NMAX]; // The Young Tableaux
int answer;
int i,j,k;
int n;

inline int  min (const int a, const int b)
{
  if( a < b ) return a;
  return b;
}

int insert_tableaux(const int row, const int col, const int val)
{
  i = min ( col , t[row][0]+1) ; /* In case insertion is tried at a position
				    further away than the beginning of the row */
  
  while ( t[row][i-1] > val && (i>1) )    i--; // Finding the right place to insert

  if (t[row][i] == 0 ) // Insert at the end of the row, if it is the case
    {
      t[row][i] = val;  
      t[row][0]++; 
      return 0;
    }

 // Insert where appropriate and continue to the lower row

 j = t[row][i];
 t[row][i] = val;
 insert_tableaux( row + 1, i, j);
  return 0; 
}


int main()
{

  // Reading Input data

  scanf("%d\n",&n);
  for(i = 1 ; i <= n ; i++ )
    scanf("%d",&seq[i]);

  //Initialization of the Tableaux

  t[0][0] = 1;
  t[0][1] = seq[1];

  //Insertion of subsequent elements

  for(k = 2; k <= n ; k++ )
    insert_tableaux(0 , t[0][0] + 1 , seq[k]);

  //Write computed numbers

  answer = 0;
  i = 0; 
  while(t[i][0] != 0 )
    {
      answer += t[i][0];
      printf("%d\n",answer);
      i++;
    }

#ifdef DB
  for (int i = 0; t[i][0]; ++i)
  {
      for (int j = 0; t[i][j]; ++j)
	  fprintf(stderr, "%d ", t[i][j]);
      fprintf(stderr, "\n");
  }
#endif
  /*
  Checking if the tableaux is generated correctly
  i = 0 ;
  freopen("tableaux","wt",stdout);
  while (t[i][0] != 0 )
    {
      for( j = 1 ; j <= t[i][0]; j++)
	printf("%d ",t[i][j]);
      printf("\n");
      i++;
    }
  fclose(stdout);  

  */
  return 0;
}
// vim:ts=8
