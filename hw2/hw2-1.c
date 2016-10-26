#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Please input the file name: ");
	char inputFile[30];
	scanf("%s",inputFile);
	//printf("%s",inputFile);
	
	FILE *ifp = fopen(inputFile,"r");
	int matrixDim;
	int matrix[matrixDim][matrixDim];
	int i,j=0;
	while(!feof(ifp))
	{
		fscanf(ifp,"%d\n",&matrixDim);
		for(i=0;i<matrixDim;i++)
		{
			for(j=0;j<matrixDim;j++)
				fscanf(ifp,"%d ",&matrix[i][j]); 
		}
	}

	for(i=0;i<matrixDim;i++)
		for(i=0;i<matrixDim;i++)
			printf("%d ",matrix[i][j]);





}
