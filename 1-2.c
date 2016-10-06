#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void genPowerSet(int currentElement, int num_of_element, char set[], bool solution[]);

int main()
{
	char set[100];
	char tmp;
	int cnt = 0;
	while(tmp != '}')
	{
		scanf("%c",&tmp);
		if(tmp != '{' && tmp != ',' && tmp != '}')
		{
			set[cnt] = tmp;
			cnt++;	
		}
	}
	bool solution[cnt];
	genPowerSet(0,cnt,set,solution);
	int i = 0;
	int num_of_set = 1;
	for(i=0;i<cnt;i++)
		num_of_set *= 2;
	printf("The Total Amount of Subsets is %d\n",num_of_set);
}

void genPowerSet(int currentElement, int num_of_element, char set[], bool solution[])
{
	/*e.g 3 elements, if we've decided all 3 elements to be true or false, we've found one solution then print this solution*/
	int i;
	if(currentElement == num_of_element)
	{
		printf("{");
		for(i=0;i<num_of_element;i++)
		{
			if(solution[i] == true)
				printf("%c",set[i]);
		}

		printf("}\n");
		return;
	}

	//run branches to get the solutions (one branch separates into true,false....)
	solution[currentElement] = true;
	genPowerSet(currentElement + 1,num_of_element,set,solution);

	solution[currentElement] = false;
	genPowerSet(currentElement + 1,num_of_element,set,solution);

}
