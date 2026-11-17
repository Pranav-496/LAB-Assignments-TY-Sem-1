/*
A company receives multiple job requests, each with a priority value. 
The manager wants to process the most important (highest priority) job first and also identify the least
priority one for deferred execution. 
Write a C++ program using max heap and min heap to perform the following operations:
1. Insert a new job with its priority
2. Find and display the highest priority and lowest priority jobs
3. Delete the job with the highest priority
4. Display all the jobs in order of priority.

Time Complexity Analysis:
Operation                               Time Complexity
-------------------------------------------------------
Insert into Min/Max Heap                O(log N)
Find Minimum / Maximum                  O(1)
Delete root from Max Heap               O(log N)
Synchronize Min Heap after deletion     O(N)
Display all jobs in sorted order        O(N log N)
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Structure to store a Job with its name and priority
struct Job
{
    string name;
    int priority;
};

// Helper function to sort jobs in descending order of priority
bool compareJobs(Job a, Job b)
{
    return a.priority > b.priority;
}

class Heap
{
public:
    vector<Job> h;
    bool isMax;

    Heap(bool type)
    {
        isMax = type;
    }

    bool compare(Job a, Job b)
    {
        return isMax ? (a.priority > b.priority) : (a.priority < b.priority);
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

    // Insert Job
    void insert(Job j)
    {
        h.push_back(j);
        reheapUp(h.size() - 1);
    }

    // Delete Root (Highest priority from Max Heap)
    Job deleteRoot()
    {
        if (h.empty())
            return {"", -1};

        Job value = h[0];
        h[0] = h.back();
        h.pop_back();

        if (!h.empty())
            reheapDown(0);

        return value;
    }

    // Display jobs in descending priority order
    void display()
    {
        if (h.empty())
        {
            cout << "No jobs available!\n";
            return;
        }

        vector<Job> temp = h;
        sort(temp.begin(), temp.end(), compareJobs);

        for (int i = 0; i < (int)temp.size(); i++)
            cout << "[" << temp[i].name << " : " << temp[i].priority << "] ";
        cout << "\n";
    }
};

int main()
{
    Heap maxHeap(true);  // Max Heap for highest priority
    Heap minHeap(false); // Min Heap for lowest priority

    int choice;
    string name;
    int priority;

    do
    {
        cout << "\n----- JOB PRIORITY MANAGEMENT -----";
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
            cout << "Enter job name: ";
            cin >> name;
            cout << "Enter job priority: ";
            cin >> priority;

            maxHeap.insert({name, priority});
            minHeap.insert({name, priority});
            cout << "Job inserted successfully!\n";
            break;

        case 2:
            if (maxHeap.h.empty())
                cout << "No jobs available!\n";
            else
                cout << "Highest Priority: " << maxHeap.h[0].name << " (Priority: " << maxHeap.h[0].priority << ")\n";
            break;

        case 3:
            if (minHeap.h.empty())
                cout << "No jobs available!\n";
            else
                cout << "Lowest Priority: " << minHeap.h[0].name << " (Priority: " << minHeap.h[0].priority << ")\n";
            break;

        case 4:
            if (maxHeap.h.empty())
            {
                cout << "No jobs available!\n";
            }
            else
            {
                // 1. Delete highest priority job from maxHeap
                Job deleted = maxHeap.deleteRoot();

                // 2. Refresh minHeap with remaining jobs from maxHeap
                minHeap.h.clear();
                for (Job j : maxHeap.h)
                    minHeap.insert(j);

                cout << "Deleted highest priority job: " << deleted.name << " (Priority: " << deleted.priority << ")\n";
            }
            break;

        case 5:
            cout << "Jobs in descending priority order:\n";
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
