#include <stdio.h>
#include <stdlib.h>

#define MAXROW 100
#define MAXCOL 100

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
	struct node *down;
	int col_index;
	struct col_head_node *next_cHead;
}cHeadNode;

/*row head node*/
typedef struct row_head_node
{
	struct row_head_node *next_rHead;
	int row_index;
	struct node *right;

}rHeadNode;

/*element node*/
typedef struct element_node
{
	int row_index;
	int col_index;
	int value;
	struct node *down;
	struct node *right;
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
void initSparse(sparse *spar)
{
	int i;
	scanf("%d\n",&(spar -> maxRow));
	scanf("%d\n",&(spar -> maxCol));
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
	int element,i,temp;
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
		printf("%d\t", *(spar->sp + i));
	}
}

/*counts the number of non-zero elements*/
int cntNonzero(sparse *spar)
{
	int cnt = 0;
	int i;
	for(i=0;i < (spar->maxRow)*(spar->maxCol);i++)
	{
		if(*(spar->sp + i) != 0)
			cnt++;
	}
	return cnt;
}

/*creates an array of triplets, storing infos(row col and value) of each nonzero element*/
void createInfo(sparse *spar,sparse s)
{
	int i;
	int r = 0;
	int c = -1;
	int tripletIndex = -1;
	spar -> num_of_element = cntNonzero(spar);
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
	elementNode *temp1,*temp2;
	rHeadNode *rHead;
	cHeadNode *cHead;
	int i,j;
	
	/*allocate memory for element nodes*/
	spar -> elementNd = malloc(sizeof(elementnode));
	/*assign info needed to element node*/
	spar -> elementNd -> row_index = r;
	spar -> elementNd -> col_index = c;
	spar -> elementNd -> value = val;

	/*get first row headnode*/
	rHead = smat -> first_rHead;
	/*get proprer row headnode*/
	for(i=0;i<r;i++)
		rHead = rHead -> next_rHead;
	
	temp1 = rHead -> right;
	
	/*if no element is added in a row, that is, rowHeadNode points to NULL*/
	if(temp1 == NULL)
	{
		/*then we add element node to the row headnode*/
		rHead -> right = spar -> elementNd;
		spar -> elementNd -> right = NULL;
	}

	 /*row headnode already linked to one or more element nodes*/
	else
	{
		/*add element in proper position*/
		while(temp1 != NULL && temp1 -> col < c)
		{
			//temp2 = temp1;
			//temp1 = temp1 -> right;
		}

	}



}





int main()
{
	

	
}


