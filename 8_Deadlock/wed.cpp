#include <iostream>
#include <vector>
using namespace std;

// Safety check function
bool isSafe(vector<vector<int>> alloc,vector<vector<int>> need,vector<int> avail) 
{
    int n = alloc.size();      // number of processes
    int m = avail.size();      // number of resources

    vector<bool> finish(n, false);
    vector<int> work = avail;
    vector<int> safeSeq;

    for (int count = 0; count < n; count++)
    {
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool possible = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        possible = false;
                        break;
                    }
                }
                if (possible)
                {
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += alloc[i][j];
                    }
                    finish[i] = true;
                    safeSeq.push_back(i);
                }
            }
        }
    }

    cout << "Safe Sequence: ";
    for (int x : safeSeq) cout << "P" << x << " ";
    cout << endl;

    // If all processes finished, system is safe
    for (bool f : finish) if (!f) return false;
    return true;
}

int main() {
    // Example data
    vector<vector<int>> alloc = {{2,1,1},{1,1,1},{3,2,2},{1,1,2}};

    vector<vector<int>> maxm = {{6,5,7},{4,2,3},{7,5,6},{3,3,3}};
    vector<int> total = {10,20,30};

    int n = alloc.size();
    int m = total.size();

    // Need = Max - Allocation
    vector<vector<int>> need(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maxm[i][j] - alloc[i][j];

    // Available = Total - Sum(Allocation)
    vector<int> avail(m, 0);
    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) sum += alloc[i][j];
        avail[j] = total[j] - sum;
    }

    cout << "------ BANKER'S ALGORITHM ------\n";
    cout << "Initial check...\n";
    if (isSafe(alloc, need, avail))
    {
        cout << "✅ System is SAFE\n";
    }
    else
    {
        cout << "❌ System is UNSAFE\n";
    }

    // 🔥 Request Example: P1 requests (1,0,1)
    int p = 1;
    vector<int> request = {1,0,1};
    cout << "\nProcess P" << p << " requesting (1,0,1)...\n";

    // Check Request <= Need
    bool valid = true;
    for (int j = 0; j < m; j++)
    {
        if (request[j] > need[p][j]) 
        {
            valid = false;
        }
    }
    if (!valid)
    {
        cout << "❌ Request exceeds Need\n";
        return 0;
    }

    // Check Request <= Available
    for (int j = 0; j < m; j++)
    {
        if (request[j] > avail[j]) valid = false;
    }
    if (!valid)
    {
        cout << "❌ Not enough resources Available\n";
        return 0;
    }

    // Pretend allocation
    for (int j = 0; j < m; j++)
    {
        avail[j] -= request[j];
        alloc[p][j] += request[j];
        need[p][j] -= request[j];
    }

    cout << "After pretending allocation...\n";
    if (isSafe(alloc, need, avail))
    {
        cout << "✅ Request CAN be granted (System remains SAFE)\n";
    }
    else
    {
        cout << "❌ Request CANNOT be granted (Unsafe)\n";
    }

    return 0;
}
