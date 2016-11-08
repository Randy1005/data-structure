#include <stdio.h>

#define MAX 4

/*declare array for queue and rear, front index*/
char queueArray[MAX] = {' ',' ',' ',' '}
int rear = -1;
int front = -1;

void insert();
void delete();
void printQueue();

int main()
{
	
}

void chkFull()
{

}

void insert()
{
	char add_element;
	if(rear == MAX - 1)
	{
		printf("queue is full, stop inserting\n");
	}
	else
	{
		printf("Insert number: ");
		scanf("%c",&add_element);
		rear++; //every time I push an element rear increments
		queueArray[rear] = add_element;
		return;
	}

}

void delete()
{
	char delete_element;
	if((front == -1 && rear == -1) || front > rear) //queue is already empty
	{
		printf("queue is empty, stop deleting\n");
	}

	else
	{
		printf("deleted element: %c\n",queueArray[front + 1]); //pop element from front
		front++; //increment front

	}
}

void printQueue()
{
	int i;
	if(front == -1 && rear == -1)
	{
		printf("Queue is empty\n");
	}
	else if(rear == MAX -1)
		printf("Queue is full\n");
	else
	{
		printf("Front = %d Rear = %d\n",front,rear);
		printf("Queue: ");
		for(i=0;i<MAX;i++)
			printf("[%c]",queueArray[i]);

		printf("\n");
	}
}
