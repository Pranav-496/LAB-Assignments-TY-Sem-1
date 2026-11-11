/*
Each user in a social network is connected to the others via "friend" relationships.
If user A and user B are friends, an undirected edge exists between them.
Write a menu-driven C++ program to represent this social network using both adjacency matrix and adjacency list.
The program should:
- Check if two users are connected directly or through one intermediate user
- Display all friends of a given user.
*/

// Adjacency List

#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int vertex;
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

    void addFriend(int u, int v)
    {
        Node *newNode = new Node{v, adj[u]};
        adj[u] = newNode;

        newNode = new Node{u, adj[v]};
        adj[v] = newNode;

        cout << "Friendship added.\n";
    }

    void checkFriend(int u, int v)
    {
        Node *temp = adj[u];
        while (temp != NULL)
        {
            if (temp->vertex == v)
            {
                cout << "Direct connection exists.\n";
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
                    cout << "Indirect connection exists.\n";
                    cout << u << " -> " << mid << " -> " << v << endl;
                    return;
                }

                temp2 = temp2->next;
            }

            temp = temp->next;
        }

        cout << "No connection exists.\n";
    }

    void displayFriends(int u)
    {
        Node *temp = adj[u];

        cout << "Friends of User " << u << ": ";

        if (temp == NULL)
            cout << "No friends";

        while (temp != NULL)
        {
            cout << temp->vertex << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    void display()
    {
        cout << "\nAdjacency List:\n";

        for (int i = 0; i < n; i++)
        {
            cout << i << " -> ";
            Node *temp = adj[i];

            while (temp != NULL)
            {
                cout << temp->vertex << " -> ";
                temp = temp->next;
            }

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
        cout << "\n1. Add Friendship";
        cout << "\n2. Check Friendship";
        cout << "\n3. Display Friends";
        cout << "\n4. Display Adjacency List";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
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

    void addFriend(int u, int v)
    {
        mat[u][v] = 1;
        mat[v][u] = 1;

        cout << "Friendship added successfully.\n";
    }

    void checkFriend(int u, int v)
    {
        if (mat[u][v] == 1)
        {
            cout << "Direct connection exists.\n";
            return;
        }

        for (int mid = 0; mid < n; mid++)
        {
            if (mat[u][mid] == 1 && mat[mid][v] == 1)
            {
                cout << "Indirect connection exists.\n";
                cout << u << " -> " << mid << " -> " << v << endl;
                return;
            }
        }

        cout << "No connection exists.\n";
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