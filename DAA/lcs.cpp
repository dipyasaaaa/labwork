#include <iostream>

using namespace std;

void LCS(string X, string Y, int m, int n) {
    int dp[m + 1][n + 1];

    // Building the DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) 
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1]) 
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else 
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // LCS length
    int length = dp[m][n];

    // Backtracking to find the LCS sequence
    int i = m, j = n;
    string lcs = "";

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs = X[i - 1] + lcs; // Append character
            i--; j--; // Move diagonally
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) 
            i--; // Move up
        else 
            j--; // Move left
    }

    // Output results
    cout << "Length of Longest Common Subsequence: " << length << endl;
    cout << "Longest Common Subsequence: " << lcs << endl;
}

int main() {
    string X, Y;
    cout << "Enter first string: ";
    cin >> X;
    cout << "Enter second string: ";
    cin >> Y;

    int m = X.length();
    int n = Y.length();

    LCS(X, Y, m, n);
    return 0;
}
