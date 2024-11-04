#include<bits/stdc++.h>
using namespace std;

class Solution { 
public: 
    void solve(int col, vector<vector<string>> &ans, vector<string>& board, int n, 
            vector<int>& upperDiagonal, vector<int>& lowerDiagonal, vector<int>& leftRow) { 
                if(col == n) { 
                    ans.push_back(board); 
                    return ; 
                } 
 
                for(int row=0 ; row<n ; row++) { 
                    if(upperDiagonal[row+col] == 0 && lowerDiagonal[(n-1)+col-row] == 0 
                        && leftRow[row] == 0) { 
                            board[row][col] = 'Q'; 
                            upperDiagonal[row+col] = 1; 
                            lowerDiagonal[(n-1)+col-row] = 1; 
                            leftRow[row] = 1; 
                            solve(col+1, ans, board, n, upperDiagonal, lowerDiagonal, leftRow); 
                            board[row][col] = '.'; 
                            upperDiagonal[row+col] = 0; 
                            lowerDiagonal[(n-1)+col-row] = 0; 
                            leftRow[row] = 0; 
                        } 
                } 
            } 
 
    vector<vector<string>> solveNQueens(int n) { 
        vector<vector<string>> ans; 
        vector<string> board(n); 
        string s(n, '.'); 
        for(int i=0 ; i<n ; i++) { 
            board[i] = s; 
        } 
 
        vector<int> upperDiagonal(2*n-1, 0), lowerDiagonal(2*n-1, 0), leftRow(n, 0); 
        solve(0, ans, board, n, upperDiagonal, lowerDiagonal, leftRow); 
 
        return ans; 
    } 
}; 

int main() {
    Solution s; 
    int n;
    cout << "Enter the number of Queens - ";
    cin >> n;

    vector<vector<string>> ans = s.solveNQueens(n); 
    for(auto i : ans) { 
        for(auto j : i) { 
            cout << j << endl; 
        } 
        cout << "\n"; 
    } 

    cout << "Total possible solutions for placing " << n << " queens in a board - " << ans.size() << endl;

    return 0;
}
 

/* class Solution { 
public: 
    bool isSafe(int row, int col, vector<string>& board, int n) { 
        int x = row; 
        int y = col; 
 
        //checking for same row 
        while(y >= 0){ 
            if(board[x][y] == 'Q') { 
                return false; 
            } 
            y--; 
        } 
 
        x = row; 
        y = col; 
        // checking upper diagonal  
        while(y>=0 && x>=0) { 
            if(board[x][y] == 'Q') { 
                return false; 
            } 
            x--; 
            y--; 
        } 
 
        x = row; 
        y = col; 
        while(x < n && y >= 0) { 
            if(board[x][y] == 'Q') { 
                return false; 
            } 
            x++; 
            y--; 
        } 
 
        return true; 
    } 
 
    void solve(int col, vector<vector<string>>& ans, vector<string>& board, int n) { 
        if(col == n) { 
            ans.push_back(board); 
            return ; 
        } 
 
        for(int row = 0; row<n ; row++) { 
            if(isSafe(row, col, board, n)) { 
                board[row][col] = 'Q'; 
                solve(col+1, ans, board, n); 
                board[row][col] = '.'; 
            } 
        } 
    } 
 
    vector<vector<string>> solveNQueens(int n) { 
        vector<vector<string>> ans; 
        vector<string> board(n); 
        string s(n, '.'); 
        for(int i=0 ; i<n ; i++) { 
            board[i] = s; 
        } 
 
        solve(0, ans, board, n); 
 
        return ans; 
    } 
}; */