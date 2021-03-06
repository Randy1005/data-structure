#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*needs to pass at least second element to 2D array as fucntion parameter*/

typedef struct {
	int x;
	int y;
}Point;

void printSol(int M,int N,char sol[][N])
{
	int i,j;
	for(i=0;i<M;i++)
	{	
		for(j=0;j<N;j++)
			printf("%c",sol[i][j]);
		printf("\n");
	}
}

/*function to check border*/
bool isSafe(int i,int j,int M,int N)
{
	if(i >= 0 && i < M && j >= 0 && j < N)
		return true;
	else
		return false;
}


bool visit(int M,int N,char maze[][N],int i,int j)
{
	if(isSafe(i,j,M,N)) //check border
	{
		if(maze[i][j] == 'd') //reaches destination
			return true;

		else if(maze[i][j] == 's' || maze[i][j] == '0') //a valid path
		{
			maze[i][j] = '*'; //mark the path

			if(visit(M,N,maze,i-1,j) || visit(M,N,maze,i+1,j) || visit(M,N,maze,i,j-1) || visit(M,N,maze,i,j+1) || visit(M,N,maze,i-1,j+1) || visit(M,N,maze,i-1,j-1) || visit(M,N,maze,i+1,j+1) || visit(M,N,maze,i+1,j-1) == true)
				return true; //try 8 directions

			else //if not valid
			{
				maze[i][j] = '0'; //unmark
				return false;
			}
		}

		else //encounters wall '1'
			return false;
	}
	
}




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
		if(temp != '\n')
		{
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

	/*Here we start solving the maze*/

	/*first get the starting position*/
	Point startPt;
	for(i=0;i<M;i++)
		for(j=0;j<N;j++)
		{
			if(maze[i][j] == 's')
			{
				startPt.x = i;
				startPt.y = j;
			}
		}

	int steps = 0; //total steps
	/*set up initial postion and start solving the maze*/

	ofp = fopen("out.txt","w");
	if(visit(M,N,maze,startPt.x,startPt.y))
	{
		/*changed 's' to '*' in visit accidentally, change back to 's'*/
		maze[startPt.x][startPt.y] = 's';

		/*count steps*/

		for(i=0;i<M;i++)
			for(j=0;j<N;j++)
				if(maze[i][j] == '*' || maze[i][j] == 'd')
					steps++;

		for(i=0;i<M;i++)
		{
			for(j=0;j<N;j++)
				fprintf(ofp,"%c",maze[i][j]);
			fprintf(ofp,"\n");
		}
		fprintf(ofp,"%d steps\n",steps);
	}
	else //no solution
		fprintf(ofp,"No route\n");
}
