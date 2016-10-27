#include <stdio.h>
#include <stdlib.h>

int value(int n, int a, int b, int i, int j, int e[]);

int main()
{
	printf("Please input the file name: ");
	char inputFile[30];
	scanf("%s",inputFile);
	//printf("%s",inputFile);
	
	FILE *ifp = fopen(inputFile,"r");
	int matrixDim = 0;
	int i,j = 0;
	int lineCnt = 1;

	/*get the first line, which is the matrixDimension*/
	
	while(!feof(ifp))
	{
		if(lineCnt == 1)
		{
			fscanf(ifp,"%d\n",&matrixDim);
			lineCnt++;
		}
		else
			break;	
	}

	/*DEBUG: matrixDim*/
	//printf("%d\n",matrixDim);
	
	/*create matrix*/
	int matrix[matrixDim][matrixDim];
	
	/*
	char buffer[100];
	fgets(buffer,100,ifp);
	printf("%s",buffer);
	*/
	
	while(!feof(ifp))
	{
		for(i=0;i<matrixDim;i++)
		{
			for(j=0;j<matrixDim;j++)
				fscanf(ifp,"%d",&matrix[i][j]);
		}
		/*
		if(feof(ifp))
			printf("END OF FILE\n");
		*/
	}
		
	/*DEBUG: matrix*/
	/*
	for(i=0;i<matrixDim;i++)
	{
		for(j=0;j<matrixDim;j++)
			printf("%d ",matrix[i][j]);
		printf("\n");
	}
	*/
	
	
}

int value(int n, int a, int b, int i, int j, int e[])
{

}
