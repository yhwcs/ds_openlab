#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024
void readMatrix(Term a[]);
void printMatrix(Term a[]);
void fast_transport(Term* a, Term* b);
int main(void) 
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	freopen("A.txt", "r", stdin);
	readMatrix(a);
	fast_transport(a, c);
	printMatrix(c);
	return 0;
}
void readMatrix(Term a[]) 
{
	int n, m;
	scanf("%d%d", &n, &m);
	int p = 1;
	a[0].row = n; a[0].column = m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) 
		{
			int t;
			scanf("%d", &t);
			if (t == 0) continue;
			a[p].row = i;
			a[p].column = j;
			a[p++].value = t;
		}
	a[0].value = p - 1;
}
void printMatrix(Term a[]) 
{
	for (int i = 0; i <= a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
}
void fast_transport(Term* a, Term* b)
{
	int row_terms[MAX_TERMS];
	int starting_pos[MAX_TERMS]; 
	int i, j=1, num_cols = a[0].column, num_terms = a[0].value;
	b[0].row = num_cols; 
	b[0].column = a[0].row;
	b[0].value = num_terms;

	if (num_terms > 0) 
	{ /* nonzero matrix */
		for (i = 0; i < a[0].value; i++) {
			a[i].value = 0; //initialization
		}
		for (i = 0; i < num_cols; i++) 
			row_terms[i] = 0;
		for (i = 1; i <= num_terms; i++) 
			row_terms[a[i].column]++;
        int check=0;
        for(i=1; check<a[0].row+1; i++)
        {
            if(a[i].column==check)
            {
                b[j].row=a[i].column;
                b[j].column=a[i].row;
                b[j++].value=a[i].value;
                (row_terms[check])--;
            }
            if(row_terms[check]==0)
            {
                i=1;
                check++;
            }
        }
	}
}//end fast_transport
