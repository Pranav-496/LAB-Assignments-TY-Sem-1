/*
A cloud service provider has a limited amount of processing time T available on a high-performance server.
There are several tasks with different execution times and profits associated.
Write a C++ program using a greedy approach (fractional knapsack logic) to allocate resources to maximize the total profit.
You may execute a fractional part of a task if the total time limit is reached.
Output the list of the tasks scheduled, fraction taken, and total profit achieved.
*/

#include <bits/stdc++.h>
using namespace std;

struct Task
{
  int id;
  float time, profit, ratio;
};

bool compare(Task a, Task b)
{
  return a.ratio > b.ratio;
}

int main()
{
  int n;
  float T, totalProfit = 0;

  cout << "Enter number of tasks: ";
  cin >> n;

  vector<Task> tasks(n);

  for (int i = 0; i < n; i++)
  {
    tasks[i].id = i + 1;

    cout << "Enter execution time and profit of task "
         << i + 1 << ": ";
    cin >> tasks[i].time >> tasks[i].profit;

    if (tasks[i].time <= 0 || tasks[i].profit < 0)
    {
      cout << "Invalid task data!\n";
      return 0;
    }

    tasks[i].ratio = tasks[i].profit / tasks[i].time;
  }

  cout << "Enter total available processing time: ";
  cin >> T;

  if (T < 0)
  {
    cout << "Invalid processing time!\n";
    return 0;
  }

  sort(tasks.begin(), tasks.end(), compare);

  cout << "\nScheduled Tasks:\n";
  cout << "Task\tFraction\tTime\tProfit\n";

  for (int i = 0; i < n && T > 0; i++)
  {
    float fraction, usedTime, earnedProfit;

    if (tasks[i].time <= T)
      fraction = 1.0;
    else
      fraction = T / tasks[i].time;

    usedTime = fraction * tasks[i].time;
    earnedProfit = fraction * tasks[i].profit;

    totalProfit += earnedProfit;
    T -= usedTime;

    cout << tasks[i].id << "\t"
         << fraction * 100 << "%\t\t"
         << usedTime << "\t"
         << earnedProfit << endl;
  }

  cout << "\nTotal Profit Achieved: " << totalProfit << endl;
  cout << "Remaining Processing Time: " << T << endl;

  return 0;
}
