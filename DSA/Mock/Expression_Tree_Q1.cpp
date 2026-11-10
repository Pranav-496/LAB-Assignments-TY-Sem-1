/*
write a menu-driven C++ program to construct an expression tree for a Boolean expression given in prefix form.
Perform the following operations:
1. construct and display the tree
2. traverse using inorder, preorder, and postorder, recursive and non-recursive
3. simplify the Boolean expression by applying logical laws
4. swap left and right subtrees.
*/

#include <bits/stdc++.h>
using namespace std;

struct Node
{
  char data;
  Node *left, *right;

  Node(char ch)
  {
    data = ch;
    left = right = NULL;
  }
};

bool isOperator(char ch)
{
  return ch == '&' || ch == '|' || ch == '!' || ch == '^';
}

void destroy(Node *root)
{
  if (root == NULL)
    return;

  destroy(root->left);
  destroy(root->right);
  delete root;
}

// Construct tree from Prefix
Node *constructTree(vector<char> exp)
{
  stack<Node *> st;

  for (int i = exp.size() - 1; i >= 0; i--)
  {
    Node *temp = new Node(exp[i]);

    if (isOperator(exp[i]))
    {
      if (st.empty())
      {
        delete temp;
        return NULL;
      }

      temp->left = st.top();
      st.pop();

      if (exp[i] != '!')
      {
        if (st.empty())
        {
          destroy(temp);
          return NULL;
        }

        temp->right = st.top();
        st.pop();
      }
    }

    st.push(temp);
  }

  if (st.size() != 1)
    return NULL;

  Node *root = st.top();
  st.pop();
  return root;
}

// Recursive traversals
void inorder(Node *root)
{
  if (root == NULL)
    return;

  inorder(root->left);
  cout << root->data << " ";
  inorder(root->right);
}

void preorder(Node *root)
{
  if (root == NULL)
    return;

  cout << root->data << " ";
  preorder(root->left);
  preorder(root->right);
}

void postorder(Node *root)
{
  if (root == NULL)
    return;

  postorder(root->left);
  postorder(root->right);
  cout << root->data << " ";
}

// Non-recursive Inorder
void inorderNR(Node *root)
{
  stack<Node *> st;
  Node *curr = root;

  while (curr != NULL || !st.empty())
  {
    while (curr != NULL)
    {
      st.push(curr);
      curr = curr->left;
    }

    curr = st.top();
    st.pop();

    cout << curr->data << " ";
    curr = curr->right;
  }
}

// Non-recursive Preorder
void preorderNR(Node *root)
{
  if (root == NULL)
    return;

  stack<Node *> st;
  st.push(root);

  while (!st.empty())
  {
    Node *curr = st.top();
    st.pop();

    cout << curr->data << " ";

    if (curr->right)
      st.push(curr->right);
    if (curr->left)
      st.push(curr->left);
  }
}

// Non-recursive Postorder
void postorderNR(Node *root)
{
  if (root == NULL)
    return;

  stack<Node *> s1, s2;
  s1.push(root);

  while (!s1.empty())
  {
    Node *curr = s1.top();
    s1.pop();

    s2.push(curr);

    if (curr->left)
      s1.push(curr->left);
    if (curr->right)
      s1.push(curr->right);
  }

  while (!s2.empty())
  {
    cout << s2.top()->data << " ";
    s2.pop();
  }
}

// Compare two subtrees
bool sameTree(Node *a, Node *b)
{
  if (a == NULL && b == NULL)
    return true;
  if (a == NULL || b == NULL)
    return false;

  return a->data == b->data &&
         sameTree(a->left, b->left) &&
         sameTree(a->right, b->right);
}

// Simplify Boolean Expression
Node *simplify(Node *root)
{
  if (root == NULL)
    return NULL;

  root->left = simplify(root->left);
  root->right = simplify(root->right);

  char op = root->data;
  Node *a = root->left;
  Node *b = root->right;

  // NOT operation
  if (op == '!')
  {
    if (a->data == '0' || a->data == '1')
    {
      char val = (a->data == '0') ? '1' : '0';
      destroy(root);
      return new Node(val);
    }

    if (a->data == '!')
    {
      Node *temp = a->left;
      a->left = NULL;
      root->left = NULL;
      delete a;
      delete root;
      return temp;
    }
  }

  if (op == '&' || op == '|')
  {
    bool isAnd = (op == '&');

    // Same operands: A&A=A, A|A=A
    if (sameTree(a, b))
    {
      root->left = root->right = NULL;
      delete b;
      delete root;
      return a;
    }

    // Constant on left
    if (a->data == '0' || a->data == '1')
    {
      if ((isAnd && a->data == '0') ||
          (!isAnd && a->data == '1'))
      {
        destroy(root);
        return new Node(isAnd ? '0' : '1');
      }

      root->left = NULL;
      root->right = NULL;
      delete root;
      delete a;
      return b;
    }

    // Constant on right
    if (b->data == '0' || b->data == '1')
    {
      if ((isAnd && b->data == '0') ||
          (!isAnd && b->data == '1'))
      {
        destroy(root);
        return new Node(isAnd ? '0' : '1');
      }

      root->left = NULL;
      root->right = NULL;
      delete root;
      delete b;
      return a;
    }
  }

  // XOR simplification
  if (op == '^')
  {
    if (sameTree(a, b))
    {
      destroy(root);
      return new Node('0');
    }

    if (a->data == '0')
    {
      root->left = root->right = NULL;
      delete root;
      delete a;
      return b;
    }

    if (b->data == '0')
    {
      root->left = NULL;
      root->right = NULL;
      delete root;
      delete b;
      return a;
    }

    if (a->data == '1')
    {
      root->data = '!';
      root->left = b;
      root->right = NULL;
      delete a;
      return root;
    }

    if (b->data == '1')
    {
      root->data = '!';
      root->right = NULL;
      delete b;
      return root;
    }
  }

  return root;
}

// Mirror tree
void mirror(Node *root)
{
  if (root == NULL)
    return;

  swap(root->left, root->right);

  mirror(root->left);
  mirror(root->right);
}

int main()
{
  Node *root = NULL;
  vector<char> exp;
  string input;
  int choice;

  do
  {
    cout << "\n\n--- BOOLEAN EXPRESSION TREE ---";
    cout << "\n1. Construct Tree";
    cout << "\n2. Inorder Recursive";
    cout << "\n3. Preorder Recursive";
    cout << "\n4. Postorder Recursive";
    cout << "\n5. Inorder Non-Recursive";
    cout << "\n6. Preorder Non-Recursive";
    cout << "\n7. Postorder Non-Recursive";
    cout << "\n8. Simplify Expression";
    cout << "\n9. Mirror Tree";
    cout << "\n10. Exit";

    cout << "\nEnter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
      cout << "Enter prefix expression: ";
      cin >> input;

      exp.clear();

      for (char ch : input)
        exp.push_back(ch);

      Node *newRoot = constructTree(exp);

      if (newRoot == NULL)
        cout << "Invalid expression!";
      else
      {
        destroy(root);
        root = newRoot;
        cout << "Tree constructed successfully!";
      }
      break;
    }

    case 2:
      cout << "Inorder: ";
      inorder(root);
      break;

    case 3:
      cout << "Preorder: ";
      preorder(root);
      break;

    case 4:
      cout << "Postorder: ";
      postorder(root);
      break;

    case 5:
      cout << "Inorder: ";
      inorderNR(root);
      break;

    case 6:
      cout << "Preorder: ";
      preorderNR(root);
      break;

    case 7:
      cout << "Postorder: ";
      postorderNR(root);
      break;

    case 8:
      if (root != NULL)
      {
        root = simplify(root);
        cout << "Expression simplified!";
      }
      break;

    case 9:
      mirror(root);
      cout << "Tree mirrored!";
      break;

    case 10:
      cout << "Exiting...";
      break;

    default:
      cout << "Invalid choice!";
    }

  } while (choice != 10);

  destroy(root);
  return 0;
}
