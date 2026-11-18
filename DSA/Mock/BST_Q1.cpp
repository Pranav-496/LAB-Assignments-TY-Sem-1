/*
Develop a menu-driven C++ program to manage patient records in a hospital using binary search tree, where each node stores patient ID and name.
After constructing the BST, perform:
1. insert new patient
2. search for the patient using ID
3. display all patient records in sorted order in-order traversal
4. find the minimum and maximum patient ID 
5. display the number of nodes, leaf nodes, and height of the tree
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Node
{
public:
    int id;
    string name;
    Node *left;
    Node *right;

    Node(int patientID, string patientName)
    {
        id = patientID;
        name = patientName;
        left = NULL;
        right = NULL;
    }
};

class BST
{
public:
    Node *root;

    BST()
    {
        root = NULL;
    }

    // Insert a new patient into the BST
    Node *insert(Node *root, int id, string name)
    {
        if (root == NULL)
            return new Node(id, name);

        if (id < root->id)
            root->left = insert(root->left, id, name);
        else if (id > root->id)
            root->right = insert(root->right, id, name);
        else
            cout << "Duplicate Patient ID not allowed.\n";

        return root;
    }

    // Search for a patient by ID
    Node *search(Node *root, int id)
    {
        if (root == NULL || root->id == id)
            return root;

        if (id < root->id)
            return search(root->left, id);

        return search(root->right, id);
    }

    // In-order traversal (ascending order)
    void display(Node *root)
    {
        if (root == NULL)
            return;

        display(root->left);
        cout << "Patient ID: " << root->id << " | Name: " << root->name << endl;
        display(root->right);
    }

    // Find patient with minimum ID (leftmost node)
    void findMin(Node *root)
    {
        if (root == NULL)
        {
            cout << "BST is empty.\n";
            return;
        }

        while (root->left != NULL)
            root = root->left;

        cout << "Minimum Patient ID: " << root->id << " | Name: " << root->name << endl;
    }

    // Find patient with maximum ID (rightmost node)
    void findMax(Node *root)
    {
        if (root == NULL)
        {
            cout << "BST is empty.\n";
            return;
        }

        while (root->right != NULL)
            root = root->right;

        cout << "Maximum Patient ID: " << root->id << " | Name: " << root->name << endl;
    }

    // Count total number of nodes
    int totalNodes(Node *root)
    {
        if (root == NULL)
            return 0;

        return 1 + totalNodes(root->left) + totalNodes(root->right);
    }

    // Count leaf nodes (nodes with 0 children)
    int leafNodes(Node *root)
    {
        if (root == NULL)
            return 0;

        if (root->left == NULL && root->right == NULL)
            return 1;

        return leafNodes(root->left) + leafNodes(root->right);
    }

    // Find height of the BST
    int height(Node *root)
    {
        if (root == NULL)
            return 0;

        return 1 + max(height(root->left), height(root->right));
    }
};

int main()
{
    BST tree;
    int choice, id;
    string name;

    do
    {
        cout << "\n====== HOSPITAL PATIENT MANAGEMENT ======\n";
        cout << "1. Create BST (Multiple Patients)\n";
        cout << "2. Insert New Patient\n";
        cout << "3. Search Patient by ID\n";
        cout << "4. Display All Patient Records (Inorder)\n";
        cout << "5. Find Minimum Patient ID\n";
        cout << "6. Find Maximum Patient ID\n";
        cout << "7. Count Total Patients\n";
        cout << "8. Count Leaf Nodes\n";
        cout << "9. Find Height of BST\n";
        cout << "10. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int n;
            cout << "Enter number of patients: ";
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                cout << "Enter Patient ID: ";
                cin >> id;

                cout << "Enter Patient Name: ";
                cin >> ws;
                getline(cin, name);

                tree.root = tree.insert(tree.root, id, name);
            }
            cout << "BST created successfully.\n";
            break;
        }

        case 2:
            cout << "Enter Patient ID: ";
            cin >> id;

            cout << "Enter Patient Name: ";
            cin >> ws;
            getline(cin, name);

            tree.root = tree.insert(tree.root, id, name);
            cout << "Patient record processed.\n";
            break;

        case 3:
        {
            cout << "Enter Patient ID to search: ";
            cin >> id;

            Node *temp = tree.search(tree.root, id);
            if (temp != NULL)
            {
                cout << "\nPatient Found!\n";
                cout << "Patient ID   : " << temp->id << endl;
                cout << "Patient Name : " << temp->name << endl;
            }
            else
            {
                cout << "Patient record not found.\n";
            }
            break;
        }

        case 4:
            if (tree.root == NULL)
                cout << "No patient records available.\n";
            else
            {
                cout << "\nPatient Records in Ascending Order:\n";
                tree.display(tree.root);
            }
            break;

        case 5:
            tree.findMin(tree.root);
            break;

        case 6:
            tree.findMax(tree.root);
            break;

        case 7:
            cout << "Total Patients: " << tree.totalNodes(tree.root) << endl;
            break;

        case 8:
            cout << "Leaf Nodes: " << tree.leafNodes(tree.root) << endl;
            break;

        case 9:
            cout << "Height of BST: " << tree.height(tree.root) << endl;
            break;

        case 10:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 10);

    return 0;
}
