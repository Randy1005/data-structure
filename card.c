#include<stdio.h>
#include<stdlib.h>
#include<time.h>   
int p1[]={0},p2[]={0},p3[]={0},p4[]={0};
int poker[52],i,j;
void shuffle_deal()
{   
	srand(time(NULL));
	int p,k,temp;
	char flower[4]={'c','d','h','s'};
	char num[13]={'a','2','3','4','5','6','7','8','9','t','j','q','k'};
	for(i=0;i<52;i++)
		poker[i]=i;
	for(i=0;i<52;i++)
	{
		j=rand()%52;
		temp=poker[i];
		poker[i]=poker[j];
		poker[j]=temp;
	}
	for(j=0;j<4;j++)
	{
		for(i=0;i<5;i++){
			p1[i]=poker[i+j*4];
			p2[i]=poker[i+j*4+1];
			p3[i]=poker[i+j*4+2];
			p4[i]=poker[i+j*4+3];}
	}
	printf("p1:   ");
	for(i=0;i<5;i++)
		printf("%c%2c\t",flower[p1[i]/13],num[p1[i]%13]);

	printf("\np2:   ");
	for(i=0;i<5;i++)
		printf("%c%2c\t",flower[p2[i]/13],num[p2[i]%13]);
	printf("\np3:   ");
	for(i=0;i<5;i++)
		printf("%c%2c\t",flower[p3[i]/13],num[p3[i]%13]);
	printf("\np4:   ");
	for(i=0;i<5;i++)
		printf("%c%2c\t",flower[p4[i]/13],num[p4[i]%13]);
	printf("\n");
}

int main()
{
	shuffle_deal();
}
