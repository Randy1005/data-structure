#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
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

//various types of traversal

void levelOrderTrav(maxHeap *mheap){
	int n = 0;
	int cnt = 0;
	cout << "Max Heap:" << endl;
	for(int i=0; i<mheap->size ; i++){
		cout << mheap->element[i].data << " ";

		if(i == n){
			cout << endl;
			cnt++;
			n+=pow(2,cnt);
		}
	}
	cout << endl;	
}

void postOrderTrav(maxHeap *mheap,int i){
	printf("%d ",mheap->element[i].data);
	if(LCHILD(i) < mheap->size)
		postOrderTrav(mheap,LCHILD(i));
	if(RCHILD(i) < mheap->size)
		postOrderTrav(mheap,RCHILD(i));

}

void inOrderTrav(maxHeap *mheap, int i) {
	if(LCHILD(i) < mheap->size) {
		inOrderTrav(mheap,LCHILD(i));
	}

	printf("%d ", mheap->element[i].data);
	
	if(RCHILD(i) < mheap->size) {
		inOrderTrav(mheap,RCHILD(i));
	}
}
void changePriority(int mheapArr[],maxHeap *mheap){
	int choicePrior;
	int changeTo;
	cout << "Choice priority: ";
	cin >> choicePrior;
	cout << "Change priority to: ";
	cin >> changeTo;

	//traverse mheapArr and change numbers
	for(int i=0;i<totalElem();i++)
	{
		if(mheapArr[i] == choicePrior)
			mheapArr[i] = changeTo;
	}
	
}

int main(void)
{
	int mheapArr[totalElem()];
	readIn(mheapArr);
	
	while(1)
	{
		maxHeap mheap = initMaxHeap();
		for(int i=0;i<totalElem();i++)
			push(&mheap,mheapArr[i]);
		levelOrderTrav(&mheap);
		cout << "Change Priority? (Y/N):";
		char yesOrno;
		cin >> yesOrno;
		switch(yesOrno){
			case 'Y':
				changePriority(mheapArr,&mheap);
				break;
			case 'N':
				exit(1);
			default:
				cout<<"Error"<<endl;
				break;
		}
		
	}

}




