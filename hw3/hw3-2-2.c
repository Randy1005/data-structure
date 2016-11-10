#include <stdio.h>
#include <stdbool.h>

#define MAX 4

/*declare array for queue and rear, front index*/
int queueArray[MAX] = {};
int hasValue[MAX] = {}; 
int rear = 0;
int front = 0;

void insert();
void delete();
bool queueFull();
bool queueEmpty();
void printQueue();

int main()
{
	int choice;
	while(1)
	{
		printf("insert(1) delete(2): ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				insert();
				break;
			case 2:
				delete();
				break;
			default:
				break;

		}
	}


}

void insert()
{
	int i;
	/*circular queue full condition*/
	if((rear == MAX - 1 && front == 0) || (front == rear + 1))
	{
		printf("Queue is full\n");
		return;
	}
	if(rear == MAX -1)
		rear = -1;

	int add_element;
	printf("Insert number: ");
	scanf("%d",&add_element);
	queueArray[rear+1] = add_element;
	rear++; //every time I push an element rear increments
	hasValue[rear] = 1; //to decide whether to print out number or not, cuz queue is initialized as 0s

	printQueue();

}

void delete()
{	
	/*circular queue empty: no need to reset front,rear back to 0*/
	if(front == rear)
	{
		printf("Queue is empty\n");
		return;
	}

	else
	{
		printf("deleted element: %d\n",queueArray[front + 1]); //pop element from front
		hasValue[front + 1] = 0; //set back to 0, position empty
		front++;
	}
	
	printQueue();

}

void printQueue()
{
	int i;
	printf("Front = %d Rear = %d\n",front,rear);
	printf("Queue: ");
	for(i=0;i<MAX;i++)
	{
		printf("[");

		if(hasValue[i])
			printf("%d",queueArray[i]);

		printf("]");
	}
	printf("\n");
	printf("\n");
}
