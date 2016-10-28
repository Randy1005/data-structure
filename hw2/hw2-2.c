#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	/*random seed*/
	srand(time(NULL));

	int row,col;
	int ini_X,ini_Y;
	int MAX_SQUARE = 50000;
	
	printf("THIS A \"RANDOM WALK\" PROGRAM,PLEASE ENTER THE LENGTH OF ROW(N) AND COLUMN(M),AND THE INITIAL POSITION YOU WISH TO START AT\nRANGE: 2<N<=40 , 2<M<=20\n");
	printf("N: ");
	scanf("%d",&row);
	printf("M: ");
	scanf("%d",&col);

	/*restrict N and M requirements*/
	while(row <= 2 || row > 40 || col <= 2 || col > 20)
	{
		printf("OUT OF RANGE, ENTER AGAIN\n");
		printf("N: ");
		scanf("%d",&row);
		printf("M: ");
		scanf("%d",&col);
	}
	
	printf("Initial bug position X: ");
	scanf("%d",&ini_X);
	printf("Initial bug position Y: ");
	scanf("%d",&ini_Y);

	int imove[8] = {-1,0,1,1,1,0,-1,-1};
	int jmove[8] = {1,1,1,0,-1,-1,-1,0};
	
	/*create a count board to memorize how many times the bug touched each tile*/
	int count[row][col];
	/*initialize array*/
	int i,j;
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			count[i][j] = 0;

	/*start random walk*/
	
	/*set up initial position*/
	int ibug = ini_X;
	int jbug = ini_Y;
	
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			while(count[i][j]==0)
			{
				/*generate random num k;*/
				int k = rand()%8;
				//printf("k = %d\n",k);
				/*check if the bug is out of border*/
				while(ibug+imove[k] > (row-1) || ibug+imove[k] < 0 || jbug+jmove[k] > (col-1) || jbug+jmove[k] < 0)
				{
					k = rand()%8;
				}
					
				ibug += imove[k];
				jbug += jmove[k];
				count[ibug][jbug]++;

			}
		}
	}

	/*print count array and calculate total steps*/
	int total_step = 0;	
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			total_step += count[i][j];
	
	/*write final result into a file: Sample_output.txt)*/
	FILE *ofp = fopen("result.txt","w");

	fprintf(ofp,"total steps = %d\n",total_step);

	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
			fprintf(ofp,"%d\t",count[i][j]);
		fprintf(ofp,"\n");
	}
	




}
