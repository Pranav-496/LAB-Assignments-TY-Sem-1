#include <bits/stdc++.h>
using namespace std;

void minHeapify(vector<int> &a, int n, int i)
{
  int smallest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && a[left] < a[smallest])
    smallest = left;

  if (right < n && a[right] < a[smallest])
    smallest = right;

  if (smallest != i)
  {
    swap(a[i], a[smallest]);
    minHeapify(a, n, smallest);
  }
}

void maxHeapify(vector<int> &a, int n, int i)
{
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && a[left] > a[largest])
    largest = left;

  if (right < n && a[right] > a[largest])
    largest = right;

  if (largest != i)
  {
    swap(a[i], a[largest]);
    maxHeapify(a, n, largest);
  }
}

void buildMinHeap(vector<int> &a, int n)
{
  for (int i = n / 2 - 1; i >= 0; i--)
    minHeapify(a, n, i);
}

void buildMaxHeap(vector<int> &a, int n)
{
  for (int i = n / 2 - 1; i >= 0; i--)
    maxHeapify(a, n, i);
}

int main()
{
  vector<int> marks, minHeap, maxHeap;
  int n, choice;

  do
  {
    cout << "\n\n----- MENU -----";
    cout << "\n1. Enter Student Marks";
    cout << "\n2. Display Marks";
    cout << "\n3. Find Minimum Marks";
    cout << "\n4. Find Maximum Marks";
    cout << "\n5. Exit";

    cout << "\nEnter choice: ";
    cin >> choice;

    switch (choice)
    {

    case 1:
      cout << "Enter number of students: ";
      cin >> n;

      if (n <= 0)
      {
        cout << "Invalid number of students!";
        break;
      }

      marks.resize(n);

      cout << "Enter marks:\n";
      for (int i = 0; i < n; i++)
      {
        cin >> marks[i];
      }

      minHeap = marks;
      maxHeap = marks;

      buildMinHeap(minHeap, n);
      buildMaxHeap(maxHeap, n);

      cout << "Heaps created successfully!";
      break;

    case 2:
      if (marks.empty())
      {
        cout << "Enter marks first!";
        break;
      }

      cout << "Student Marks: ";
      for (int x : marks)
        cout << x << " ";

      break;

    case 3:
      if (minHeap.empty())
      {
        cout << "Enter marks first!";
        break;
      }

      cout << "Minimum Marks: " << minHeap[0];
      break;

    case 4:
      if (maxHeap.empty())
      {
        cout << "Enter marks first!";
        break;
      }

      cout << "Maximum Marks: " << maxHeap[0];
      break;

    case 5:
      cout << "Exiting program...";
      break;

    default:
      cout << "Invalid choice!";
    }

  } while (choice != 5);

  return 0;
}