#include <iostream>
#include <algorithm>

using namespace std;

bool compare(pair<double, double> a, pair<double, double> b) {
    return (a.first / a.second) > (b.first / b.second);
}

double fractionalKnapsack(int W, double value[], double weight[], int n) {
    pair<double, double> items[10]; // Array of pairs (value, weight)

    // Storing values and weights in pairs
    for (int i = 0; i < n; i++) {
        items[i] = make_pair(value[i], weight[i]);
    }

    // Sorting items based on value/weight ratio
    sort(items, items + n, compare);

    double totalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (W >= items[i].second) {
            W -= items[i].second;
            totalValue += items[i].first;
        } else {
            totalValue += (items[i].first / items[i].second) * W;
            break;
        }
    }
    return totalValue;
}

int main() {
    int W = 50; // Knapsack weight limit
    int n;
    
    cout << "Enter number of items: ";
    cin >> n;

    double value[10], weight[10];

    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " (Value, Weight): ";
        cin >> value[i] >> weight[i];
    }

    cout << "Maximum value in Knapsack = " << fractionalKnapsack(W, value, weight, n) << endl;
    return 0;
}
