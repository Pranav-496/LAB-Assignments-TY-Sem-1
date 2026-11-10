/*
Different airlines share partnerships with each other, allowing code sharing flights.
If airline A has partnership with airline B, there is an edge between them.
The edge weight can represent number of shared routes or partnership strength.
Write a C++ program to represent this network using adjacency list and matrix.
The program should:
1. Check if two airlines have partnership
2. Display all airlines connected with a given airline
*/

// Adjacency List

#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
  int n;
  vector<pair<int, int>> adj[10];

  Graph(int size)
  {
    n = size;
  }

  void addPartnership(int u, int v, int weight)
  {
    adj[u].push_back({v, weight});
    adj[v].push_back({u, weight});

    cout << "Partnership added successfully.\n";
  }

  void checkPartnership(int u, int v)
  {
    for (auto x : adj[u])
    {
      if (x.first == v)
      {
        cout << "Partnership exists.\n";
        cout << "Partnership Strength = " << x.second;
        return;
      }
    }

    cout << "No partnership exists.\n";
  }

  void displayConnected(int u)
  {
    cout << "Airlines connected with Airline " << u << ":\n";

    for (auto x : adj[u])
    {
      cout << "Airline " << x.first
           << " (Strength = " << x.second << ")\n";
    }
  }

  void display()
  {
    cout << "\nAdjacency List:\n";

    for (int i = 0; i < n; i++)
    {
      cout << "Airline " << i << " -> ";

      for (auto x : adj[i])
      {
        cout << "(" << x.first
             << ", " << x.second << ") -> ";
      }

      cout << "NULL\n";
    }
  }
};

int main()
{
  int n, choice, u, v, weight;

  cout << "Enter number of airlines: ";
  cin >> n;

  Graph g(n);

  do
  {
    cout << "\n----- AIRLINE PARTNERSHIP MENU -----\n";
    cout << "1. Add Partnership\n";
    cout << "2. Check Partnership\n";
    cout << "3. Display Connected Airlines\n";
    cout << "4. Display Adjacency List\n";
    cout << "5. Exit\n";

    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter two airline IDs: ";
      cin >> u >> v;

      cout << "Enter partnership strength: ";
      cin >> weight;

      g.addPartnership(u, v, weight);
      break;

    case 2:
      cout << "Enter two airline IDs: ";
      cin >> u >> v;

      g.checkPartnership(u, v);
      break;

    case 3:
      cout << "Enter airline ID: ";
      cin >> u;

      g.displayConnected(u);
      break;

    case 4:
      g.display();
      break;

    case 5:
      cout << "Chalo Bye!\n";
      break;

    default:
      cout << "Invalid Choice!\n";
    }

  } while (choice != 5);

  return 0;
}

// Adjacency Matrix
/*
#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
  int n;
  int mat[10][10] = {0};

  Graph(int size)
  {
    n = size;
  }

  void addPartnership(int u, int v, int weight)
  {
    mat[u][v] = weight;
    mat[v][u] = weight;

    cout << "Partnership added successfully.\n";
  }

  void checkPartnership(int u, int v)
  {
    if (mat[u][v] != 0)
    {
      cout << "Partnership exists.\n";
      cout << "Partnership Strength = " << mat[u][v];
    }
    else
    {
      cout << "No partnership exists.\n";
    }
  }

  void displayConnected(int u)
  {
    cout << "Airlines connected with Airline " << u << ":\n";

    for (int i = 0; i < n; i++)
    {
      if (mat[u][i] != 0)
      {
        cout << "Airline " << i
             << " (Strength = " << mat[u][i] << ")\n";
      }
    }
  }

  void display()
  {
    cout << "\nAdjacency Matrix:\n";

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
        cout << mat[i][j] << "\t";

      cout << endl;
    }
  }
};

int main()
{
  int n, choice, u, v, weight;

  cout << "Enter number of airlines: ";
  cin >> n;

  Graph g(n);

  do
  {
    cout << "\n----- AIRLINE PARTNERSHIP MENU -----\n";
    cout << "1. Add Partnership\n";
    cout << "2. Check Partnership\n";
    cout << "3. Display Connected Airlines\n";
    cout << "4. Display Adjacency Matrix\n";
    cout << "5. Exit\n";

    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter two airline IDs: ";
      cin >> u >> v;

      cout << "Enter partnership strength: ";
      cin >> weight;

      g.addPartnership(u, v, weight);
      break;

    case 2:
      cout << "Enter two airline IDs: ";
      cin >> u >> v;

      g.checkPartnership(u, v);
      break;

    case 3:
      cout << "Enter airline ID: ";
      cin >> u;

      g.displayConnected(u);
      break;

    case 4:
      g.display();
      break;

    case 5:
      cout << "Chalo Bye!\n";
      break;

    default:
      cout << "Invalid Choice!\n";
    }

  } while (choice != 5);

  return 0;
}
*/