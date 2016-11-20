#include <stdio.h>
#include <stdlib.h>

#define MAXROW 100
#define MAXCOL 100

/*smat node*/
typedef struct smat_node
{
	struct node *to_rHead;
	int total_row;
	int total_col;
	struct node *to_cHead;
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
	int row_index;
	smatNode *smat;
	rHeadNode *rHead[MAXROW];
	cHeadNode *cHead[MAXCOL];
	struct node *nd;
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

	
}


int main()
{


	
}


