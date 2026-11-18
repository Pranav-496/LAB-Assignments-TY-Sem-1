/*
Write a menu-driven C++ program to construct an expression tree for an expression given in postfix form (e.g., 45+2* or AB+C*D-).
Perform the following operations:
1. Traverse the tree in inorder, preorder, postorder, both recursively and non-recursively
2. Evaluate the expression if the operands are numeric
3. Convert and display equivalent prefix and infix expressions
4. Display the height of the expression tree
*/

#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <algorithm>
using namespace std;

struct Node
{
  char data;
  Node *left;
  Node *right;

  Node(char ch)
  {
    data = ch;
    left = right = NULL;
  }
};

bool isOperator(char ch)
{
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Construct Expression Tree from Postfix expression
Node *create(string exp)
{
  stack<Node *> s;

  for (char ch : exp)
  {
    Node *newNode = new Node(ch);

    if (!isOperator(ch))
    {
      s.push(newNode);
    }
    else
    {
      // In postfix, the first popped is right child, second is left child
      newNode->right = s.top();
      s.pop();

      newNode->left = s.top();
      s.pop();

      s.push(newNode);
    }
  }

  return s.top();
}

// Recursive Traversals
void inorder(Node *root)
{
  if (!root) return;
  inorder(root->left);
  cout << root->data << " ";
  inorder(root->right);
}

void preorder(Node *root)
{
  if (!root) return;
  cout << root->data << " ";
  preorder(root->left);
  preorder(root->right);
}

void postorder(Node *root)
{
  if (!root) return;
  postorder(root->left);
  postorder(root->right);
  cout << root->data << " ";
}

// Non-Recursive Inorder
void inorderNR(Node *root)
{
  stack<Node *> s;
  Node *curr = root;

  while (curr || !s.empty())
  {
    while (curr)
    {
      s.push(curr);
      curr = curr->left;
    }
    curr = s.top();
    s.pop();
    cout << curr->data << " ";
    curr = curr->right;
  }
}

// Non-Recursive Preorder
void preorderNR(Node *root)
{
  if (!root) return;
  stack<Node *> s;
  s.push(root);

  while (!s.empty())
  {
    Node *curr = s.top();
    s.pop();
    cout << curr->data << " ";

    if (curr->right) s.push(curr->right);
    if (curr->left) s.push(curr->left);
  }
}

// Non-Recursive Postorder (Using 2 Stacks)
void postorderNR(Node *root)
{
  if (!root) return;
  stack<Node *> s1, s2;
  s1.push(root);

  while (!s1.empty())
  {
    Node *curr = s1.top();
    s1.pop();
    s2.push(curr);

    if (curr->left) s1.push(curr->left);
    if (curr->right) s1.push(curr->right);
  }

  while (!s2.empty())
  {
    cout << s2.top()->data << " ";
    s2.pop();
  }
}

// Evaluate numeric expression
double evaluate(Node *root)
{
  if (!root) return 0;

  // Leaf node (numeric operand)
  if (!isOperator(root->data))
    return root->data - '0';

  double left = evaluate(root->left);
  double right = evaluate(root->right);

  switch (root->data)
  {
  case '+': return left + right;
  case '-': return left - right;
  case '*': return left * right;
  case '/': return (right != 0) ? (left / right) : 0;
  case '^': return pow(left, right);
  }

  return 0;
}

// Display Prefix notation (Preorder)
void prefix(Node *root)
{
  preorder(root);
}

// Display Infix notation with parentheses
void infix(Node *root)
{
  if (!root) return;

  if (isOperator(root->data))
    cout << "( ";

  infix(root->left);
  cout << root->data << " ";
  infix(root->right);

  if (isOperator(root->data))
    cout << ") ";
}

// Calculate height of the tree
int height(Node *root)
{
  if (!root) return 0;
  return 1 + max(height(root->left), height(root->right));
}

int main()
{
  Node *root = NULL;
  string input;
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
      cout << "Enter postfix expression: ";
      cin >> input;
      root = create(input);
      cout << "Tree constructed successfully!";
      break;

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
      cout << "Inorder (NR): ";
      inorderNR(root);
      break;

    case 6:
      cout << "Preorder (NR): ";
      preorderNR(root);
      break;

    case 7:
      cout << "Postorder (NR): ";
      postorderNR(root);
      break;

    case 8:
      if (!root)
        cout << "Tree is empty!";
      else
        cout << "Result: " << evaluate(root);
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

  return 0;
}
