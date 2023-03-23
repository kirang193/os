#include<stdio.h>
#define MAX 100
int main(){
    // 21075031
    // Stimulating FCFS program 
    // OS LAB 7
	int bt[MAX]={0},at[MAX]={0},tat[MAX]={0},wt[MAX]={0},ct[MAX]={0};
	int n,sum=0;
	float totalTAT=0,totalWT=0;

	printf("Enter number of process: ");
	scanf("%d",&n);

	printf("---Enter arrival time and burst time for each process---\n\n");

	for(int i=0;i<n;i++)
	{

		printf("Arrival time of process[%d]: ",i+1);
		scanf("%d",&at[i]);
		
		printf("Burst time of process[%d]: ",i+1);
		scanf("%d",&bt[i]);
		
		printf("\n");
	}
		
	//calculate completion time of processes 	

	for(int j=0;j<n;j++)
	{
		sum+=bt[j];
		ct[j]+=sum;
	}

	//calculate turnaround time 

	for(int k=0;k<n;k++)
	{
		tat[k]=ct[k]-at[k];
		totalTAT+=tat[k];
	}
    
    //calculate waiting time
	
	for(int k=0;k<n;k++)
	{
		wt[k]=tat[k]-bt[k];
		totalWT+=wt[k];
	}
	
	printf("-----------Solution ----------\n\n");
	printf("P#\t A.T.\t B.T.\t C.T.\t T.A.T.\t W.T.\t\n\n");
	
	for(int i=0;i<n;i++)
	{
		printf("P%d\t %d\t %d\t %d\t %d\t %d\n",i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
	}
		
	printf("\n\nAverage Turnaround Time = %f\n",totalTAT/n);
	printf("Average WT = %f\n\n",totalWT/n);
	
	return 0;

    /*
    Example:
    Input:
    Enter number of process: 3
    ---Enter arrival time and burst time for each process---

    Arrival time of process[1]: 0
    Burst time of process[1]: 24

    Arrival time of process[2]: 0
    Burst time of process[2]: 3

    Arrival time of process[3]: 0
    Burst time of process[3]: 3

    -----------Solution ----------

    P#       A.T.    B.T.    C.T.    T.A.T.  W.T.

    P1       0       24      24      24      0
    P2       0       3       27      27      24
    P3       0       3       30      30      27


    Average Turnaround Time = 27.000000
    Average WT = 17.000000

   "Table" :

    p#   |   A.T.  |  B.T. |   C.T.  |  T.A.T. |  W.T.
   ------+---------+-------+---------+---------+-------+
    P1   |    0    |   24  |    24   |   24    |  0
    P2   |    0    |   3   |    27   |   27    |  24
    P3   |    0    |   3   |    30   |   30    |  27
    */
}
