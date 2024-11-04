#include<bits/stdc++.h>
using namespace std;

int greedy(vector<int>& values, vector<int>& weights, int w, int n) {
    vector<pair<int, int>> arr(n);
    for(int i = 0; i < n; i++) {
        arr[i] = {values[i], weights[i]};
    }

    sort(arr.begin(), arr.end(), [](pair<int, int>& a, pair<int, int>& b) {
        double r1 = (double)a.first / (double)a.second;
        double r2 = (double)b.first / (double)b.second;

        return r1 > r2;
        // return a.first > b.first;
    });

    int ans = 0;
    for(int i = 0; i < n; i++) {
        int value = arr[i].first;
        int weight = arr[i].second;

        if(weight <= w) {
            w -= weight;
            ans += value;
        } else {
            break;
        }
    }

    return ans;
}

int recursive(vector<int>& values, vector<int>& weights, int w, int ind, int n) {
    if(ind >= n || w <= 0) {
        if(weights[ind] <= w) {
            return values[ind];
        }
        return 0;
    }

    int take = INT_MIN;
    if(weights[ind] <= w) {
        take = values[ind] + recursive(values, weights, w-weights[ind], ind+1, n);
    }

    int notTake = 0 + recursive(values, weights, w, ind+1, n);

    return max(take, notTake);
}

int memoization(vector<int>& values, vector<int>& weights, int w, int ind, int n, vector<vector<int>>& dp) {
    if(ind >= n) {
        if(weights[ind] <= w) {
            return values[ind];
        }
        return 0;
    }

    if(dp[ind][w] != -1) {
        return dp[ind][w];
    }

    int take = INT_MIN;
    if(weights[ind] <= w) {
        take = values[ind] + memoization(values, weights, w-weights[ind], ind+1, n, dp);
    }

    int notTake = 0 + memoization(values, weights, w, ind+1, n, dp);

    return dp[ind][w] = max(take, notTake);
}

int tabulation(vector<int>& values, vector<int>& weights, int maxWeights, int n) {
    vector<vector<int>> dp(n, vector<int> (maxWeights+1, 0));
    for(int i=weights[0] ; i<=maxWeights ; i++) dp[0][i] = values[0];

    for(int ind=0 ; ind<n ; ind++) {
        for(int W=0 ; W<=maxWeights ; W++) {
            int take = INT_MIN;
            if(weights[ind] <= W) {
                take = values[ind] + dp[ind-1][W-weights[ind]];
            }

            int notTake = 0 + dp[ind-1][W];

            dp[ind][W] = max(take, notTake);
        }
    }

    return dp[n-1][maxWeights];
}

int main() {
    int n;
    cout << "Enter the number of elements - ";
    cin >> n;

    vector<int> values(n), weights(n);
    cout << "Enter the values - ";
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    cout << "Enter the weights - ";
    for (int i = 0; i < n; i++) {
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

    // int ans = greedy(values, weights, w, n);
    // int ans = recursive(values, weights, w, 0, n);

    // vector<vector<int>> dp(n, vector<int> (w+1, -1));
    // int ans = memoization(values, weights, w, 0, n, dp);
 
    int ans = tabulation(values, weights, w, n);
    cout << "\nMaximum profit that can be obtained is - " << ans << endl;

    return 0; 
}

/* 
Enter the number of elements - 5
Enter the values - 12 35 41 25 32
Enter the weights - 20 24 36 40 42
Enter the weight of Knapsack - 100

Values - 12 35 41 25 32
Weights - 20 24 36 40 42
Weight of your Knapsack is - 100

Maximum profit that can be obtained is - 101

*/