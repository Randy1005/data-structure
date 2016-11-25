#include <stdio.h>
#include <stdlib.h>

#define MAXROW 1000
#define MAXCOL 1000


/*smat node*/
typedef struct smat_node
{
	struct row_head_node *first_rHead;
	int total_row;
	int total_col;
	struct col_head_node *first_cHead;
}smatNode;

/*column head node*/
typedef struct col_head_node
{
	struct element_node *down;
	int col_index;
	struct col_head_node *next_cHead;
}cHeadNode;

/*row head node*/
typedef struct row_head_node
{
	struct row_head_node *next_rHead;
	int row_index;
	struct element_node *right;

}rHeadNode;

/*element node*/
typedef struct element_node
{
	int row_index;
	int col_index;
	int value;
	struct element_node *down;
	struct element_node *right;
}elementNode;

/*sparse matrix structure*/
typedef struct sparse_matrix
{
	int maxRow;
	int maxCol;
	int *sp;
	int num_of_element;
	smatNode *smat;
	rHeadNode *rHead[MAXROW];
	cHeadNode *cHead[MAXCOL];
	elementNode *elementNd;
}sparse;

/*initialize sparse matrix structure*/
void initSparse(sparse *spar,int spRow, int spCol)
{
	int i;
	//scanf("%d\n",&(spar -> maxRow));
	//scanf("%d\n",&(spar -> maxCol));
	spar -> maxRow = spRow;
	spar -> maxCol = spCol;
	/*create row headNodes*/
	for(i=0;i < spar -> maxRow;i++)
		spar -> rHead[i] = malloc(sizeof(rHeadNode));
	/*initialize and link row headNodes*/
	for(i=0;i < spar -> maxRow-1;i++)
	{
		//link one by one to the next rHeadNode
		spar -> rHead[i] -> next_rHead = spar -> rHead[i+1]; 
		//no elements yet, "right" points to NULL
		spar -> rHead[i] -> right = NULL;
		spar -> rHead[i] -> row_index = i;
	}

	/*the bottom row head node shall point to NULL*/
	// i = maxRow here
	spar -> rHead[i] -> right = NULL;
	spar -> rHead[i] -> next_rHead = NULL;

	/*---------same for col headNodes---------*/

	/*create col headNodes*/
	for(i=0;i < spar -> maxCol;i++)
		spar -> cHead[i] = malloc(sizeof(cHeadNode));
	/*initialize and link col headNodes*/
	for(i=0;i < spar -> maxCol-1;i++)
	{
		spar -> cHead[i] -> next_cHead = spar -> cHead[i+1];
		spar -> cHead[i] -> down = NULL;
		spar -> cHead[i] -> col_index = i;
	}

	//i = maxCol here
	spar -> cHead[i] -> down = NULL;
	spar -> cHead[i] -> next_cHead = NULL;

	/*create and initialize special headNodes*/
	spar -> smat = malloc(sizeof(smatNode));
	/*link smatNode to first rHead and cHead*/
	spar -> smat -> first_rHead = spar -> rHead[0];
	spar -> smat -> first_cHead = spar -> cHead[0];
	/*store num of rows and cols*/
	spar -> smat -> total_row = spar -> maxRow;
	spar -> smat -> total_col = spar -> maxCol;	
}

/*read in elements and create mateix of size maxRow * maxCol*/
void createArray(sparse *spar)
{
	int i,temp;
	spar -> sp = malloc((spar -> maxRow)*(spar -> maxCol)*sizeof(int));

	/*read in  elements and store*/
	for(i=0;i < (spar->maxRow)*(spar->maxCol);i++)
	{
		scanf("%d",&temp);
		*(spar -> sp + i) = temp;
	}
}

/*prints out the matrix*/
void display(sparse *spar)
{
	int i;
	for(i=0;i < (spar->maxRow)*(spar->maxCol);i++)
	{
		if(i % (spar->maxCol) == 0)
			printf("\n");
		printf("%d ", *(spar->sp + i));
	}
	printf("\n");
}

/*counts the number of non-zero elements*/
int cntNonzero(sparse spar)
{
	int cnt = 0;
	int i;
	for(i=0;i < (spar.maxRow)*(spar.maxCol);i++)
	{
		if(*(spar.sp + i) != 0)
			cnt++;
	}
	return cnt;
}

/*creates an array of triplets, storing infos(row col and value) of each nonzero element*/
void createTriplet(sparse *spar,sparse s)
{
	int i;
	int r = 0;
	int c = -1;
	int tripletIndex = -1;
	spar -> num_of_element = cntNonzero(s);
	/*allocate memory for triplets*/
	spar -> sp = malloc(spar -> num_of_element*3*sizeof(int));
	for(i=0;i < (spar->maxRow)*(spar->maxCol);i++)
	{
		c++;
		/*store row and col for each element*/
		if((i % (spar->maxCol)) == 0 && (i!=0))
		{
			r++; //row
			c = 0; //col value set back to 0
		}

		/*check for nonzero elements.Row, col, value assigned to triplets*/
		if(*(s.sp + i) != 0)
		{
			tripletIndex++; *(spar -> sp + tripletIndex) = r;//triplet index = 0, storing "row"

			tripletIndex++; *(spar -> sp + tripletIndex) = c;//triplet index = 1, storing "col"

			tripletIndex++; *(spar -> sp + tripletIndex) = *(s.sp + i);//triplet index = 2, storing "value"
		}
	}
}

/*insert element to list*/
void insert(sparse *spar,smatNode *smat,int r,int c,int val)
{
	elementNode *previous,*temp;
	rHeadNode *rHead;
	cHeadNode *cHead;
	int i,j;

	/*allocate memory for element nodes*/
	spar -> elementNd = malloc(sizeof(elementNode));
	/*assign info needed to element node*/
	spar -> elementNd -> row_index = r;
	spar -> elementNd -> col_index = c;
	spar -> elementNd -> value = val;

	/*get first row headnode*/
	rHead = smat -> first_rHead;
	/*get proprer row headnode*/
	for(i=0;i<r;i++)
		rHead = rHead -> next_rHead;

	temp = rHead -> right;

	/*if no element is added in a row, that is, rowHeadNode points to NULL*/
	if(temp == NULL)
	{
		/*then we add element node to the row headnode*/
		rHead -> right = spar -> elementNd;
		spar -> elementNd -> right = NULL;
	}

	/*row headnode already linked to one or more element nodes*/
	else
	{
		/*add element in proper position*/

		/*-----caution-----*/
		//inserting nodes requires:
		//1.previous node  ('previous')
		//2.previous -> next node ('temp')
		//keep pushing 'temp to the right until we find the position we want to insert the element node
		/*-----------------*/

		while(temp != NULL && temp -> col_index < c)
		{
			//push to the right until we find proper position to insert
			previous = temp;
			temp = temp -> right;
		}
		//after finding position, insert element node
		previous -> right = spar -> elementNd;
		spar -> elementNd -> right = NULL;
	}

	/*link proper col headnode with the elementnode*/
	cHead = spar -> smat -> first_cHead;
	for(j=0;j<c;j++)
		cHead = cHead -> next_cHead;

	temp = cHead -> down;

	/*same insert method as row headnode*/
	if(temp == NULL) 
	{
		cHead -> down = spar -> elementNd;
		spar -> elementNd -> down = NULL;
	}
	else
	{
		while((temp != NULL) && (temp -> row_index < r))
		{
			previous = temp;
			temp = temp -> down;
		}

		previous -> down = spar -> elementNd;
		spar -> elementNd -> down = NULL;
	}

}

/*store info of triplets in a linked list form(also inserts element nodes)*/
void createList(sparse *spar)
{
	int j=0,i; //j+=3: triplets come in 3 (0,1,2)->(3,4,5)->.......
	for(i=0;i < spar -> num_of_element;i++,j+=3)
		insert(spar, spar -> smat, *(spar -> sp + j), *(spar -> sp + j+1), *(spar -> sp + j+2));		
}

void showList(sparse *spar)
{
	elementNode *temp;
	/*get first row headnode*/
	int r = spar -> smat -> total_row;
	int i,j=0;

	printf("\n");
	for(i=0;i<r;i++)
	{
		temp = spar -> rHead[i] -> right;
		if(temp != NULL)
		{
			while(temp -> right != NULL)
			{
				printf("Row:%d Col:%d Val:%d\n",temp -> row_index,temp -> col_index,temp -> value);
				temp = temp -> right;	
			}
			if(temp -> row_index == i)
				printf("Row:%d Col:%d Val:%d\n",temp -> row_index,temp -> col_index,temp -> value);
		}

	}

}

//it's basically "createList" function, but I switched row and column when inserting element nodes (transpose)
void transpose(sparse *spar,sparse *trans)
{
	int i,j=0;
	//j+=3: triplets come in 3 (0,1,2)->(3,4,5)->.......
	for(i=0;i < spar -> num_of_element;i++,j+=3)
		insert(trans, trans -> smat, *(spar -> sp + j+1), *(spar -> sp + j), *(spar -> sp + j+2));

}

void printResult(sparse *spar)
{
	int i,j = 0;
	/*for printing result*/
	int result[spar -> maxRow][spar -> maxCol];

	/*initialize array*/
	for(i=0;i<spar->maxRow;i++)
		for(j=0;j<spar->maxCol;j++)
			result[i][j] = 0;

	/*visit the nodes to get nonzero elements*/
	elementNode *temp;
	/*get first row headnode*/
	int r = spar -> smat -> total_row;

	for(i=0;i<r;i++)
	{
		temp = spar -> rHead[i] -> right;
		if(temp != NULL)
		{
			while(temp -> right != NULL)
			{
				result[temp -> row_index][temp -> col_index] = temp -> value;	
				temp = temp -> right;	
			}
			if(temp -> row_index == i)	
				result[temp -> row_index][temp -> col_index] = temp -> value;	
		}
	}

	printf("\n");
	/*print out result*/
	for(i=0;i<spar -> maxRow;i++)
	{
		for(j=0;j<spar -> maxCol;j++)
			printf("%d ",result[i][j]);
		printf("\n");
	}

}

void multiply(sparse *s1,sparse *s2,sparse *result)
{
	int sum = 0;
	int i,j;
	/*visit the nodes to get nonzero elements*/
	elementNode *temp1, *temp2;
	int r = s1 -> smat -> total_row;
	int c = s2 -> smat -> total_col; 

	//visit through rows and cols, if row = col, multiply and sum up
	for(i=0;i<r;i++)
	{
		temp1 = s1 -> rHead[i] -> right;
		if(temp1 != NULL) //if row has value
		{
			for(j=0;j<c;j++)
			{
				while(temp1 != NULL)
				{		
					temp2 = s2 -> cHead[j] -> down;
					while(temp2 != NULL) //if col has value
					{
						if((temp1 -> row_index) == (temp2 -> col_index))
						{
							sum += (temp1 -> value)*(temp2 -> value);
							if(sum != 0)
							{	
								insert(result,result -> smat,i,j,sum);
								sum = 0;
							}
						}	
						temp2 = temp2 -> down; //ptr shift down
					}
					temp1 = temp1 -> right;//ptr shift right
				}
				/*
				if(sum != 0)
				{
					insert(result,result -> smat,i,j,sum);
				}
				*/
			}
				
		}
	}

}

int main()
{
	int inputRow,inputRow2;
	int inputCol,inputCol2;

	sparse s1,infoS1,s2,infoS2;
	sparse result,infoRE;

	scanf("%d",&inputRow);
	scanf("%d",&inputCol);

	/*first sparse matrix*/
	initSparse(&s1,inputRow,inputCol);
	initSparse(&infoS1,inputRow,inputCol);
	createArray(&s1);
	createTriplet(&infoS1,s1);
	createList(&infoS1);


	scanf("%d",&inputRow2);
	scanf("%d",&inputCol2);

	/*second sparse matrix*/
	initSparse(&s2,inputRow2,inputCol2);
	initSparse(&infoS2,inputRow2,inputCol2);
	createArray(&s2);
	createTriplet(&infoS2,s2);
	createList(&infoS2);

	/*result matrix*/
	initSparse(&result,inputRow,inputCol2);
	initSparse(&infoRE,inputRow,inputCol2);
	//multiply(&infoS1,&infoS2,&result);   problems here

	printResult(&result);
	
}


