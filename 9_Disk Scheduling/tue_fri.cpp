#include<bits/stdc++.h>
using namespace std;

void FCFS(vector<int> req, int head)
{
    int seek = 0;
    for(int i=0;i<req.size();i++)
    {
        seek += abs(head - req[i]);
        head = req[i];
    }

    cout<< " FCFS Total Seek Time: "<<seek <<endl;
}

void SSTF(vector<int> req, int head)
{
    int n = req.size();
    vector<bool> visited(n,false);
    int seek = 0;

    for(int i=0;i<n;i++)
    {
        int idx = -1;
        int mindist = INT_MAX;

        for(int j=0;j<n;j++)
        {
            if(!visited[j] && abs(head - req[j]) < mindist)
            {
                mindist = abs(head-req[j]);
                idx = j;
            }
        }

        seek+=mindist;
        head = req[idx];
        visited[idx] = true;
    }

    cout<<"SSTF total seek time: "<<seek<<endl;
}

void SCAN(vector<int> req, int head, int disk_size)
{
    int seek = 0;
    vector<int> left, right;

    for(int r : req)
    {
        if(r < head) left.push_back(r);
        else right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Move right first
    for(int r : right)
    {
        seek += abs(head - r);
        head = r;
    }

    // Go to end
    seek += abs(head - (disk_size - 1));
    head = disk_size - 1;

    // Reverse direction (left side)
    for(int i = left.size() - 1; i >= 0; i--)
    {
        seek += abs(head - left[i]);
        head = left[i];
    }

    cout << "SCAN Total Seek Time: " << seek << endl;
}


void CSCAN(vector<int> req, int head, int disk_size)
{
    int seek = 0;
    vector<int> left, right;

    for(int r : req)
    {
        if(r >= head) right.push_back(r);
        else left.push_back(r);
    }

    sort(right.begin(), right.end());
    sort(left.begin(), left.end());

    // Move right
    for(int r : right)
    {
        seek += abs(head - r);
        head = r;
    }

    // Go to end
    seek += abs(head - (disk_size - 1));
    head = 0;

    // Jump to beginning
    seek += (disk_size - 1);

    // Move left part
    for(int r : left)
    {
        seek += abs(head - r);
        head = r;
    }

    cout << "CSCAN Total Seek Time: " << seek << endl;
}

void LOOK(vector<int> req, int head)
{
    int seek = 0;
    vector<int> left, right;

    for(int r : req)
    {
        if(r < head) left.push_back(r);
        else right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Move right first
    for(int r : right)
    {
        seek += abs(head - r);
        head = r;
    }

    // Reverse direction (only till last request)
    for(int i = left.size() - 1; i >= 0; i--)
    {
        seek += abs(head - left[i]);
        head = left[i];
    }

    cout << "LOOK Total Seek Time: " << seek << endl;
}

void CLOOK(vector<int> req, int head)
{
    int seek = 0;
    vector<int> left, right;

    for(int r : req)
    {
        if(r >= head) right.push_back(r);
        else left.push_back(r);
    }

    sort(right.begin(), right.end());
    sort(left.begin(), left.end());

    // Move right
    for(int r : right)
    {
        seek += abs(head - r);
        head = r;
    }

    // Jump to first of left
    if(!left.empty())
    {
        seek += abs(head - left[0]);
        head = left[0];
    }

    // Continue left
    for(int i = 0; i < left.size(); i++)
    {
        seek += abs(head - left[i]);
        head = left[i];
    }

    cout << "CLOOK Total Seek Time: " << seek << endl;
}

int main()
{
    // Tuesday/Friday
    vector<int> req1 = {55, 58, 39, 18, 90, 160, 150, 38, 184};
    int head1 = 100;

    FCFS(req1, head1);
    SSTF(req1, head1);

    cout << endl;

    // Wednesday
    vector<int> req2 = {86, 1470, 913, 1774, 948, 1509, 1022, 1750, 130};
    int head2 = 143;
    int disk_size = 5000;

    CSCAN(req2, head2, disk_size);
    CLOOK(req2, head2);

    return 0;
}