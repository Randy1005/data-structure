#include <stdio.h>
#include <stdlib.h>

int elementNum = 3;
char set[elementNum] = {'a','b','c'};
bool solution[elementNum];


void genPowerSet(int elementNum, int currentElement);


int main()
{
	




}

void genPowerSet(int elementNum, int currentElement)
{
	/*e.g 3 elements, if we've decided all 3 elements to be true or false, we've found one solution then print this solution*/
	int i;
	if(currentElement == elementNum)
	{
		for(i=0;i<elementNum;i++)
		{
			if(solution[i] == true)
				printf("%c ",set[i]);
		}
		printf("\n");
		return;
	}
	
	//run branches to get the solutions (one branch separates into true,false....)
	solution[currentElement] = true;
	genPowerSet(currentElement + 1);

	solution[currentElement] = false;
	genPowerSet(currentElement + 1);

}
