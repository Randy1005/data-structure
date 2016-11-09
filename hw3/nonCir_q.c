#include <stdio.h>

#define MAX 4

/*declare array for queue and rear, front index*/
int queueArray[MAX] = {};
int hasValue[MAX] = {}; 
int rear = 0;
int front = 0;

void insert();
void delete();
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

		}
	}


}

void insert()
{
	if(rear == MAX -1)
	{
		printf("Queue is full\n");
		return;
	}

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
	if(front == rear)
	{
		front = 0;
		rear = 0;
		printf("Queue is empty\n");
		return;
	}

	else
	{
		printf("deleted element: %d\n",queueArray[front + 1]); //pop element from front
		hasValue[front + 1] = 0; //set back to 0, position empty
		front++;
	}
	
	/*determine again, output front = 3 rear = 3 isn't legal*/
	if(front == rear)
	{
		front = 0;
		rear = 0;
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

	printf("\n\n");
}
