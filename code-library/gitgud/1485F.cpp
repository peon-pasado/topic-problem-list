#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int mod = 1e9 + 7;

int main() {
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        vector<ll> b(n+1);
        vector<vector<ll>> dp(2, vector<ll>(n+1));
        map<ll, int> f;
        //f[0];
        for (int i=1; i<=n; ++i) cin>>b[i], b[i] += b[i-1];
        //dp[0][0] = dp[0][1] = 0;
        dp[1][0] = dp[1][1] = 1;
        for (int i=2; i<=n; ++i) {
            f[b[i-2]] = (f[b[i-2]] + dp[1][i-1]) % mod;
            dp[1][i] = dp[0][i] = (dp[1][i-1] + dp[0][i-1]) % mod;
            if (f.count(b[i-1]))
               dp[1][i] = (dp[1][i] + mod - f[b[i-1]]) % mod;
        }
        cout << (dp[0][n] + dp[1][n]) % mod << '\n';
    }
    return 0;
}
