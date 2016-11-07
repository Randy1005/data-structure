#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	FILE *ifp;
	FILE *ofp;
	ifp = fopen("in.txt","r");

	/*to get M and N*/
	int M = 0;
	int N = 0;

	char temp;
	/*get N*/
	while(!feof(ifp))
	{
		if((temp = fgetc(ifp)) == '\n')
		{
			N--;
			break;
		}
		else
			N++;
	}

	/*get M*/
	while(!feof(ifp))
	{
		if((temp = fgetc(ifp)) == '\n')
			M++;

		else if((temp = fgetc(ifp)) == EOF)
		{
			M++;
		}
		else
			;

	}


	/*create maze array*/
	char maze[M][N];
	int i,j;

	/*initialize maze array*/
	
	for(i=0;i<M;i++)
		for(j=0;j<N;j++)
			maze[i][j] = '0';

	/*It won't stop emitting EOF signal, I have to close file and open again*/
	fclose(ifp);
	ifp = fopen("in.txt","r");


	/*read in the maze*/
	//printf("M:%d N:%d\n",M,N);
	i = 0;
	j = 0;
	while((temp = fgetc(ifp)) != EOF)
	{
		if((temp = fgetc(ifp)) != '\n')
		{
			printf("come on ");
			maze[i][j] = temp;
			j++;
		}
		else
		{
			i++;
			j = 0;
		}				
	}
	fclose(ifp);
	
	
	/*
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
			printf("%c",maze[i][j]);
		printf("\n");
	}
	*/
	
	
	
	



}
