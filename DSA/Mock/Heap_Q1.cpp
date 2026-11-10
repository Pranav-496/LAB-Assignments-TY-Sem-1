/*
A company receives multiple job requests, each with a priority value. 
The manager wants to process the most important (highest priority) job first and also identify the least
priority one for deferred execution. 
Write a C++ program using max heap and min heap to perform the following operations:
1. Insert a new job with its priority
2. Find and display the highest priority and lowest priority jobs
3. Delete the job with the highest priority
4. Display all the jobs in order of priority.
Also analyze the time complexity of each operation: insert, delete, find min, max.
Operation	                            Time complexity
Insert into Min Heap	                O(log N)
Insert into Max Heap	                O(log N)
Find minimum	                        O(1)
Find maximum	                        O(1)
Delete root from Max Heap	            O(log N)
Synchronize Min Heap after deletion	  O(N)
Display all jobs in sorted order	    O(N log N)
*/

#include <bits/stdc++.h>
using namespace std;

class Heap
{
  vector<int> h;
  bool isMax;

public:
  Heap(bool type)
  {
    isMax = type;
    create();
  }

  void create()
  {
    h.clear();
  }

  bool compare(int a, int b)
  {
    if (isMax)
      return a > b;
    else
      return a < b;
  }

  // Reheap Up
  void reheapUp(int i)
  {
    while (i > 0)
    {
      int parent = (i - 1) / 2;

      if (compare(h[i], h[parent]))
      {
        swap(h[i], h[parent]);
        i = parent;
      }
      else
        break;
    }
  }

  // Insert Job
  void insert(int value)
  {
    h.push_back(value);
    reheapUp(h.size() - 1);
  }

  // Reheap Down
  void reheapDown(int i)
  {
    int n = h.size();

    while (true)
    {
      int left = 2 * i + 1;
      int right = 2 * i + 2;
      int best = i;

      if (left < n && compare(h[left], h[best]))
        best = left;

      if (right < n && compare(h[right], h[best]))
        best = right;

      if (best != i)
      {
        swap(h[i], h[best]);
        i = best;
      }
      else
        break;
    }
  }

  // Delete Root
  int deleteRoot()
  {
    if (h.empty())
      return -1;

    int value = h[0];

    h[0] = h.back();
    h.pop_back();

    if (!h.empty())
      reheapDown(0);

    return value;
  }

  // Delete a particular value
  bool deleteValue(int value)
  {
    int i = 0;

    while (i < h.size() && h[i] != value)
      i++;

    if (i == h.size())
      return false;

    h[i] = h.back();
    h.pop_back();

    if (i < h.size())
    {
      if (i > 0 && compare(h[i], h[(i - 1) / 2]))
        reheapUp(i);
      else
        reheapDown(i);
    }

    return true;
  }

  // Find Root
  int getRoot()
  {
    if (h.empty())
      return -1;

    return h[0];
  }

  bool empty()
  {
    return h.empty();
  }

  // Display jobs in priority order
  void display()
  {
    if (h.empty())
    {
      cout << "No jobs available!";
      return;
    }

    Heap temp = *this;

    while (!temp.empty())
    {
      cout << temp.deleteRoot() << " ";
    }

    cout << endl;
  }
};

int main()
{

  Heap maxHeap(true);
  Heap minHeap(false);

  int choice, priority;

  do
  {
    cout << "\n\n----- JOB PRIORITY MANAGEMENT -----";
    cout << "\n1. Insert New Job";
    cout << "\n2. Find Highest Priority Job";
    cout << "\n3. Find Lowest Priority Job";
    cout << "\n4. Delete Highest Priority Job";
    cout << "\n5. Display Jobs in Priority Order";
    cout << "\n6. Exit";

    cout << "\nEnter choice: ";
    cin >> choice;

    switch (choice)
    {

    case 1:
      cout << "Enter job priority: ";
      cin >> priority;

      maxHeap.insert(priority);
      minHeap.insert(priority);

      cout << "Job inserted successfully!";
      break;

    case 2:
      if (maxHeap.empty())
        cout << "No jobs available!";
      else
        cout << "Highest Priority: "
             << maxHeap.getRoot();
      break;

    case 3:
      if (minHeap.empty())
        cout << "No jobs available!";
      else
        cout << "Lowest Priority: "
             << minHeap.getRoot();
      break;

    case 4:
      if (maxHeap.empty())
      {
        cout << "No jobs available!";
        break;
      }

      priority = maxHeap.deleteRoot();

      minHeap.deleteValue(priority);

      cout << "Deleted highest priority job: "
           << priority;
      break;

    case 5:
      cout << "Jobs in descending priority order:\n";
      maxHeap.display();
      break;

    case 6:
      cout << "Exiting program...";
      break;

    default:
      cout << "Invalid choice!";
    }

  } while (choice != 6);

  return 0;
}