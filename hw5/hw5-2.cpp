#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <time.h>
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

//after deleting node, it violated maxheap properties so reheapify
void reheapify(maxHeap *mheap,int i){
	int maxElement;
	if(LCHILD(i) < mheap -> size && mheap -> element[LCHILD(i)].data > mheap -> element[i].data)
		maxElement = LCHILD(i);
	else
		maxElement = i; //parent

	if(RCHILD(i) < mheap -> size && mheap->element[RCHILD(i)].data > mheap->element[maxElement].data)
		maxElement = RCHILD(i);
	
	if(maxElement != i)//parent is not the largest
	{
		swap(&(mheap -> element[i]), &(mheap -> element[maxElement]));
		reheapify(mheap,maxElement);
	}
}
	

void pop(maxHeap *mheap){
	int choiceDelete;
	cout << "Choice element:";
	cin >> choiceDelete;
	
	if(mheap -> size) //heap not empty
	{
		//find index of choiceDelete first
		for(int i=0;i<mheap -> size;i++)
		{
			if(mheap -> element[i].data == choiceDelete)
			{
				mheap -> element[i] = mheap -> element[--(mheap -> size)]; //choiceDelete switch with bottom node first
				reheapify(mheap,i);//then reheapify
				break;
			}
		}
	}
	else
	{
		cout << "heap empty!" << endl;
		free(mheap -> element);
	}

}

int main(void)
{
	int mheapArr[totalElem()];
	readIn(mheapArr);
	maxHeap mheap = initMaxHeap();
	for(int i=0;i<totalElem();i++)
		push(&mheap,mheapArr[i]);
	levelOrderTrav(&mheap);
	
	while(1)
	{
		clock_t begin = clock();
		cout << "Delete element? (Y/N):";
		char yesOrno;
		cin >> yesOrno;
		switch(yesOrno){
			case 'Y':
				pop(&mheap);
				break;
			case 'N':
				exit(1);
			default:
				cout<<"Error"<<endl;
				break;
		}
		clock_t end = clock();
		double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
		levelOrderTrav(&mheap);
		cout << "Spend time:" << timeSpent << " sec" << endl;
		cout << endl;
	}

}




