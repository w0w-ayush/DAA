#include<bits/stdc++.h>
using namespace std;

double fractionalKnapsack(vector<int>& values, vector<int>& weights, int w, int n) {
    vector<pair<int, int>> arr(n);
    for(int i=0 ; i<n ; i++){ 
        arr[i] = {values[i], weights[i]};        
    }

    sort(arr.begin(), arr.end(), [](pair<int, int>&a, pair<int, int>& b) {
        // return a.second < b.second;
        double r1 = (double)a.first / (double)a.second;
        double r2 = (double)b.first / (double)b.second;

        return r1 > r2;
    });

    for(auto it : arr) {
        cout << it.first << " " << it.second << endl;
    }

    double ans = 0;
    for(int i=0 ; i<arr.size() ; i++) {
        int value = arr[i].first;
        int weight = arr[i].second;

        if(weight <= w) {
            ans += value;
            w -= weight;
        } else {
            ans += ((double)value / (double)weight) * w;
            break;
        }
    }

    return ans;
}

int main(){ 
    int n;
    cout << "Enter the number of elements - ";
    cin >> n;

    vector<int> values(n, 0), weights(n, 0);
    cout << "Enter the values - " << endl;
    for(int i=0 ; i<n ; i++) {
        cin >> values[i]; 
    }

    cout << "Enter the weights - " << endl;
    for(int i=0 ; i<n ; i++) {
        cin >> weights[i];
    }

    int w;
    cout << "Enter the weight of Knapsack - ";
    cin >> w;

    cout << "\nValues - ";
    for(int i=0 ; i<n ; i++) {
        cout << values[i] << " "; 
    }

    cout << "\nWeights - ";
    for(int i=0 ; i<n ; i++) {
        cout << weights[i] << " ";
    }

    cout << "\nWeight of your Knapsack is - " << w << endl;

    double ans = fractionalKnapsack(values, weights, w, n);
    cout << "\nMaximum value that can be obtained is - " << ans << endl;

    return 0; 
}

/* 
Enter the number of elements - 10
Enter the values -
8 2 10 1 9 7 2 6 4 9
Enter the weights -
10 1 7 7 5 1 8 6 8 7
Enter the weight of Knapsack - 21

Values - 8 2 10 1 9 7 2 6 4 9
Weights - 10 1 7 7 5 1 8 6 8 7
Weight of your Knapsack is - 21

7 1
2 1
9 5
10 7
9 7
6 6
8 10
4 8
2 8
1 7

Maximum value that can be obtained is - 37
*/