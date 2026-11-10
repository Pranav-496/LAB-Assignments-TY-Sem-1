/*
Develop a menu-driven C++ program to maintain an employee directory using an AVL tree. 
Each node should contain employee ID (key) and employee name (value) 
Perform the following operations:
1. insert a new employee record
2. search for an employee using their ID
3. delete an employee record
4. display employee records in sorted order (ascending, descending)
5. calculate and display the height of the AVL tree
6. determine the maximum number of comparisons required for searching any employee.
*/

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int id, ht;
    string name;
    Node *left, *right;

    Node(int i, string n) {
        id = i;
        name = n;
        ht = 1;
        left = right = NULL;
    }
};

class AVL {
public:
    Node *root;

    AVL() {
        root = NULL;
    }

    int height(Node *x) {
        if (x == NULL)
            return 0;

        return x->ht;
    }

    int balance(Node *x) {
        if (x == NULL)
            return 0;

        return height(x->left) - height(x->right);
    }

    void updateHeight(Node *x) {
        x->ht = 1 + max(height(x->left), height(x->right));
    }

    Node* rot_right(Node *x) {
        Node *y = x->left;
        Node *t = y->right;

        y->right = x;
        x->left = t;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* rot_left(Node *x) {
        Node *y = x->right;
        Node *t = y->left;

        y->left = x;
        x->right = t;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insert(Node *x, int id, string name, bool &inserted) {
        if (x == NULL) {
            inserted = true;
            return new Node(id, name);
        }

        if (id < x->id)
            x->left = insert(x->left, id, name, inserted);

        else if (id > x->id)
            x->right = insert(x->right, id, name, inserted);

        else {
            inserted = false;
            return x;
        }

        updateHeight(x);

        int bf = balance(x);

        // LL Case
        if (bf > 1 && id < x->left->id)
            return rot_right(x);

        // RR Case
        if (bf < -1 && id > x->right->id)
            return rot_left(x);

        // LR Case
        if (bf > 1 && id > x->left->id) {
            x->left = rot_left(x->left);
            return rot_right(x);
        }

        // RL Case
        if (bf < -1 && id < x->right->id) {
            x->right = rot_right(x->right);
            return rot_left(x);
        }

        return x;
    }

    Node* minNode(Node *x) {
        while (x->left != NULL)
            x = x->left;

        return x;
    }

    Node* deleteNode(Node *x, int id, bool &deleted) {
        if (x == NULL)
            return NULL;

        if (id < x->id)
            x->left = deleteNode(x->left, id, deleted);

        else if (id > x->id)
            x->right = deleteNode(x->right, id, deleted);

        else {
            deleted = true;

            // Zero or one child
            if (x->left == NULL || x->right == NULL) {
                Node *child = x->left ? x->left : x->right;
                delete x;
                return child;
            }

            // Two children
            Node *successor = minNode(x->right);

            x->id = successor->id;
            x->name = successor->name;

            bool temp = false;
            x->right = deleteNode(x->right, successor->id, temp);
        }

        updateHeight(x);

        int bf = balance(x);

        // LL Case
        if (bf > 1 && balance(x->left) >= 0)
            return rot_right(x);

        // LR Case
        if (bf > 1 && balance(x->left) < 0) {
            x->left = rot_left(x->left);
            return rot_right(x);
        }

        // RR Case
        if (bf < -1 && balance(x->right) <= 0)
            return rot_left(x);

        // RL Case
        if (bf < -1 && balance(x->right) > 0) {
            x->right = rot_right(x->right);
            return rot_left(x);
        }

        return x;
    }

    Node* search(Node *x, int id, int &comparisons) {
        while (x != NULL) {
            comparisons++;

            if (id == x->id)
                return x;

            if (id < x->id)
                x = x->left;
            else
                x = x->right;
        }

        return NULL;
    }

    void ascending(Node *x) {
        if (x == NULL)
            return;

        ascending(x->left);

        cout << x->id << " : " << x->name << endl;

        ascending(x->right);
    }

    void descending(Node *x) {
        if (x == NULL)
            return;

        descending(x->right);

        cout << x->id << " : " << x->name << endl;

        descending(x->left);
    }

    void insertEmployee(int id, string name) {
        bool inserted = false;
        root = insert(root, id, name, inserted);

        if (inserted)
            cout << "Employee inserted successfully!\n";
        else
            cout << "Employee ID already exists!\n";
    }

    void searchEmployee(int id) {
        int comparisons = 0;

        Node *temp = search(root, id, comparisons);

        if (temp != NULL) {
            cout << "Employee found!\n";
            cout << "Employee ID   : " << temp->id << endl;
            cout << "Employee Name : " << temp->name << endl;
        }
        else {
            cout << "Employee not found!\n";
        }

        cout << "Comparisons made: " << comparisons << endl;
    }

    void deleteEmployee(int id) {
        bool deleted = false;
        root = deleteNode(root, id, deleted);

        if (deleted)
            cout << "Employee deleted successfully!\n";
        else
            cout << "Employee ID not found!\n";
    }

    void displayHeight() {
        cout << "Height of AVL Tree: " << height(root) << endl;
    }

    void maxComparisons() {
        cout << "Maximum comparisons required: "
             << height(root) << endl;
    }
};

int main() {
    AVL t;

    int choice, id;
    string name;

    do {
        cout << "\n====== EMPLOYEE DIRECTORY USING AVL ======\n";
        cout << "1. Insert Employee\n";
        cout << "2. Search Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Display Ascending Order\n";
        cout << "5. Display Descending Order\n";
        cout << "6. Display Height\n";
        cout << "7. Maximum Search Comparisons\n";
        cout << "8. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter Employee ID: ";
            cin >> id;

            cout << "Enter Employee Name: ";
            cin >> ws;
            getline(cin, name);

            t.insertEmployee(id, name);
            break;

        case 2:
            cout << "Enter Employee ID to search: ";
            cin >> id;

            t.searchEmployee(id);
            break;

        case 3:
            cout << "Enter Employee ID to delete: ";
            cin >> id;

            t.deleteEmployee(id);
            break;

        case 4:
            cout << "\nEmployees in Ascending Order:\n";
            t.ascending(t.root);
            break;

        case 5:
            cout << "\nEmployees in Descending Order:\n";
            t.descending(t.root);
            break;

        case 6:
            t.displayHeight();
            break;

        case 7:
            t.maxComparisons();
            break;

        case 8:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 8);

    return 0;
}
