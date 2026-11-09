#include <iostream>
#include <vector>
using namespace std;

class Heap
{
  vector<int> h;
  bool isMin;

public:
  // Create Heap
  Heap(bool type)
  {
    isMin = type;
    create();
  }

  void create()
  {
    h.clear();
  }

  // Compare elements according to heap type
  bool compare(int a, int b)
  {
    if (isMin)
      return a < b;
    else
      return a > b;
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

  // Insert Element
  void insert(int value)
  {
    h.push_back(value);

    int i = h.size() - 1;
    reheapUp(i);
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

  // Delete Root Element
  bool deleteRoot(int &value)
  {
    if (h.empty())
      return false;

    value = h[0];

    h[0] = h.back();
    h.pop_back();

    if (!h.empty())
      reheapDown(0);

    return true;
  }

  // Display Heap
  void display()
  {
    if (h.empty())
    {
      cout << "Heap is empty!";
      return;
    }

    for (int x : h)
      cout << x << " ";

    cout << endl;
  }
};

int main()
{

  Heap minHeap(true);
  Heap maxHeap(false);

  int choice, value;

  do
  {
    cout << "\n\n----- HEAP ADT MENU -----";
    cout << "\n1. Insert into Min Heap";
    cout << "\n2. Insert into Max Heap";
    cout << "\n3. Delete from Min Heap";
    cout << "\n4. Delete from Max Heap";
    cout << "\n5. Display Min Heap";
    cout << "\n6. Display Max Heap";
    cout << "\n7. Create / Reset Min Heap";
    cout << "\n8. Create / Reset Max Heap";
    cout << "\n9. Exit";

    cout << "\nEnter choice: ";
    cin >> choice;

    switch (choice)
    {

    case 1:
      cout << "Enter value: ";
      cin >> value;
      minHeap.insert(value);
      break;

    case 2:
      cout << "Enter value: ";
      cin >> value;
      maxHeap.insert(value);
      break;

    case 3:
      if (minHeap.deleteRoot(value))
        cout << "Deleted minimum: " << value;
      else
        cout << "Min Heap is empty!";
      break;

    case 4:
      if (maxHeap.deleteRoot(value))
        cout << "Deleted maximum: " << value;
      else
        cout << "Max Heap is empty!";
      break;

    case 5:
      cout << "Min Heap: ";
      minHeap.display();
      break;

    case 6:
      cout << "Max Heap: ";
      maxHeap.display();
      break;

    case 7:
      minHeap.create();
      cout << "Min Heap created/reset!";
      break;

    case 8:
      maxHeap.create();
      cout << "Max Heap created/reset!";
      break;

    case 9:
      cout << "Exiting...";
      break;

    default:
      cout << "Invalid choice!";
    }

  } while (choice != 9);

  return 0;
}