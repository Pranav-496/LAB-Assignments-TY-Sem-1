/*
A stock analyst recorded the daily stock prices of a company.
They want to quickly find the highest and lowest prices during a given period.
Write a C++ program using heap data structure to perform the following:
1. Insert data stock prices
2. Display the maximum and minimum stock price
3. Delete the topmost maximum price
4. Display all prices in ascending or descending order.
Perform algorithmic analysis for insertion and deletion operations.
*/

#include <bits/stdc++.h>
using namespace std;

class Heap
{
  vector<int> arr;
  bool isMax;

public:
  Heap(bool type)
  {
    isMax = type;
  }

  bool compare(int a, int b)
  {
    if (isMax)
      return a > b;
    return a < b;
  }

  void insert(int value)
  {
    arr.push_back(value);
    int i = arr.size() - 1;

    while (i > 0)
    {
      int parent = (i - 1) / 2;

      if (compare(arr[i], arr[parent]))
      {
        swap(arr[i], arr[parent]);
        i = parent;
      }
      else
        break;
    }
  }

  void heapify(int i)
  {
    int n = arr.size();
    int best = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compare(arr[left], arr[best]))
      best = left;

    if (right < n && compare(arr[right], arr[best]))
      best = right;

    if (best != i)
    {
      swap(arr[i], arr[best]);
      heapify(best);
    }
  }

  int getTop()
  {
    if (arr.empty())
      return -1;

    return arr[0];
  }

  void deleteTop()
  {
    if (arr.empty())
    {
      cout << "Heap is empty!\n";
      return;
    }

    arr[0] = arr.back();
    arr.pop_back();

    if (!arr.empty())
      heapify(0);
  }

  void deleteValue(int value)
  {
    for (int i = 0; i < arr.size(); i++)
    {
      if (arr[i] == value)
      {
        arr[i] = arr.back();
        arr.pop_back();

        if (i < arr.size())
        {
          if (i > 0 && compare(arr[i], arr[(i - 1) / 2]))
          {
            while (i > 0)
            {
              int parent = (i - 1) / 2;

              if (compare(arr[i], arr[parent]))
              {
                swap(arr[i], arr[parent]);
                i = parent;
              }
              else
                break;
            }
          }
          else
            heapify(i);
        }
        return;
      }
    }
  }

  void displaySorted()
  {
    Heap temp = *this;

    while (!temp.arr.empty())
    {
      cout << temp.getTop() << " ";
      temp.deleteTop();
    }
    cout << endl;
  }

  bool empty()
  {
    return arr.empty();
  }
};

int main()
{
  Heap maxHeap(true);
  Heap minHeap(false);

  int n, price, choice;

  do
  {
    cout << "\n1. Insert Stock Price";
    cout << "\n2. Display Maximum and Minimum Price";
    cout << "\n3. Delete Maximum Price";
    cout << "\n4. Display Prices in Ascending Order";
    cout << "\n5. Display Prices in Descending Order";
    cout << "\n6. Exit";
    cout << "\nEnter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter stock price: ";
      cin >> price;

      maxHeap.insert(price);
      minHeap.insert(price);

      cout << "Stock price inserted successfully.\n";
      break;

    case 2:
      if (maxHeap.empty())
        cout << "No stock prices available.\n";
      else
      {
        cout << "Maximum Price: " << maxHeap.getTop() << endl;
        cout << "Minimum Price: " << minHeap.getTop() << endl;
      }
      break;

    case 3:
      if (maxHeap.empty())
        cout << "No stock prices available.\n";
      else
      {
        price = maxHeap.getTop();
        maxHeap.deleteTop();
        minHeap.deleteValue(price);

        cout << "Maximum price " << price
             << " deleted successfully.\n";
      }
      break;

    case 4:
      if (minHeap.empty())
        cout << "No stock prices available.\n";
      else
      {
        cout << "Prices in Ascending Order: ";
        minHeap.displaySorted();
      }
      break;

    case 5:
      if (maxHeap.empty())
        cout << "No stock prices available.\n";
      else
      {
        cout << "Prices in Descending Order: ";
        maxHeap.displaySorted();
      }
      break;

    case 6:
      cout << "Exiting program.\n";
      break;

    default:
      cout << "Invalid choice!\n";
    }

  } while (choice != 6);

  return 0;
}
