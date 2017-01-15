#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

void printArr(int *arr, int len) {
	for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

/*early events time*/
/*ee[j] = max {ee[i] + duration of <i, j>}*/
void cal_earlyEvent(int *ee, int events, int **aoe) 
{
	for (int i = 0; i < events; i++) 
	{
		for (int j = 0; j < events; j++) 
			if (aoe[i][j] != 0 && ee[i] + aoe[i][j] > ee[j]) 
				ee[j] = ee[i] + aoe[i][j];
	}
}

/*late events time*/
/*le[j] = min {le[i] - duration of <i, j>}*/
void cal_lateEvent(int *le, int *ee, int events, int **aoe) 
{
	int len = events - 1;
	le[len] = ee[len];
	for (int i = len; i >= 0; --i) 
	{
		for (int j = len; j >= 0; --j) 
			if (aoe[i][j] != 0 && le[j] - aoe[i][j] < le[i]) 
				le[i] = le[j] - aoe[i][j];
	}
}

/*early and late activity time*/
/*
 * for an activity<k, l>
 * e[i] = ee[k]
 * l[i] = le[l] - act[k][l]
 */
void cal_eAct_lAct(int *e, int *l, int *ee, int *le, int events, int **aoe)
{
	int k = 0;
	for (int i = 0; i < events; i++) 
	{
		for (int j = 0; j < events; j++) 
		{
			if (aoe[i][j] != 0) 
			{
				e[k] = ee[i];
				l[k++] = le[j] - aoe[i][j];
			}
		}
	}

}


int main()
{
	FILE *ifp = fopen("Sample_input.txt","r");
	int event = 0;
	int lineCnt = 1;
	int activities = 0;

	/*get the first line, which is the matrixDimension*/

	while(!feof(ifp))
	{
		if(lineCnt == 1)
		{
			fscanf(ifp,"%d\n",&event);
			lineCnt++;
		}
		else
			break;	
	}

	/*create AOE matrix*/
	int **aoe;
	aoe = new int *[event];
	for(int i=0;i<event;i++)
		aoe[i] = new int[10];

	while(!feof(ifp))
	{
		for(int i=0;i<event;i++)
		{
			for(int j=0;j<event;j++)
				fscanf(ifp,"%d",&aoe[i][j]);
		}
		/*
		   if(feof(ifp))
		   printf("END OF FILE\n");
		 */
	}
	fclose(ifp);

	/*count activities*/
	for(int i=0;i<event;i++)
		for(int j=0;j<event;j++)
			if(aoe[i][j]) activities++;

	/*calculate early event time & late event time*/

	int *eEvent;
	int *lEvent;
	eEvent = new int[event];
	lEvent = new int[event];

	for(int i=0;i<event;i++)
	{
		eEvent[i] = 0;
		lEvent[i] = 9999;
	}
	cal_earlyEvent(eEvent,event,aoe);
	cal_lateEvent(lEvent,eEvent,event,aoe);
	int *eAct;
	eAct = new int[activities];
	int *lAct;
	lAct = new int[activities];

	//printArr(eEvent,event);
	//printArr(lEvent,event);

	cal_eAct_lAct(eAct,lAct,eEvent,lEvent,event,aoe);
	cout << "Early Time:" << endl;
	printArr(eAct,activities);
	cout << "Late Time:" << endl;
	printArr(lAct,activities);

	int *slack = new int[activities];
	for(int i=0;i<activities;i++)
		slack[i] = lAct[i] - eAct[i];
	cout << "Slack:" << endl;
	printArr(slack,activities);
}






