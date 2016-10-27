#include <stdio.h>
#include <stdlib.h>

int value(int n, int a, int b, int i, int j, int e[]);

int main()
{
	char inputFile[30];
	int lowerBand;
	int upperBand;
	printf("Please input the file name: ");
	scanf("%s",inputFile);
	printf("a: ");
	scanf("%d",&lowerBand);
	printf("b: ");
	scanf("%d",&upperBand);
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
	int element_of_e = matrixDim; //initialize num of elements of e_array to dimension of matrix
	int temp = matrixDim; //a temp variable for adding
	int a = lowerBand;

	/*add up lowerBand first*/
	while(a > 1)
	{
		element_of_e += (temp-1);
		temp--;
		a--;
	}

	/*then add up upperBand*/
	int temp2 = matrixDim;
	int b = upperBand;
	while(b > 1)
	{
		element_of_e += (temp2-1);
		temp2--;
		b--;
	}

	printf("%d\n",element_of_e);
	
	
}

/*
int value(int n, int a, int b, int i, int j, int e[])
{
	return matrix[i][j];	
}
*/
