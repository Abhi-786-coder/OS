#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of patients: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n];
    int ct[n], tat[n], wt[n];
    int done[n];

    for(int i = 0; i < n; i++)
    {
        printf("\nPatient %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Treatment Time (BT): ");
        scanf("%d", &bt[i]);

        printf("Priority: ");
        scanf("%d", &pr[i]);

        done[i] = 0; // not treated yet
    }

    int completed = 0, time = 0;

    while(completed < n)
    {
        int idx = -1;
        int highest_priority = 9999;

        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && done[i] == 0)
            {
                if(pr[i] < highest_priority)
                {
                    highest_priority = pr[i];
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
            time++; // idle time
        }
    }

    // Output
    printf("\nPatient\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i],
               ct[i], tat[i], wt[i]);
    }

    return 0;
}