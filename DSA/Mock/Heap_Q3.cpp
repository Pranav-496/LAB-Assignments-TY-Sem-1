/*
A stock analyst recorded the daily stock prices of a company.
They want to quickly find the highest and lowest prices during a given period.
Write a C++ program using heap data structure to perform the following:
1. Insert data stock prices
2. Display the maximum and minimum stock price
3. Delete the topmost maximum price
4. Display all prices in ascending or descending order.

Time Complexity Analysis:
Operation                               Time Complexity
-------------------------------------------------------
Insert into Min/Max Heap                O(log N)
Find Minimum / Maximum                  O(1)
Delete root from Max Heap               O(log N)
Synchronize Min Heap after deletion     O(N)
Display all prices in sorted order      O(N log N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Heap
{
public:
    vector<int> h;
    bool isMax;

    Heap(bool type)
    {
        isMax = type;
    }

    bool compare(int a, int b)
    {
        return isMax ? (a > b) : (a < b);
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

    // Insert Stock Price
    void insert(int value)
    {
        h.push_back(value);
        reheapUp(h.size() - 1);
    }

    // Delete Root (Maximum price from Max Heap)
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

    // Display prices in ascending or descending order
    void display(bool ascending)
    {
        if (h.empty())
        {
            cout << "No stock prices available.\n";
            return;
        }

        vector<int> temp = h;
        if (ascending)
            sort(temp.begin(), temp.end());
        else
            sort(temp.begin(), temp.end(), greater<int>());

        for (int i = 0; i < (int)temp.size(); i++)
            cout << temp[i] << " ";
        cout << "\n";
    }
};

int main()
{
    Heap maxHeap(true);  // Max Heap for highest price
    Heap minHeap(false); // Min Heap for lowest price

    int price, choice;

    do
    {
        cout << "\n----- STOCK PRICE MANAGEMENT -----";
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
            if (maxHeap.h.empty())
                cout << "No stock prices available.\n";
            else
            {
                cout << "Maximum Price: " << maxHeap.h[0] << "\n";
                cout << "Minimum Price: " << minHeap.h[0] << "\n";
            }
            break;

        case 3:
            if (maxHeap.h.empty())
            {
                cout << "No stock prices available.\n";
            }
            else
            {
                // 1. Delete maximum price from maxHeap
                price = maxHeap.deleteRoot();

                // 2. Refresh minHeap with remaining prices from maxHeap
                minHeap.h.clear();
                for (int p : maxHeap.h)
                    minHeap.insert(p);

                cout << "Maximum price " << price << " deleted successfully.\n";
            }
            break;

        case 4:
            cout << "Prices in Ascending Order: ";
            maxHeap.display(true);
            break;

        case 5:
            cout << "Prices in Descending Order: ";
            maxHeap.display(false);
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
