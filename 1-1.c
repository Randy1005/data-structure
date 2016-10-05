#include <stdio.h>
#include <stdlib.h>

long int rec_factorial(int n);
long int iter_factorial(int n);

int main()
{
	int input;
	printf("please enter a number bigger than 0 , enter \"-1\" to end the program.\n");
	scanf("%d",&input);
	if(input == -1)
		exit(0);

	printf("iterative:%ld\n",iter_factorial(input));
	printf("recursive: %ld\n",rec_factorial(input));
}

long int rec_factorial(int n)
{
	if(n == 1 || n == 0)
		return 1;
	else
		return n * rec_factorial(n-1);


}

long int iter_factorial(int n)
{
	int i;
	int product;
	if(n == 1 || n == 0)
		return 1;
	else
	{
		product = 1;
		for(i=1;i<=n;i++)
			product = product * i;

		return product;
	}

}


