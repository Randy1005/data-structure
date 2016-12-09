#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#define LCHILD(x) 2*x + 1
#define RCHILD(x) 2*x + 2
#define PARENT(x) (x-1)/2

typedef struct Node{
	int data;
}node;

typedef struct MaxHeap{
	int size;
	node *element;
}maxHeap;

//initialize members of the max heap with default values
maxHeap initMaxHeap(){
	maxHeap mheap;
	mheap.size = 0;
	return mheap;
}

void push(maxHeap *mheap, int value){
	//first allocate space
	if(mheap -> size != 0){
		//if already allocated before
		mheap -> element = (node *)realloc(mheap -> element, ((mheap -> size) + 1)*sizeof(node));
	}
	else
		mheap -> element = (node *)malloc(sizeof(node));
		
	//initialize node with value
	node nd;
	nd.data = value;
	
	//positioning node at the right position
	int i = (mheap -> size)++;
	while(i && nd.data > mheap -> element[PARENT(i)].data){
		mheap -> element[i] = mheap -> element[PARENT(i)];
		i = PARENT(i);
	}
	mheap -> element[i] = nd;
}

void swap(node *n1, node *n2){
	node temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}


int totalElem()
{
	FILE *ifp = fopen("in.txt","r");
	char temp;
	int total = 0;
	while(!feof(ifp))
	{
		if((temp = fgetc(ifp)) == ',')
			total++;
	}
	return (total+1);
}

void readIn(int Arr[]){
	ifstream input("in.txt",ios::in);
	for(int i=0;i<totalElem();i++)
	{
		input >> Arr[i];
		input.ignore(1,',');
	}
	input.close();
	
}


int main(void)
{
	maxHeap mheap = initMaxHeap();
	int mheapArr[totalElem()];
	
	readIn(mheapArr);
	for(int i=0;i<totalElem();i++)
		cout<<mheapArr[i]<<endl;

}




