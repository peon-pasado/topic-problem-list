/**
 * @topics: dp, relax-constraint
 * @idea:
 *      - constraint: exist a solucion with dag structure. (never go back).
 *      - observation: if we are in a row, dont need change if necessary.
 *      - every same front-distance (to right) differ only in final position.
 * 
 *          x ------------o>
 *                        v
 *  
 *      - just optimize path with distance at most 1. 
 * 
 *          x>
 *          v
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    string s[2];
    int sum = 0;
    for (int i=0; i<2; ++i) { 
        cin>>s[i];
        for (auto c : s[i]) sum += c == '1';
        s[i] += '0';
    }
    vector<vector<int>> dp(2, vector<int>(n + 2, 1e9));
    dp[0][0] = 0;
    for (int i=0; i<n; ++i) {
        for (int j = 0; j < 2; ++j) {
            //dont change direction
            dp[j][i+1] = min(dp[j][i+1], dp[j][i] + (s[1-j][i] == '1'));
            //need change direction
            if (s[j][i+1] == '1' && s[1-j][i] == '1') {
                dp[1-j][i+2] = min(dp[1-j][i+2], dp[j][i] + 1);
            } else if (s[1-j][i] == '1') {
                dp[1-j][i+1] = min(dp[1-j][i+1], dp[j][i]);
            }
        }
    }
    int ans = min({dp[0][n], dp[1][n], dp[0][n+1], dp[1][n+1]});
    cout << sum - ans << '\n';
    return 0;
}