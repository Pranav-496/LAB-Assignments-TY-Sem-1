/*
A relief organization needs to distribute food packages to food-affected areas using limited capacity truck.
Each package type has a weight and a benefit score(importance).
Write a C++ program to select the combination of packages that maximizes total benefit using the
fractional knapsack greedy method.
Display:
1. Each package selected and its fraction
2. Total benefit obtained
3. Total truck weight used.
*/

#include <bits/stdc++.h>
using namespace std;

struct Item
{
  int id, benefit, weight;
  double ratio;
};

bool compare(Item a, Item b)
{
  return a.ratio > b.ratio;
}

int main()
{
  int n, capacity;

  cout << "Enter number of packages: ";
  cin >> n;

  vector<Item> items(n);

  cout << "Enter benefit and weight of each package:\n";

  for (int i = 0; i < n; i++)
  {
    items[i].id = i + 1;

    cin >> items[i].benefit >> items[i].weight;

    items[i].ratio =
        (double)items[i].benefit / items[i].weight;
  }

  cout << "Enter truck capacity: ";
  cin >> capacity;

  sort(items.begin(), items.end(), compare);

  double totalBenefit = 0;
  double totalWeight = 0;

  cout << "\nSelected Packages:\n";

  for (int i = 0; i < n; i++)
  {
    if (capacity == 0)
      break;

    double fraction;

    if (items[i].weight <= capacity)
    {
      fraction = 1.0;
      capacity -= items[i].weight;
    }
    else
    {
      fraction = (double)capacity / items[i].weight;
      capacity = 0;
    }

    double selectedWeight = fraction * items[i].weight;
    double selectedBenefit = fraction * items[i].benefit;

    totalWeight += selectedWeight;
    totalBenefit += selectedBenefit;

    cout << "Package " << items[i].id
         << " - Fraction: " << fraction
         << ", Weight: " << selectedWeight
         << ", Benefit: " << selectedBenefit << endl;
  }

  cout << "\nTotal Truck Weight Used = " << totalWeight;
  cout << "\nMaximum Benefit Obtained = " << totalBenefit << endl;

  return 0;
}
