/*
In an online gaming tournament, players receive scores for each round.
The organizer wants to find the highest and lowest scores among all the participants efficiently. 
Write a menu-driven C++ program using max heap and min heap to 
1. insert player scores
2. display the highest
3. find and display the highest score
4. delete the player with highest score
5. display all the players in order of score.
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

    // Insert Score
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

    // Delete a particular score
    void deleteValue(int value)
    {
        int i = 0;

        while (i < h.size() && h[i] != value)
            i++;

        if (i == h.size())
            return;

        h[i] = h.back();
        h.pop_back();

        if (i < h.size())
        {
            if (i > 0 && compare(h[i], h[(i - 1) / 2]))
                reheapUp(i);
            else
                reheapDown(i);
        }
    }

    // Get Root
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

    // Display scores in sorted order
    void display()
    {
        if (h.empty())
        {
            cout << "No scores available!";
            return;
        }

        Heap temp = *this;

        while (!temp.empty())
            cout << temp.deleteRoot() << " ";

        cout << endl;
    }
};

int main()
{
    Heap maxHeap(true);
    Heap minHeap(false);

    int choice, score;

    do
    {
        cout << "\n\n----- PLAYER SCORE MANAGEMENT -----";
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

            cout << "Score inserted successfully!";
            break;

        case 2:
            if (maxHeap.empty())
                cout << "No scores available!";
            else
                cout << "Highest Score: " << maxHeap.getRoot();
            break;

        case 3:
            if (minHeap.empty())
                cout << "No scores available!";
            else
                cout << "Lowest Score: " << minHeap.getRoot();
            break;

        case 4:
            if (maxHeap.empty())
            {
                cout << "No scores available!";
                break;
            }

            score = maxHeap.deleteRoot();
            minHeap.deleteValue(score);

            cout << "Highest score deleted: " << score;
            break;

        case 5:
            cout << "Scores in descending order:\n";
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
