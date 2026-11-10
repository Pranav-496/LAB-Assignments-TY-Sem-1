#include <bits/stdc++.h>
using namespace std;

int n, capacity, maxProfit = 0;
vector<int> weight, profit;

int bound(int i, int currentWeight, int currentProfit)
{
    int total = currentProfit;
    int remaining = capacity - currentWeight;

    for (int j = i; j < n; j++)
    {
        if (weight[j] <= remaining)
        {
            remaining -= weight[j];
            total += profit[j];
        }
        else
        {
            total += profit[j] * remaining / weight[j];
            break;
        }
    }

    return total;
}

void knapsack(int i, int currentWeight, int currentProfit)
{
    if (currentWeight <= capacity)
        maxProfit = max(maxProfit, currentProfit);

    if (i == n || bound(i, currentWeight, currentProfit) <= maxProfit)
        return;

    // Include item
    if (currentWeight + weight[i] <= capacity)
    {
        knapsack(i + 1,
                 currentWeight + weight[i],
                 currentProfit + profit[i]);
    }

    // Exclude item
    knapsack(i + 1, currentWeight, currentProfit);
}

int main()
{
    cout << "Enter number of items: ";
    cin >> n;

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    weight.resize(n);
    profit.resize(n);

    cout << "Enter profit and weight of each item:\n";

    for (int i = 0; i < n; i++)
        cin >> profit[i] >> weight[i];

    // Sort by profit/weight ratio
    vector<pair<double, int>> items;

    for (int i = 0; i < n; i++)
        items.push_back({(double)profit[i] / weight[i], i});

    sort(items.rbegin(), items.rend());

    vector<int> w(n), p(n);

    for (int i = 0; i < n; i++)
    {
        w[i] = weight[items[i].second];
        p[i] = profit[items[i].second];
    }

    weight = w;
    profit = p;

    knapsack(0, 0, 0);

    cout << "Maximum Profit = " << maxProfit << endl;

    return 0;
}
