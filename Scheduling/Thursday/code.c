#include <stdio.h>

int main()
{
    int n = 4;

    int at[] = {0, 2, 4, 6};
    int bt[] = {6, 4, 3, 5};

    int ct[4], tat[4], wt[4];

    // FCFS
    ct[0] = at[0] + bt[0];

    for(int i = 1; i < n; i++)
    {
        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i]; // idle case
        else
            ct[i] = ct[i-1] + bt[i];
    }

    // TAT and WT
    for(int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // Output
    printf("Patient\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    float avg_wt = 0, avg_tat = 0;

    for(int i = 0; i < n; i++)
    {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);

    return 0;
}