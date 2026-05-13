#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>> alloc, vector<vector<int>> maxm, vector<int> avail)
{
    int n = alloc.size(); // number of processes
    int m = avail.size(); // how many resources

    vector<vector<int>> need(n, vector<int>(m));

    // Calculate Need = Max - Allocation
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = maxm[i][j] - alloc[i][j];

    vector<bool> finish(n, false);
    vector<int> safeSeq;

    for(int count = 0; count < n; count++)
    {
        bool found = false;

        for(int i = 0; i < n; i++)
        {
            if(!finish[i])
            {
                bool possible = true;

                for(int j = 0; j < m; j++)
                {
                    if(need[i][j] > avail[j])
                    {
                        possible = false;
                        break;
                    }
                }

                if(possible)
                {
                    // Allocate
                    for(int j = 0; j < m; j++)
                        avail[j] += alloc[i][j];

                    safeSeq.push_back(i);
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found)
        {
            cout << "System is NOT in safe state\n";
            return false;
        }
    }

    cout << "System is in SAFE state\nSafe sequence: ";
    for(int i : safeSeq)
        cout << "P" << i << " ";
    cout << endl;

    return true;
}

int main()
{
    int n = 4, m = 3;

    // Allocation Matrix
    vector<vector<int>> alloc = {
        {1,0,1}, // P0
        {2,1,0}, // P1
        {1,1,1}, // P2
        {0,1,2}  // P3
    };

    // Max Matrix
    vector<vector<int>> maxm = {{3,2,2},{2,2,2},{2,2,2},{1,2,3}};

    // Total resources
    vector<int> total = {6,4,5};

    // Calculate Available
    vector<int> avail(m, 0);

    for(int j = 0; j < m; j++)
    {
        int sum = 0;
        for(int i = 0; i < n; i++)
            sum += alloc[i][j];

        avail[j] = total[j] - sum;
    }

    cout << "Initial Safety Check:\n";
    isSafe(alloc, maxm, avail);

    // --------------------------
    // P2 Request: (1,0,1)
    // --------------------------

    vector<int> request = {1,0,1};
    int p = 2;

    cout << "\nProcessing Request for P2: (1,0,1)\n";

    // Calculate Need
    vector<vector<int>> need(n, vector<int>(m));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = maxm[i][j] - alloc[i][j];

    // Check Request <= Need
    bool valid = true;
    for(int j = 0; j < m; j++)
    {
        if(request[j] > need[p][j])
        {
            valid = false;
            break;
        }
    }

    if(!valid)
    {
        cout << "Error: Request exceeds maximum need\n";
        return 0;
    }

    // Check Request <= Available
    for(int j = 0; j < m; j++)
    {
        if(request[j] > avail[j])
        {
            cout << "Request cannot be granted immediately (not enough resources)\n";
            return 0;
        }
    }

    // Try allocation
    for(int j = 0; j < m; j++)
    {
        avail[j] -= request[j];
        alloc[p][j] += request[j];
    }

    cout << "Checking safety after allocation...\n";

    if(isSafe(alloc, maxm, avail))
        cout << "Request CAN be granted safely\n";
    else
        cout << "Request CANNOT be granted (unsafe)\n";

    return 0;
}