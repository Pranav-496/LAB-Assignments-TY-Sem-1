/*
Develop a menu-driven C++ program to manage patient records in a hospital using binary search tree, where each node stores patient ID and name.
After constructing the BST, perform:
1. insert new patient
2. search for the patient using ID
3. display all patient records in sorted order in-order traversal
4. find the minimum and maximum patient ID 
5. display the number of nodes, leaf nodes, and height of the tree
*/
#include <bits/stdc++.h>
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
private:
    Node *root;

    Node *insertNode(Node *, int, string);
    Node *searchNode(Node *, int);

    int countNodes(Node *);
    int countLeaf(Node *);
    int heightRec(Node *);

public:
    BST()
    {
        root = NULL;
    }

    Node *getRoot()
    {
        return root;
    }

    void create();
    void insertPatient();
    void searchPatient();

    void display(Node *);
    void findMin(Node *);
    void findMax(Node *);

    int totalNodes(Node *);
    int leafNodes(Node *);
    int height(Node *);
};

// TC: O(h)  SC: O(h)
Node *BST::insertNode(Node *root, int id, string name)
{
    if (root == NULL)
        return new Node(id, name);

    if (id < root->id)
        root->left = insertNode(root->left, id, name);

    else if (id > root->id)
        root->right = insertNode(root->right, id, name);

    else
        cout << "Duplicate Patient ID not allowed.\n";

    return root;
}

// TC: O(n log n) average for n insertions
void BST::create()
{
    int n, id;
    string name;

    cout << "Enter number of patients: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Patient ID: ";
        cin >> id;

        cout << "Enter Patient Name: ";
        cin >> ws;
        getline(cin, name);

        root = insertNode(root, id, name);
    }
}

// TC: O(h)  SC: O(h)
void BST::insertPatient()
{
    int id;
    string name;

    cout << "Enter Patient ID: ";
    cin >> id;

    cout << "Enter Patient Name: ";
    cin >> ws;
    getline(cin, name);

    Node *temp = searchNode(root, id);

    if (temp != NULL)
    {
        cout << "Patient ID already exists.\n";
        return;
    }

    root = insertNode(root, id, name);

    cout << "Patient record inserted successfully.\n";
}

// TC: O(h)  SC: O(h)
Node *BST::searchNode(Node *root, int id)
{
    if (root == NULL || root->id == id)
        return root;

    if (id < root->id)
        return searchNode(root->left, id);

    return searchNode(root->right, id);
}

// TC: O(h)  SC: O(h)
void BST::searchPatient()
{
    int id;

    cout << "Enter Patient ID to search: ";
    cin >> id;

    Node *temp = searchNode(root, id);

    if (temp == NULL)
        cout << "Patient record not found.\n";
    else
    {
        cout << "\nPatient Found!\n";
        cout << "Patient ID: " << temp->id << endl;
        cout << "Patient Name: " << temp->name << endl;
    }
}

// Inorder traversal - ascending order
// TC: O(n)  SC: O(h)
void BST::display(Node *root)
{
    if (root == NULL)
        return;

    display(root->left);

    cout << "Patient ID: " << root->id
         << " | Name: " << root->name << endl;

    display(root->right);
}

// TC: O(h)  SC: O(1)
void BST::findMin(Node *root)
{
    if (root == NULL)
    {
        cout << "BST is empty.\n";
        return;
    }

    while (root->left != NULL)
        root = root->left;

    cout << "Minimum Patient ID: " << root->id
         << " | Name: " << root->name << endl;
}

// TC: O(h)  SC: O(1)
void BST::findMax(Node *root)
{
    if (root == NULL)
    {
        cout << "BST is empty.\n";
        return;
    }

    while (root->right != NULL)
        root = root->right;

    cout << "Maximum Patient ID: " << root->id
         << " | Name: " << root->name << endl;
}

// TC: O(n)  SC: O(h)
int BST::countNodes(Node *root)
{
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left)
             + countNodes(root->right);
}

int BST::totalNodes(Node *root)
{
    return countNodes(root);
}

// TC: O(n)  SC: O(h)
int BST::countLeaf(Node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeaf(root->left) + countLeaf(root->right);
}

int BST::leafNodes(Node *root)
{
    return countLeaf(root);
}

// TC: O(n)  SC: O(h)
int BST::heightRec(Node *root)
{
    if (root == NULL)
        return 0;

    return 1 + max(heightRec(root->left),
                   heightRec(root->right));
}

int BST::height(Node *root)
{
    return heightRec(root);
}

int main()
{
    BST tree;
    int choice;

    do
    {
        cout << "\n====== HOSPITAL PATIENT MANAGEMENT ======\n";

        cout << "1. Create BST\n";
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
            tree.create();
            break;

        case 2:
            tree.insertPatient();
            break;

        case 3:
            tree.searchPatient();
            break;

        case 4:
            if (tree.getRoot() == NULL)
                cout << "No patient records available.\n";
            else
            {
                cout << "\nPatient Records in Ascending Order:\n";
                tree.display(tree.getRoot());
            }
            break;

        case 5:
            tree.findMin(tree.getRoot());
            break;

        case 6:
            tree.findMax(tree.getRoot());
            break;

        case 7:
            cout << "Total Patients: "
                 << tree.totalNodes(tree.getRoot()) << endl;
            break;

        case 8:
            cout << "Leaf Nodes: "
                 << tree.leafNodes(tree.getRoot()) << endl;
            break;

        case 9:
            cout << "Height of BST: "
                 << tree.height(tree.getRoot()) << endl;
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
