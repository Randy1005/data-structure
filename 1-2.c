#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


char set[3] = {'a','b','c'};
bool solution[3];


void genPowerSet(int currentElement);


int main()
{
	genPowerSet(0);
}

void genPowerSet(int currentElement)
{
	/*e.g 3 elements, if we've decided all 3 elements to be true or false, we've found one solution then print this solution*/
	int i;
	if(currentElement == 3)
	{
		printf("{");
		for(i=0;i<3;i++)
		{
			if(solution[i] == true)
				printf("%c",set[i]);
		}

		printf("}\n");
		return;
	}
	
	//run branches to get the solutions (one branch separates into true,false....)
	solution[currentElement] = true;
	genPowerSet(currentElement + 1);

	solution[currentElement] = false;
	genPowerSet(currentElement + 1);

}
