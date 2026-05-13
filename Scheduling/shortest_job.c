#include <stdio.h>

int main()
{
    int n = 4;

    int at[] = {0, 2, 4, 6};
    int bt[] = {6, 4, 3, 5};

    int ct[4], tat[4], wt[4];
    int done[4] = {0};

    int completed = 0, time = 0;

    while(completed < n)
    {
        int idx = -1;
        int min_bt = 9999;

        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && done[i] == 0)
            {
                if(bt[i] < min_bt)
                {
                    min_bt = bt[i];
                    idx = i;
                }
            }
        }

        if(idx != -1)
        {
            time += bt[idx];
            ct[idx] = time;

            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            done[idx] = 1;
            completed++;
        }
        else
        {
            time++; // idle
        }
    }

    printf("Patient\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    return 0;
}