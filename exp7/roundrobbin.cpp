#include <stdio.h>

int main()
{
    int max =100;
    int i, nop, time_elapsed = 0, num, time_quant, wt = 0, tat = 0, at[max], bt[max], bt_dup[max];
    bool check = 0;
    // wt -> total weighting time 
    // tat -> total turnaround time
    // nop -> number of processes
    // check -> check whether process has completed its burst time. bt[i]=0
    // num -> duplicate of nop
    // time_quant -> fixed time quantum for round robbin
    // at[] : arrival time array
    // wt[] : waiting time array
    // bt[] : burst time array
    // bt_dup : burst time duplicate array
    float avg_wt, avg_tat;
    printf(" Total number of process in the system: ");
    scanf("%d", &nop);

    // Take input of arrival and burst times.
    for (i = 0; i < nop; i++)
    {
        printf("\n Enter the Arrival and Burst time of the Process[%d]\n", i + 1);
        printf(" Arrival time is: "); // Take arrival time input
        scanf("%d", &at[i]);
        printf(" Burst time is: "); // Take burst time input
        scanf("%d", &bt[i]);
        bt_dup[i] = bt[i]; // storing bt in bt_dup array
    }
    // Take input for time quantum
    printf(" Enter the Time Quantum for the process: ");
    scanf("%d", &time_quant);
    // Display the process No, burst time, Turn Around Time and the waiting time
    printf("\n P# \t\t Burst Time \t\t\t TAT \t\t\t Waiting Time ");
    num = nop; // Duplicate of number of processes to be used in for loop
    for (time_elapsed = 0, i = 0; num != 0;)
    {
        if (bt_dup[i] <= time_quant && bt_dup[i] > 0) // checking conditions
        {
            time_elapsed = time_elapsed + bt_dup[i];
            bt_dup[i] = 0;
            check = 1;
        }
        else if (bt_dup[i] > 0)
        {
            bt_dup[i] = bt_dup[i] - time_quant;
            time_elapsed = time_elapsed + time_quant;
        }
        if (bt_dup[i] == 0 && check == 1)
        {
            num--; // decrement the process no.
            printf("\nP[%d] \t\t %d\t\t\t\t %d\t\t\t %d", i + 1, bt[i], time_elapsed - at[i], time_elapsed - at[i] - bt[i]);
            wt = wt + time_elapsed - at[i] - bt[i];
            tat = tat + time_elapsed - at[i];
            check = 0;
        }
        if (i == nop - 1)
        {
            // We have reached end of array. We need to iterate from start of array again. round in 'round robbin'
            i = 0;
        }
        else if (at[i + 1] <= time_elapsed)
        {
            // if next process already arrived, then we increment i(execute that process for time quanta)
            i++;
        }
        else
        {
            // else we will again iterate from 0.
            i = 0;
        }
    }
        // represents the average waiting time and Turn Around time
    avg_wt = wt * 1.0 / nop;
    avg_tat = tat * 1.0 / nop;
    printf("\n Average Turn Around Time: \t%f", avg_wt);
    printf("\n Average Waiting Time: \t%f", avg_tat);
    return 0;
}
/*
Total number of process in the system: 4

 Enter the Arrival and Burst time of the Process[1]
 Arrival time is: 0
 Burst time is: 8

 Enter the Arrival and Burst time of the Process[2]
 Arrival time is: 1
 Burst time is: 5

 Enter the Arrival and Burst time of the Process[3]
 Arrival time is: 2
 Burst time is: 10

 Enter the Arrival and Burst time of the Process[4]
 Arrival time is: 3
 Burst time is: 11
 Enter the Time Quantum for the process: 6

 P#              Burst Time              TAT             Waiting Time
P[2]             5                               10                      5
P[1]             8                               25                      17
P[3]             10                              27                      17
P[4]             11                              31                      20
 Average Turn Around Time:      14.750000
 Average Waiting Time:  23.250000
*/
