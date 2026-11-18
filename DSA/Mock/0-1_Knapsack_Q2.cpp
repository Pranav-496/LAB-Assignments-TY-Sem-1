/*
A cloud storage provider has limited storage capacity S GB.
It must decide which files (each with a size and importance value) to back up to maximize total importance.
Write a C++ program using a 0/1 knapsack approach (DP) to find a subset of files that yields the maximum importance without exceeding storage capacity.
Display:
- Selected files
- Total storage used
- Maximum importance achieved
*/

#include <iostream>
#include <vector>
using namespace std;

struct File
{
    int id;
    int size;
    int importance;
};

int main()
{
    int n, S;

    cout << "Enter number of files: ";
    cin >> n;

    cout << "Enter total storage capacity (GB): ";
    cin >> S;

    vector<File> files(n);
    cout << "Enter size and importance of each file:\n";

    for (int i = 0; i < n; i++)
    {
        files[i].id = i + 1;
        cout << "File " << i + 1 << " - Size (GB) and Importance: ";
        cin >> files[i].size >> files[i].importance;
    }

    // dp[w] stores the maximum importance possible with storage capacity w
    vector<int> dp(S + 1, 0);

    // selected[w] stores the file IDs that give the optimal importance for capacity w
    vector<vector<int>> selected(S + 1);

    // 1D DP Knapsack:
    // Outer loop considers each file one by one
    for (int i = 0; i < n; i++)
    {
        // Inner loop runs BACKWARDS from S down to file size (ensures 0/1 choice)
        for (int w = S; w >= files[i].size; w--)
        {
            if (dp[w - files[i].size] + files[i].importance > dp[w])
            {
                dp[w] = dp[w - files[i].size] + files[i].importance;
                selected[w] = selected[w - files[i].size];
                selected[w].push_back(files[i].id);
            }
        }
    }

    cout << "\n--- Selected Files ---\n";
    int totalSize = 0;

    for (int id : selected[S])
    {
        cout << "File " << id
             << " | Size: " << files[id - 1].size << " GB"
             << " | Importance: " << files[id - 1].importance << "\n";

        totalSize += files[id - 1].size;
    }

    cout << "\nTotal Storage Used = " << totalSize << " GB" << endl;
    cout << "Maximum Importance = " << dp[S] << endl;

    return 0;
}
