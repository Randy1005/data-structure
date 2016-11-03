#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	FILE *ifp;
	FILE *ofp;
	ifp = fopen("in.txt","r");
	
	/*to get M and N*/
	int M = 0;
	int N = 0;
	while(!feof(ifp))
	{
		bool M_flag = false; //count one line is enough, after we get M, set to 'true'
		char temp;
		fscanf(ifp,"%c",&temp);
		if(temp != '\n' && M_flag == false)
			M++;
		else
			M_flag = true;
	}

	fclose(ifp);
	printf("%d\n",M);


}
