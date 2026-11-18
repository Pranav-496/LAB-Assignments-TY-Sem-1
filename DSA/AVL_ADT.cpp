#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    string key, mean;
    node *left, *right;
    int ht;
};

class tree
{
public:
    node *root;

    tree()
    {
        root = NULL;
    }

    node *rot_right(node *x);
    node *rot_left(node *x);

    node *ll(node *x);
    node *lr(node *x);
    node *rr(node *x);
    node *rl(node *x);

    int height(node *x);
    int bf(node *x);

    node *insert(node *root, string newKey, string newMean);
    node *deleteNode(node *root, string key);
    node *search(node *root, string key);

    void ascending(node *root);
    void descending(node *root);
};

node *tree::rot_right(node *x)
{
    node *y;

    y = x->left;
    x->left = y->right;
    y->right = x;

    x->ht = height(x);
    y->ht = height(y);

    return y;
}

node *tree::rot_left(node *x)
{
    node *y;

    y = x->right;
    x->right = y->left;
    y->left = x;

    x->ht = height(x);
    y->ht = height(y);

    return y;
}

int tree::height(node *x)
{
    if (x == nullptr)
        return 0;

    return 1 + max(height(x->left), height(x->right));
}

int tree::bf(node *x)
{
    if (!x)
        return 0;

    return height(x->left) - height(x->right);
}

node *tree::rr(node *x)
{
    x = rot_left(x);
    return x;
}

node *tree::rl(node *x)
{
    x->right = rot_right(x->right);
    x = rot_left(x);

    return x;
}

node *tree::ll(node *x)
{
    x = rot_right(x);
    return x;
}

node *tree::lr(node *x)
{
    x->left = rot_left(x->left);
    x = rot_right(x);

    return x;
}

node *tree::insert(node *root, string newKey, string newMean)
{
    if (!root)
    {
        node *curr = new node;

        curr->key = newKey;
        curr->mean = newMean;
        curr->ht = 1;
        curr->left = NULL;
        curr->right = NULL;

        return curr;
    }

    if (newKey < root->key)
    {
        root->left = insert(root->left, newKey, newMean);
    }
    else if (newKey > root->key)
    {
        root->right = insert(root->right, newKey, newMean);
    }
    else
    {
        cout << "Duplicate key not allowed!\n";
        return root;
    }

    // Update height
    root->ht = height(root);

    // Check balance
    if (bf(root) == 2)
    {
        // LL Case
        if (newKey < root->left->key)
        {
            root = ll(root);
        }
        // LR Case
        else
        {
            root = lr(root);
        }
    }
    else if (bf(root) == -2)
    {
        // RR Case
        if (newKey > root->right->key)
        {
            root = rr(root);
        }
        // RL Case
        else
        {
            root = rl(root);
        }
    }

    return root;
}

node *tree::deleteNode(node *root, string key)
{
    if (!root)
        return NULL;

    if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        if (!root->left || !root->right)
        {
            node *child = root->left ? root->left : root->right;
            delete root;
            return child;
        }

        node *successor = root->right;
        while (successor->left)
            successor = successor->left;

        root->key = successor->key;
        root->mean = successor->mean;
        root->right = deleteNode(root->right, successor->key);
    }

    root->ht = height(root);

    if (bf(root) > 1)
    {
        if (bf(root->left) >= 0)
            return ll(root);
        return lr(root);
    }
    if (bf(root) < -1)
    {
        if (bf(root->right) <= 0)
            return rr(root);
        return rl(root);
    }

    return root;
}

node *tree::search(node *root, string key)
{
    if (root == NULL)
        return NULL;

    if (key == root->key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

void tree::ascending(node *root)
{
    if (root == NULL)
        return;

    ascending(root->left);

    cout << root->key << " : " << root->mean << endl;

    ascending(root->right);
}

void tree::descending(node *root)
{
    if (root == NULL)
        return;

    descending(root->right);

    cout << root->key << " : " << root->mean << endl;

    descending(root->left);
}

int main()
{
    tree t;

    int choice;
    string key, mean;

    do
    {
        cout << "\n========== AVL DICTIONARY ==========\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Display Ascending\n";
        cout << "4. Display Descending\n";
        cout << "5. Delete\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter key: ";
            cin >> key;

            cout << "Enter meaning: ";
            cin >> mean;

            t.root = t.insert(t.root, key, mean);

            cout << "Key inserted successfully.\n";
            break;

        case 2:
        {
            cout << "Enter key to search: ";
            cin >> key;

            node *temp = t.search(t.root, key);

            if (temp != NULL)
            {
                cout << "Key found!\n";
                cout << "Key     : " << temp->key << endl;
                cout << "Meaning : " << temp->mean << endl;
            }
            else
            {
                cout << "Key not found.\n";
            }

            break;
        }

        case 3:
            cout << "\nDictionary in Ascending Order:\n";
            t.ascending(t.root);
            break;

        case 4:
            cout << "\nDictionary in Descending Order:\n";
            t.descending(t.root);
            break;

        case 5:
            cout << "Enter key to delete: ";
            cin >> key;

            if (t.search(t.root, key) != NULL)
            {
                t.root = t.deleteNode(t.root, key);
                cout << "Key deleted successfully.\n";
            }
            else
            {
                cout << "Key not found.\n";
            }
            break;

        case 6:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}