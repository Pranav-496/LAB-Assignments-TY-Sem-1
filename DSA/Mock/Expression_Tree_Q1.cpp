/*
write a menu-driven C++ program to construct an expression tree for a Boolean expression given in prefix form.
Perform the following operations:
1. construct and display the tree
2. traverse using inorder, preorder, and postorder, recursive and non-recursive
3. simplify the Boolean expression by applying logical laws
4. swap left and right subtrees.
*/

#include <iostream>
#include <string>
#include <stack>
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
  return ch == '&' || ch == '|' || ch == '!' || ch == '^';
}

// Construct tree from Prefix expression
Node *create(string exp)
{
  stack<Node *> s;

  for (int i = exp.length() - 1; i >= 0; i--)
  {
    Node *newNode = new Node(exp[i]);

    if (!isOperator(exp[i]))
    {
      s.push(newNode);
    }
    else
    {
      newNode->left = s.top();
      s.pop();

      // Binary operators take a right child too (unary '!' takes only left)
      if (exp[i] != '!')
      {
        newNode->right = s.top();
        s.pop();
      }

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

// Check if two subtrees are identical
bool sameTree(Node *a, Node *b)
{
  if (!a && !b) return true;
  if (!a || !b) return false;
  return (a->data == b->data) && sameTree(a->left, b->left) && sameTree(a->right, b->right);
}

// Simplify Boolean Expression using Logical Laws
Node *simplify(Node *root)
{
  if (!root) return NULL;

  root->left = simplify(root->left);
  root->right = simplify(root->right);

  char op = root->data;
  Node *L = root->left;
  Node *R = root->right;

  // Double Negation: !(!A) = A
  if (op == '!' && L && L->data == '!')
    return L->left;

  // AND Laws (&)
  if (op == '&')
  {
    if (L->data == '0' || R->data == '0') return new Node('0'); // Annihilation: A & 0 = 0
    if (L->data == '1') return R;                               // Identity: 1 & A = A
    if (R->data == '1') return L;                               // Identity: A & 1 = A
    if (sameTree(L, R)) return L;                               // Idempotence: A & A = A
  }

  // OR Laws (|)
  if (op == '|')
  {
    if (L->data == '1' || R->data == '1') return new Node('1'); // Annihilation: A | 1 = 1
    if (L->data == '0') return R;                               // Identity: 0 | A = A
    if (R->data == '0') return L;                               // Identity: A | 0 = A
    if (sameTree(L, R)) return L;                               // Idempotence: A | A = A
  }

  // XOR Laws (^)
  if (op == '^')
  {
    if (sameTree(L, R)) return new Node('0');                   // A ^ A = 0
    if (L->data == '0') return R;                               // 0 ^ A = A
    if (R->data == '0') return L;                               // A ^ 0 = A
  }

  return root;
}

// Swap / Mirror left and right subtrees
void mirror(Node *root)
{
  if (!root) return;
  swap(root->left, root->right);
  mirror(root->left);
  mirror(root->right);
}

int main()
{
  Node *root = NULL;
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
      cout << "Enter prefix expression: ";
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
      if (root)
      {
        root = simplify(root);
        cout << "Expression simplified! New Inorder: ";
        inorder(root);
      }
      else
        cout << "Tree is empty!";
      break;

    case 9:
      mirror(root);
      cout << "Tree mirrored! New Inorder: ";
      inorder(root);
      break;

    case 10:
      cout << "Exiting...";
      break;

    default:
      cout << "Invalid choice!";
    }

  } while (choice != 10);

  return 0;
}
