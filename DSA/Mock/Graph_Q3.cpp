/*
Representation of flight routes between cities using adjacency list.
There are several cities connected by direct flights. If a flight exists between city A and city B,
there is an edge between the corresponding nodes in the graph.
The weight of the edge represents the time taken in hours and cost in currency units of the flight.
Represent this flight network using an adjacency list and perform the following operations:
1. Check if direct flight exists between city A and city B with time and cost
2. Display all available flights with their corresponding time and cost
3. Count total flights from a city
4. Find all reachable cities from a source using matrix traversal
5. If direct flight is not available, display all connected flights path (with total time and cost)
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
    int dest;
    double time;
    double cost;
    Node *next;
};

class Graph
{
public:
    Node *adj[10];
    int mat[10][10];
    int n;

    Graph(int vertices)
    {
        n = vertices;

        for (int i = 0; i < n; i++)
        {
            adj[i] = NULL;
            for (int j = 0; j < n; j++)
                mat[i][j] = 0;
        }
    }

    // Add a flight route from city u to city v
    void addFlight(int u, int v, double time, double cost)
    {
        Node *newNode = new Node{v, time, cost, adj[u]};
        adj[u] = newNode;

        // Also update adjacency matrix for matrix traversal
        mat[u][v] = 1;

        cout << "Flight route added successfully from City " << u << " to City " << v << ".\n";
    }

    // 1. Check if direct flight exists between City u and City v
    bool checkDirectFlight(int u, int v)
    {
        Node *temp = adj[u];

        while (temp != NULL)
        {
            if (temp->dest == v)
            {
                cout << "Direct flight exists between City " << u << " and City " << v << ":\n";
                cout << "  Time : " << temp->time << " hours\n";
                cout << "  Cost : " << temp->cost << " currency units\n";
                return true;
            }
            temp = temp->next;
        }

        cout << "No direct flight exists between City " << u << " and City " << v << ".\n";
        return false;
    }

    // 2. Display all available flights with corresponding time and cost
    void displayAllFlights()
    {
        cout << "\n===== ALL AVAILABLE FLIGHT ROUTES =====\n";
        bool any = false;

        for (int i = 0; i < n; i++)
        {
            Node *temp = adj[i];
            while (temp != NULL)
            {
                cout << "City " << i << " -> City " << temp->dest
                     << " | Time: " << temp->time << " hrs"
                     << " | Cost: " << temp->cost << " units\n";
                any = true;
                temp = temp->next;
            }
        }

        if (!any)
            cout << "No flights scheduled.\n";
    }

    // 3. Count total flights from a city
    void countFlightsFromCity(int u)
    {
        int count = 0;
        Node *temp = adj[u];

        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }

        cout << "Total direct flights departing from City " << u << ": " << count << endl;
    }

    // 4. Find all reachable cities from source using matrix traversal (BFS on matrix)
    void findReachableCities(int src)
    {
        bool visited[10] = {false};
        queue<int> q;

        visited[src] = true;
        q.push(src);

        cout << "Reachable cities from City " << src << " (using matrix traversal): ";
        bool foundAny = false;

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            for (int j = 0; j < n; j++)
            {
                if (mat[curr][j] == 1 && !visited[j])
                {
                    visited[j] = true;
                    cout << "City " << j << " ";
                    foundAny = true;
                    q.push(j);
                }
            }
        }

        if (!foundAny)
            cout << "None";
        cout << endl;
    }

    // Helper DFS function to find and print connecting paths
    void dfsPaths(int curr, int dest, bool visited[], vector<int> &path, double currTime, double currCost, bool &found)
    {
        visited[curr] = true;
        path.push_back(curr);

        if (curr == dest)
        {
            // Only display if it has intermediate stops (connecting flights)
            if (path.size() > 2)
            {
                found = true;
                cout << "Connecting Flight Path: ";
                for (int i = 0; i < (int)path.size(); i++)
                {
                    cout << "City " << path[i];
                    if (i != (int)path.size() - 1)
                        cout << " -> ";
                }
                cout << "\n  Total Time: " << currTime << " hrs | Total Cost: " << currCost << " units\n";
            }
        }
        else
        {
            Node *temp = adj[curr];
            while (temp != NULL)
            {
                if (!visited[temp->dest])
                {
                    dfsPaths(temp->dest, dest, visited, path, currTime + temp->time, currCost + temp->cost, found);
                }
                temp = temp->next;
            }
        }

        path.pop_back();
        visited[curr] = false;
    }

    // 5. If direct flight is not available, display all connected flights path
    void findConnectedPaths(int u, int v)
    {
        // First check if direct flight exists
        bool direct = checkDirectFlight(u, v);

        if (direct)
        {
            cout << "(Direct flight is already available between these cities.)\n";
        }
        else
        {
            cout << "\nSearching for connecting flight paths between City " << u << " and City " << v << ":\n";
            bool visited[10] = {false};
            vector<int> path;
            bool found = false;

            dfsPaths(u, v, visited, path, 0, 0, found);

            if (!found)
                cout << "No connecting flight paths found between City " << u << " and City " << v << ".\n";
        }
    }
};

int main()
{
    int numCities;
    cout << "Enter number of cities (max 10): ";
    cin >> numCities;

    Graph g(numCities);

    int choice, u, v;
    double time, cost;

    do
    {
        cout << "\n====== FLIGHT NETWORK MANAGEMENT ======\n";
        cout << "1. Add Flight Route\n";
        cout << "2. Check Direct Flight (with Time & Cost)\n";
        cout << "3. Display All Available Flights\n";
        cout << "4. Count Total Flights from a City\n";
        cout << "5. Find All Reachable Cities (Matrix Traversal)\n";
        cout << "6. Find Connected Flights Path (If Direct Not Available)\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Source City (0 to " << numCities - 1 << "): ";
            cin >> u;
            cout << "Enter Destination City (0 to " << numCities - 1 << "): ";
            cin >> v;
            cout << "Enter Flight Time (in hours): ";
            cin >> time;
            cout << "Enter Flight Cost (in currency units): ";
            cin >> cost;

            g.addFlight(u, v, time, cost);
            break;

        case 2:
            cout << "Enter Source City: ";
            cin >> u;
            cout << "Enter Destination City: ";
            cin >> v;

            g.checkDirectFlight(u, v);
            break;

        case 3:
            g.displayAllFlights();
            break;

        case 4:
            cout << "Enter City to count departing flights: ";
            cin >> u;

            g.countFlightsFromCity(u);
            break;

        case 5:
            cout << "Enter Source City: ";
            cin >> u;

            g.findReachableCities(u);
            break;

        case 6:
            cout << "Enter Source City: ";
            cin >> u;
            cout << "Enter Destination City: ";
            cin >> v;

            g.findConnectedPaths(u, v);
            break;

        case 7:
            cout << "Exiting program. Safe travels!\n";
            break;

        default:
            cout << "Invalid choice! Please select 1-7.\n";
        }

    } while (choice != 7);

    return 0;
}
