/*
A cloud storage provider has limited stoarage capacity S GB.
It must decide which files (each with a size and importance value) to back up to maximize total importance.
Using DP or branch and bound. Write a C++ program to find a subset of files that yields the maximum importance without exceeding storage capacity.
Display selected files, total size and total importance score.
*/

// Dynamic Programming

#include <iostream>
using namespace std;

int main()
{
  int n, capacity;

  cout << "Enter number of files: ";
  cin >> n;

  int size[100], importance[100];

  cout << "Enter size and importance of each file:\n";

  for (int i = 0; i < n; i++)
  {
    cout << "File " << i + 1 << ": ";
    cin >> size[i] >> importance[i];
  }

  cout << "Enter storage capacity: ";
  cin >> capacity;

  int dp[101][1001] = {0};

  for (int i = 1; i <= n; i++)
  {
    for (int j = 0; j <= capacity; j++)
    {
      if (size[i - 1] <= j)
      {
        dp[i][j] = max(
            dp[i - 1][j],
            importance[i - 1] +
                dp[i - 1][j - size[i - 1]]);
      }
      else
      {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  int selected[100], count = 0;
  int totalSize = 0;
  int j = capacity;

  for (int i = n; i > 0; i--)
  {
    if (dp[i][j] != dp[i - 1][j])
    {
      selected[count++] = i - 1;
      totalSize += size[i - 1];
      j -= size[i - 1];
    }
  }

  cout << "\nSelected Files:\n";

  for (int i = count - 1; i >= 0; i--)
  {
    int k = selected[i];

    cout << "File " << k + 1
         << " - Size: " << size[k] << " GB"
         << ", Importance: " << importance[k] << endl;
  }

  cout << "\nTotal Storage Used: " << totalSize << " GB";
  cout << "\nMaximum Importance: " << dp[n][capacity] << endl;

  return 0;
}

// Branch and bound
/*
#include <iostream>
#include <algorithm>
using namespace std;

struct File
{
  int id, size, importance;
  double ratio;
};

File files[100];

int n, capacity;
int maxImportance = 0;
int bestSize = 0;
bool selected[100], bestSelected[100];

bool compare(File a, File b)
{
  return a.ratio > b.ratio;
}

double bound(int i, int currentSize, int currentImportance)
{
  if (currentSize >= capacity)
    return currentImportance;

  double result = currentImportance;
  int remaining = capacity - currentSize;

  while (i < n && files[i].size <= remaining)
  {
    remaining -= files[i].size;
    result += files[i].importance;
    i++;
  }

  if (i < n)
  {
    result += (double)files[i].importance *
              remaining / files[i].size;
  }

  return result;
}

void knapsack(int i, int currentSize, int currentImportance)
{
  if (currentImportance > maxImportance)
  {
    maxImportance = currentImportance;
    bestSize = currentSize;

    for (int k = 0; k < n; k++)
      bestSelected[k] = selected[k];
  }

  if (i == n)
    return;

  if (bound(i, currentSize, currentImportance) <= maxImportance)
    return;

  if (currentSize + files[i].size <= capacity)
  {
    selected[i] = true;

    knapsack(i + 1,
             currentSize + files[i].size,
             currentImportance + files[i].importance);

    selected[i] = false;
  }

  knapsack(i + 1, currentSize, currentImportance);
}

int main()
{
  cout << "Enter number of files: ";
  cin >> n;

  cout << "Enter size and importance of each file:\n";

  for (int i = 0; i < n; i++)
  {
    files[i].id = i + 1;

    cout << "File " << i + 1 << ": ";
    cin >> files[i].size >> files[i].importance;

    files[i].ratio =
        (double)files[i].importance / files[i].size;
  }

  cout << "Enter storage capacity: ";
  cin >> capacity;

  sort(files, files + n, compare);

  knapsack(0, 0, 0);

  cout << "\nSelected Files:\n";

  for (int i = 0; i < n; i++)
  {
    if (bestSelected[i])
    {
      cout << "File " << files[i].id
           << " - Size: " << files[i].size << " GB"
           << ", Importance: " << files[i].importance
           << endl;
    }
  }

  cout << "\nTotal Storage Used: " << bestSize << " GB";
  cout << "\nMaximum Importance: " << maxImportance << endl;

  return 0;
}
*/