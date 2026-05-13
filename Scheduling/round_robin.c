#include <stdio.h>

int main()
{
    int n = 4, tq = 3;

    int at[] = {0, 1, 2, 3};
    int bt[] = {8, 5, 4, 6};

    int rem_bt[4], ct[4], tat[4], wt[4];

    for(int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    int time = 0, completed = 0;

    while(completed < n)
    {
        int done = 1;

        for(int i = 0; i < n; i++)
        {
            if(rem_bt[i] > 0 && at[i] <= time)
            {
                done = 0;

                if(rem_bt[i] > tq)
                {
                    time += tq;
                    rem_bt[i] -= tq;
                }
                else
                {
                    time += rem_bt[i];
                    ct[i] = time;
                    rem_bt[i] = 0;
                    completed++;
                }
            }
        }

        if(done)
        {
            time++;
        }
    }

    for(int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("R%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    return 0;
}