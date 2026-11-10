#include <bits/stdc++.h>
using namespace std;

struct Item {
    int profit, weight;
    double ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);

    cout << "Enter profit and weight of each item:\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].profit >> items[i].weight;
        items[i].ratio = (double)items[i].profit / items[i].weight;
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    sort(items.begin(), items.end(), compare);

    double maxProfit = 0.0;

    for (int i = 0; i < n; i++) {
        if (capacity == 0)
            break;

        if (items[i].weight <= capacity) {
            maxProfit += items[i].profit;
            capacity -= items[i].weight;
        } else {
            maxProfit += items[i].ratio * capacity;
            capacity = 0;
        }
    }

    cout << "Maximum Profit = " << maxProfit << endl;

    return 0;
}