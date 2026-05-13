#include <iostream>
#include <vector>
using namespace std;

void FCFS(vector<int> req, int head)
{
    int seek = 0;

    for(int i = 0; i < req.size(); i++)
    {
        seek += abs(head - req[i]);
        head = req[i];
    }

    cout << "FCFS Total Seek Time: " << seek << endl;
}


void SSTF(vector<int> req, int head)
{
    int n = req.size();
    vector<bool> visited(n, false);
    int seek = 0;

    for(int i = 0; i < n; i++)
    {
        int idx = -1;
        int minDist = INT_MAX;

        for(int j = 0; j < n; j++)
        {
            if(!visited[j] && abs(head - req[j]) < minDist)
            {
                minDist = abs(head - req[j]);
                idx = j;
            }
        }

        seek += minDist;
        head = req[idx];
        visited[idx] = true;
    }

    cout << "SSTF Total Seek Time: " << seek << endl;
}

