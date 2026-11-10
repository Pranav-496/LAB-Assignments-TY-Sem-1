#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, capacity;

    cout << "Enter number of items: ";
    if (!(cin >> n) || n < 0) // simply cin >> n bhi chalega itne drame ki jarurat nahi 
    {
        cerr << "Number of items must be a non-negative integer.\n";
        return 1;
    }

    cout << "Enter knapsack capacity: ";
    if (!(cin >> capacity) || capacity < 0) // simply cin >> capacity bhi chalega itne drame ki jarurat nahi 
    {
        cerr << "Capacity must be a non-negative integer.\n";
        return 1;
    }

    vector<int> profits(n), weights(n);
    cout << "Enter profit and weight of each item:\n";
    for (int i = 0; i < n; i++)
    {
        if (!(cin >> profits[i] >> weights[i]) ||
            profits[i] < 0 || weights[i] < 0)
        {
            cerr << "Profits and weights must be non-negative integers.\n";
            return 1;
        }
    }

    vector<long long> dp(capacity + 1, 0);

    for (int i = 0; i < n; i++)
    {
        for (int currentCapacity = capacity; currentCapacity >= weights[i]; currentCapacity--)
        {
            dp[currentCapacity] = max(
                dp[currentCapacity],
                dp[currentCapacity - weights[i]] + profits[i]);
        }
    }

    cout << "Maximum Profit = " << dp[capacity] << endl;
    return 0;
}
