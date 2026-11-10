/*
write a menu-driven C++ program to construct an expression tree for a Boolean expression given in postfix form.
Perform the following operations:
1. traverse the tree in inorder, preorder, postorder, both recursively and non-recursively
2. evaluate the expression if the operands are numeric
3. convert and display the equivalent prefix and infix expressions
4. display the height of the expression tree
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
  return ch == '+' || ch == '-' || ch == '*' ||
         ch == '/' || ch == '^';
}

void destroy(Node *root)
{
  if (root == NULL)
    return;

  destroy(root->left);
  destroy(root->right);
  delete root;
}

// Construct tree from Postfix
Node *constructTree(vector<char> exp)
{
  stack<Node *> st;

  for (char ch : exp)
  {
    Node *temp = new Node(ch);

    if (isOperator(ch))
    {
      if (st.size() < 2)
      {
        delete temp;

        while (!st.empty())
        {
          destroy(st.top());
          st.pop();
        }

        return NULL;
      }

      temp->right = st.top();
      st.pop();

      temp->left = st.top();
      st.pop();
    }

    else if (ch < '0' || ch > '9')
    {
      delete temp;

      while (!st.empty())
      {
        destroy(st.top());
        st.pop();
      }

      return NULL;
    }

    st.push(temp);
  }

  if (st.size() != 1)
  {
    while (!st.empty())
    {
      destroy(st.top());
      st.pop();
    }

    return NULL;
  }

  Node *root = st.top();
  st.pop();

  return root;
}

// Recursive Inorder
void inorder(Node *root)
{
  if (root == NULL)
    return;

  inorder(root->left);
  cout << root->data << " ";
  inorder(root->right);
}

// Recursive Preorder
void preorder(Node *root)
{
  if (root == NULL)
    return;

  cout << root->data << " ";
  preorder(root->left);
  preorder(root->right);
}

// Recursive Postorder
void postorder(Node *root)
{
  if (root == NULL)
    return;

  postorder(root->left);
  postorder(root->right);
  cout << root->data << " ";
}

// Non-Recursive Inorder
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

// Non-Recursive Preorder
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

// Non-Recursive Postorder
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

// Evaluate Expression
double evaluate(Node *root)
{
  if (!isOperator(root->data))
    return root->data - '0';

  double left = evaluate(root->left);
  double right = evaluate(root->right);

  switch (root->data)
  {
  case '+':
    return left + right;

  case '-':
    return left - right;

  case '*':
    return left * right;

  case '/':
    if (right == 0)
      throw runtime_error("Division by zero!");
    return left / right;

  case '^':
    return pow(left, right);
  }

  return 0;
}

// Display Prefix
void prefix(Node *root)
{
  if (root == NULL)
    return;

  cout << root->data << " ";
  prefix(root->left);
  prefix(root->right);
}

// Display Infix
void infix(Node *root)
{
  if (root == NULL)
    return;

  if (isOperator(root->data))
    cout << "( ";

  infix(root->left);

  cout << root->data << " ";

  infix(root->right);

  if (isOperator(root->data))
    cout << ") ";
}

// Calculate Height
int height(Node *root)
{
  if (root == NULL)
    return 0;

  int lh = height(root->left);
  int rh = height(root->right);

  return 1 + max(lh, rh);
}

int main()
{
  Node *root = NULL;
  vector<char> exp;
  char ch;
  int choice;

  do
  {
    cout << "\n\n--- ARITHMETIC EXPRESSION TREE ---";
    cout << "\n1. Construct Tree";
    cout << "\n2. Inorder Recursive";
    cout << "\n3. Preorder Recursive";
    cout << "\n4. Postorder Recursive";
    cout << "\n5. Inorder Non-Recursive";
    cout << "\n6. Preorder Non-Recursive";
    cout << "\n7. Postorder Non-Recursive";
    cout << "\n8. Evaluate Expression";
    cout << "\n9. Display Prefix";
    cout << "\n10. Display Infix";
    cout << "\n11. Display Height";
    cout << "\n12. Exit";

    cout << "\nEnter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
      exp.clear();

      cout << "Enter postfix expression: ";

      while (cin >> ch && ch != '#')
        exp.push_back(ch);

      Node *newRoot = constructTree(exp);

      if (newRoot == NULL)
        cout << "Invalid postfix expression!";
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
      if (root == NULL)
        cout << "Tree is empty!";
      else
      {
        try
        {
          cout << "Result: " << evaluate(root);
        }
        catch (const exception &e)
        {
          cout << e.what();
        }
      }
      break;

    case 9:
      cout << "Prefix: ";
      prefix(root);
      break;

    case 10:
      cout << "Infix: ";
      infix(root);
      break;

    case 11:
      cout << "Height: " << height(root);
      break;

    case 12:
      cout << "Exiting...";
      break;

    default:
      cout << "Invalid choice!";
    }

  } while (choice != 12);

  destroy(root);
  return 0;
}
