/*
Different airlines share partnerships with each other, allowing code sharing flights.
If airline A has partnership with airline B, there is an edge between them.
The edge weight can represent number of shared routes or partnership strength.
Write a C++ program to represent this network using adjacency list and matrix.
The program should:
1. Check if two airlines have a direct partnership or a path through one intermediate airline
2. Display all airlines connected with a given airline
*/

// Adjacency List

#include <bits/stdc++.h>
using namespace std;

struct Node
{
  int vertex;
  int weight;
  Node *next;
};

class Graph
{
  Node *adj[10];
  int n;

public:
  Graph(int vertices)
  {
    n = vertices;

    for (int i = 0; i < n; i++)
      adj[i] = NULL;
  }

  void addPartnership(int u, int v, int w)
  {
    Node *newNode = new Node{v, w, adj[u]};
    adj[u] = newNode;

    newNode = new Node{u, w, adj[v]};
    adj[v] = newNode;

    cout << "Partnership added.\n";
  }

  void checkPartnership(int u, int v)
  {
    Node *temp = adj[u];

    while (temp != NULL)
    {
      if (temp->vertex == v)
      {
        cout << "Direct partnership exists.\n";
        cout << "Strength = " << temp->weight << endl;
        return;
      }

      temp = temp->next;
    }

    temp = adj[u];

    while (temp != NULL)
    {
      int mid = temp->vertex;
      Node *temp2 = adj[mid];

      while (temp2 != NULL)
      {
        if (temp2->vertex == v)
        {
          cout << "Indirect path exists.\n";
          cout << u << " -> " << mid << " -> " << v << endl;
          cout << "Combined strength = "
               << temp->weight + temp2->weight << endl;
          return;
        }

        temp2 = temp2->next;
      }

      temp = temp->next;
    }

    cout << "No path exists.\n";
  }

  void displayConnections(int u)
  {
    Node *temp = adj[u];

    cout << "Airline " << u << " connections:\n";

    if (temp == NULL)
      cout << "No connections\n";

    while (temp != NULL)
    {
      cout << "Airline " << temp->vertex
           << " (Strength: " << temp->weight << ")\n";

      temp = temp->next;
    }
  }

  void display()
  {
    cout << "\nWeighted Adjacency List:\n";

    for (int i = 0; i < n; i++)
    {
      cout << i << " -> ";
      Node *temp = adj[i];

      while (temp != NULL)
      {
        cout << "(" << temp->vertex
             << ", " << temp->weight << ") -> ";

        temp = temp->next;
      }

      cout << "NULL\n";
    }
  }
};

int main()
{
  int n, choice, u, v, w;

  cout << "Enter number of airlines: ";
  cin >> n;

  Graph g(n);

  do
  {
    cout << "\n1. Add Partnership";
    cout << "\n2. Check Partnership";
    cout << "\n3. Display Connected Airlines";
    cout << "\n4. Display Adjacency List";
    cout << "\n5. Exit";
    cout << "\nEnter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter two airline IDs and partnership strength: ";
      cin >> u >> v >> w;
      g.addPartnership(u, v, w);
      break;

    case 2:
      cout << "Enter two airline IDs: ";
      cin >> u >> v;

      g.checkPartnership(u, v);
      break;

    case 3:
      cout << "Enter airline ID: ";
      cin >> u;
      g.displayConnections(u);
      break;

    case 4:
      g.display();
      break;

    case 5:
      cout << "Exiting...\n";
      break;

    default:
      cout << "Invalid choice!\n";
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
      cout << "Direct partnership exists.\n";
      cout << "Strength = " << mat[u][v] << endl;
      return;
    }

    for (int mid = 0; mid < n; mid++)
    {
      if (mat[u][mid] != 0 && mat[mid][v] != 0)
      {
        cout << "Indirect path exists.\n";
        cout << u << " -> " << mid << " -> " << v << endl;
        cout << "Combined strength = "
             << mat[u][mid] + mat[mid][v] << endl;
        return;
      }
    }

    cout << "No path exists.\n";
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