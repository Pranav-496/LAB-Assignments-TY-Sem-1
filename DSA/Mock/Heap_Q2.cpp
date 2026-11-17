/*
In an online gaming tournament, players receive scores for each round.
The organizer wants to find the highest and lowest scores among all the participants efficiently. 
Write a menu-driven C++ program using max heap and min heap to:
1. Insert player scores
2. Find and display the highest score
3. Find and display the lowest score
4. Delete the player with highest score
5. Display all the players in order of score.

Time Complexity Analysis:
Operation                               Time Complexity
-------------------------------------------------------
Insert into Min/Max Heap                O(log N)
Find Minimum / Maximum                  O(1)
Delete root from Max Heap               O(log N)
Synchronize Min Heap after deletion     O(N)
Display all scores in sorted order      O(N log N)
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

    // Insert Score
    void insert(int value)
    {
        h.push_back(value);
        reheapUp(h.size() - 1);
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

    // Display scores in descending order
    void display()
    {
        if (h.empty())
        {
            cout << "No scores available!\n";
            return;
        }

        vector<int> temp = h;
        sort(temp.begin(), temp.end(), greater<int>());

        for (int i = 0; i < (int)temp.size(); i++)
            cout << temp[i] << " ";
        cout << "\n";
    }
};

int main()
{
    Heap maxHeap(true);  // Max Heap for highest score
    Heap minHeap(false); // Min Heap for lowest score

    int choice, score;

    do
    {
        cout << "\n----- PLAYER SCORE MANAGEMENT -----";
        cout << "\n1. Insert Player Score";
        cout << "\n2. Find Highest Score";
        cout << "\n3. Find Lowest Score";
        cout << "\n4. Delete Highest Score";
        cout << "\n5. Display Scores in Descending Order";
        cout << "\n6. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter player score: ";
            cin >> score;
            maxHeap.insert(score);
            minHeap.insert(score);
            cout << "Score inserted successfully!\n";
            break;

        case 2:
            if (maxHeap.h.empty())
                cout << "No scores available!\n";
            else
                cout << "Highest Score: " << maxHeap.h[0] << "\n";
            break;

        case 3:
            if (minHeap.h.empty())
                cout << "No scores available!\n";
            else
                cout << "Lowest Score: " << minHeap.h[0] << "\n";
            break;

        case 4:
            if (maxHeap.h.empty())
            {
                cout << "No scores available!\n";
            }
            else
            {
                // 1. Delete highest score from maxHeap
                score = maxHeap.deleteRoot();

                // 2. Refresh minHeap with remaining scores from maxHeap
                minHeap.h.clear();
                for (int s : maxHeap.h)
                    minHeap.insert(s);

                cout << "Highest score deleted: " << score << "\n";
            }
            break;

        case 5:
            cout << "Scores in descending order:\n";
            maxHeap.display();
            break;

        case 6:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
