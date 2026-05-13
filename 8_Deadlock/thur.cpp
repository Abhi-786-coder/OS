#include <iostream>
#include <vector>
using namespace std;

// 🔹 Core function: returns true if safe and also gives sequence
bool isSafe(vector<int> alloc, vector<int> need, int avail, vector<int> &seq)
{
    int n = alloc.size();
    vector<bool> done(n, false);

    for (int k = 0; k < n; k++)
    {
        bool progress = false;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && need[i] <= avail)
            {
                avail += alloc[i];
                done[i] = true;
                seq.push_back(i);
                progress = true;
            }
        }

        if (!progress)
            return false; // stuck → unsafe
    }
    return true;
}

int main()
{
    int n = 4;

    vector<int> maxm = {40, 30, 50, 20};
    vector<int> alloc = {10, 15, 20, 5};

    int total = 100;

    // 🔹 Need
    vector<int> need(n);
    for (int i = 0; i < n; i++)
    {
        need[i] = maxm[i] - alloc[i];
    }

    // 🔹 Available
    int sum = 0;
    for (int x : alloc)
    {
        sum += x;
    }
    int avail = total - sum;

    // 🔹 Initial Safety Check
    vector<int> seq;
    if (isSafe(alloc, need, avail, seq))
    {
        cout << "Safe Sequence: ";
        for (int x : seq)
            cout << "C" << x << " ";
        cout << endl;
    }
    else
    {
        cout << "System NOT SAFE\n";
        return 0;
    }

    // 🔥 Request (C2 = 10)
    int p = 2;
    int request = 10;

    if (request <= need[p] && request <= avail)
    {
        // pretend allocation
        avail -= request;
        alloc[p] += request;
        need[p] -= request;

        vector<int> newSeq;

        if (isSafe(alloc, need, avail, newSeq))
        {
            cout << "Request GRANTED\nNew Sequence: ";
            for (int x : newSeq)
                cout << "C" << x << " ";
        }
        else
        {
            cout << "Request DENIED (Unsafe)\n";
        }
    }
    else
    {
        cout << "Request INVALID\n";
    }

    return 0;
}