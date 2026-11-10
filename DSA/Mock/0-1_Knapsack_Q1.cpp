/*
A marketing firm can choose from n adcertisement campaigns, each having a cost an an expected reach value(benefit).
Given a total budget B, use a 0/1 knapsack approach (DP or Branch and bound) to determine the optimal set of campaigns that maximizes
the total reach value.
Display:
- Selected campaigns
- Total cost used
- Maximum reach achieved  
*/


#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, B;

    cout << "Enter number of campaigns: ";
    cin >> n;

    cout << "Enter total budget: ";
    cin >> B;

    vector<int> cost(n);
    vector<int> reach(n);

    cout << "Enter cost and reach of each campaign:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> cost[i] >> reach[i];
    }

    // DP table
    vector<vector<int>> dp(n + 1, vector<int>(B + 1, 0));

    // Build DP table
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= B; j++)
        {
            dp[i][j] = dp[i - 1][j];

            if (cost[i - 1] <= j)
            {
                dp[i][j] = max(
                    dp[i][j],
                    reach[i - 1] + dp[i - 1][j - cost[i - 1]]
                );
            }
        }
    }

    // Find selected campaigns
    vector<int> selected;
    int remainingBudget = B;

    for (int i = n; i >= 1; i--)
    {
        if (dp[i][remainingBudget] != dp[i - 1][remainingBudget])
        {
            selected.push_back(i);
            remainingBudget -= cost[i - 1];
        }
    }

    reverse(selected.begin(), selected.end());

    // Calculate total cost
    int totalCost = 0;

    cout << "\nSelected Campaigns:\n";

    for (int i : selected)
    {
        cout << "Campaign " << i
             << " (Cost: " << cost[i - 1]
             << ", Reach: " << reach[i - 1] << ")\n";

        totalCost += cost[i - 1];
    }

    cout << "\nTotal Cost Used = " << totalCost;
    cout << "\nMaximum Reach = " << dp[n][B] << endl;

    return 0;
}


// Branch and bound karne ke liye ye niche wala 

/*
#include <bits/stdc++.h>
using namespace std;

struct Campaign
{
    int id, cost, reach;
    double ratio;
};

int B, n;
int maxReach = 0;
int totalCost = 0;
vector<int> bestSelected;
vector<Campaign> campaigns;

double bound(int level, int cost, int reach)
{
    if (cost >= B)
        return reach;

    double result = reach;
    int remaining = B - cost;

    for (int i = level; i < n; i++)
    {
        if (campaigns[i].cost <= remaining)
        {
            remaining -= campaigns[i].cost;
            result += campaigns[i].reach;
        }
        else
        {
            result += campaigns[i].ratio * remaining;
            break;
        }
    }

    return result;
}

void knapsack(int level, int cost, int reach, vector<int> selected)
{
    if (cost <= B && reach > maxReach)
    {
        maxReach = reach;
        totalCost = cost;
        bestSelected = selected;
    }

    if (level == n || bound(level, cost, reach) <= maxReach)
        return;

    // Include current campaign
    if (cost + campaigns[level].cost <= B)
    {
        selected.push_back(campaigns[level].id);

        knapsack(level + 1,
                 cost + campaigns[level].cost,
                 reach + campaigns[level].reach,
                 selected);

        selected.pop_back();
    }

    // Exclude current campaign
    knapsack(level + 1, cost, reach, selected);
}

int main()
{
    cout << "Enter number of campaigns: ";
    cin >> n;

    cout << "Enter total budget: ";
    cin >> B;

    campaigns.resize(n);

    cout << "Enter cost and reach of each campaign:\n";

    for (int i = 0; i < n; i++)
    {
        campaigns[i].id = i + 1;
        cin >> campaigns[i].cost >> campaigns[i].reach;
        campaigns[i].ratio =
            (double)campaigns[i].reach / campaigns[i].cost;
    }

    // Sort campaigns by reach/cost ratio
    sort(campaigns.begin(), campaigns.end(),
         [](Campaign a, Campaign b)
         {
             return a.ratio > b.ratio;
         });

    vector<int> selected;

    knapsack(0, 0, 0, selected);

    cout << "\nSelected Campaigns:\n";

    for (int id : bestSelected)
    {
        for (auto c : campaigns)
        {
            if (c.id == id)
            {
                cout << "Campaign " << id
                     << " (Cost: " << c.cost
                     << ", Reach: " << c.reach << ")\n";
                break;
            }
        }
    }

    cout << "\nTotal Cost Used = " << totalCost;
    cout << "\nMaximum Reach = " << maxReach << endl;

    return 0;
}
*/