/*
Each user in a social network is connected to the others via "friend" relationships.
If user A and user B are friends, an undirected edge exists between them.
Write a menu-driven C++ program to represent this social network using both adjacency matrix and adjacency list.
The program should:
- Check if two users are directly connected
- Display all friends of a given user.
*/

// Adjacency List

#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
  int n;
  vector<int> adj[10];

  Graph(int size)
  {
    n = size;
  }

  void addFriend(int u, int v)
  {
    adj[u].push_back(v);
    adj[v].push_back(u);

    cout << "Friendship added successfully.\n";
  }

  void checkFriend(int u, int v)
  {
    for (int x : adj[u])
    {
      if (x == v)
      {
        cout << "Users are friends.\n";
        return;
      }
    }

    cout << "Users are not friends.\n";
  }

  void displayFriends(int u)
  {
    cout << "Friends of User " << u << ": ";

    for (int x : adj[u])
      cout << x << " ";

    cout << endl;
  }

  void display()
  {
    cout << "\nAdjacency List:\n";

    for (int i = 0; i < n; i++)
    {
      cout << i << " -> ";

      for (int x : adj[i])
        cout << x << " -> ";

      cout << "NULL\n";
    }
  }
};

int main()
{
  int n, choice, u, v;

  cout << "Enter number of users: ";
  cin >> n;

  Graph g(n);

  do
  {
    cout << "\n------ MENU ------\n";
    cout << "1. Add Friendship\n";
    cout << "2. Check Friendship\n";
    cout << "3. Display Friends of User\n";
    cout << "4. Display Adjacency List\n";
    cout << "5. Exit\n";

    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter two user IDs: ";
      cin >> u >> v;
      g.addFriend(u, v);
      break;

    case 2:
      cout << "Enter two user IDs: ";
      cin >> u >> v;
      g.checkFriend(u, v);
      break;

    case 3:
      cout << "Enter user ID: ";
      cin >> u;
      g.displayFriends(u);
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

    void addFriend(int u, int v)
    {
        mat[u][v] = 1;
        mat[v][u] = 1;

        cout << "Friendship added successfully.\n";
    }

    void checkFriend(int u, int v)
    {
        if (mat[u][v] == 1)
            cout << "Users are friends.\n";
        else
            cout << "Users are not friends.\n";
    }

    void displayFriends(int u)
    {
        cout << "Friends of User " << u << ": ";

        for (int i = 0; i < n; i++)
        {
            if (mat[u][i] == 1)
                cout << i << " ";
        }

        cout << endl;
    }

    void display()
    {
        cout << "\nAdjacency Matrix:\n";

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << mat[i][j] << " ";

            cout << endl;
        }
    }
};

int main()
{
    int n, choice, u, v;

    cout << "Enter number of users: ";
    cin >> n;

    Graph g(n);

    do
    {
        cout << "\n------ MENU ------\n";
        cout << "1. Add Friendship\n";
        cout << "2. Check Friendship\n";
        cout << "3. Display Friends of User\n";
        cout << "4. Display Adjacency Matrix\n";
        cout << "5. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter two user IDs: ";
            cin >> u >> v;
            g.addFriend(u, v);
            break;

        case 2:
            cout << "Enter two user IDs: ";
            cin >> u >> v;
            g.checkFriend(u, v);
            break;

        case 3:
            cout << "Enter user ID: ";
            cin >> u;
            g.displayFriends(u);
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