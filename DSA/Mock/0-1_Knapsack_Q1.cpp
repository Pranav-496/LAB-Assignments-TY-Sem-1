/*
A marketing firm can choose from n advertisement campaigns, each having a cost and an expected reach value (benefit).
Given a total budget B, use a 0/1 knapsack approach (DP or Branch and bound) to determine the optimal set of campaigns that maximizes
the total reach value.
Display:
- Selected campaigns
- Total cost used
- Maximum reach achieved  
*/

#include <iostream>
#include <vector>
using namespace std;

struct Campaign
{
    int id;
    int cost;
    int reach;
};

int main()
{
    int n, B;

    cout << "Enter number of campaigns: ";
    cin >> n;

    cout << "Enter total budget: ";
    cin >> B;

    vector<Campaign> campaigns(n);
    cout << "Enter cost and reach of each campaign:\n";

    for (int i = 0; i < n; i++)
    {
        campaigns[i].id = i + 1;
        cout << "Campaign " << i + 1 << " - Cost and Reach: ";
        cin >> campaigns[i].cost >> campaigns[i].reach;
    }

    // dp[w] stores the maximum reach possible within budget w
    vector<int> dp(B + 1, 0);

    // selected[w] stores the campaign IDs that gave the best reach for budget w
    vector<vector<int>> selected(B + 1);

    // 1D DP Knapsack:
    // Outer loop picks one campaign at a time
    for (int i = 0; i < n; i++)
    {
        // Inner loop runs BACKWARDS from B down to campaign's cost.
        // Running backwards ensures each campaign is used AT MOST ONCE (0/1 condition)
        for (int w = B; w >= campaigns[i].cost; w--)
        {
            if (dp[w - campaigns[i].cost] + campaigns[i].reach > dp[w])
            {
                dp[w] = dp[w - campaigns[i].cost] + campaigns[i].reach;
                selected[w] = selected[w - campaigns[i].cost];
                selected[w].push_back(campaigns[i].id);
            }
        }
    }

    cout << "\n--- Selected Campaigns ---\n";
    int totalCost = 0;

    for (int id : selected[B])
    {
        cout << "Campaign " << id
             << " | Cost: " << campaigns[id - 1].cost
             << " | Reach: " << campaigns[id - 1].reach << "\n";

        totalCost += campaigns[id - 1].cost;
    }

    cout << "\nTotal Cost Used = " << totalCost << endl;
    cout << "Maximum Reach   = " << dp[B] << endl;

    return 0;
}
