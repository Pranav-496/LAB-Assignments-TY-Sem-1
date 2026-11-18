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

#include <iostream>
#include <string>
#include <algorithm>
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

    int height(Node *root) {
        if (root == NULL)
            return 0;

        return 1 + max(height(root->left), height(root->right));
    }

    int balance(Node *x) {
        if (x == NULL)
            return 0;

        return height(x->left) - height(x->right);
    }

    Node* rot_right(Node *x) {
        Node *y = x->left;
        Node *t = y->right;

        y->right = x;
        x->left = t;

        x->ht = height(x);
        y->ht = height(y);

        return y;
    }

    Node* rot_left(Node *x) {
        Node *y = x->right;
        Node *t = y->left;

        y->left = x;
        x->right = t;

        x->ht = height(x);
        y->ht = height(y);

        return y;
    }

    Node* ll(Node *x) {
        return rot_right(x);
    }

    Node* rr(Node *x) {
        return rot_left(x);
    }

    Node* lr(Node *x) {
        x->left = rot_left(x->left);
        return rot_right(x);
    }

    Node* rl(Node *x) {
        x->right = rot_right(x->right);
        return rot_left(x);
    }

    Node* insert(Node *x, int id, string name) {
        if (x == NULL)
            return new Node(id, name);

        if (id < x->id)
            x->left = insert(x->left, id, name);
        else if (id > x->id)
            x->right = insert(x->right, id, name);
        else {
            cout << "Employee ID already exists!\n";
            return x;
        }

        x->ht = height(x);

        int bf = balance(x);

        // LL Case
        if (bf > 1 && id < x->left->id)
            return ll(x);

        // LR Case
        if (bf > 1 && id > x->left->id)
            return lr(x);

        // RR Case
        if (bf < -1 && id > x->right->id)
            return rr(x);

        // RL Case
        if (bf < -1 && id < x->right->id)
            return rl(x);

        return x;
    }

    Node* deleteNode(Node *x, int id) {
        if (x == NULL)
            return NULL;

        if (id < x->id)
            x->left = deleteNode(x->left, id);
        else if (id > x->id)
            x->right = deleteNode(x->right, id);
        else {
            // Node with 0 or 1 child
            if (x->left == NULL) {
                Node *temp = x->right;
                delete x;
                return temp;
            }
            else if (x->right == NULL) {
                Node *temp = x->left;
                delete x;
                return temp;
            }

            // Node with 2 children: get In-order Successor
            Node *successor = x->right;
            while (successor->left != NULL)
                successor = successor->left;

            x->id = successor->id;
            x->name = successor->name;

            x->right = deleteNode(x->right, successor->id);
        }

        x->ht = height(x);

        int bf = balance(x);

        // LL Case
        if (bf > 1 && balance(x->left) >= 0)
            return ll(x);

        // LR Case
        if (bf > 1 && balance(x->left) < 0)
            return lr(x);

        // RR Case
        if (bf < -1 && balance(x->right) <= 0)
            return rr(x);

        // RL Case
        if (bf < -1 && balance(x->right) > 0)
            return rl(x);

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

            t.root = t.insert(t.root, id, name);
            cout << "Employee record processed.\n";
            break;

        case 2: {
            cout << "Enter Employee ID to search: ";
            cin >> id;

            int comparisons = 0;
            Node *temp = t.search(t.root, id, comparisons);

            if (temp != NULL) {
                cout << "Employee found!\n";
                cout << "Employee ID   : " << temp->id << endl;
                cout << "Employee Name : " << temp->name << endl;
                cout << "Comparisons made: " << comparisons << endl;
            }
            else {
                cout << "Employee not found!\n";
            }
            break;
        }

        case 3: {
            cout << "Enter Employee ID to delete: ";
            cin >> id;

            int dummy = 0;
            if (t.search(t.root, id, dummy) != NULL) {
                t.root = t.deleteNode(t.root, id);
                cout << "Employee deleted successfully!\n";
            }
            else {
                cout << "Employee ID not found!\n";
            }
            break;
        }

        case 4:
            cout << "\nEmployees in Ascending Order:\n";
            t.ascending(t.root);
            break;

        case 5:
            cout << "\nEmployees in Descending Order:\n";
            t.descending(t.root);
            break;

        case 6:
            cout << "Height of AVL Tree: " << t.height(t.root) << endl;
            break;

        case 7:
            cout << "Maximum comparisons required: " << t.height(t.root) << endl;
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
