#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, v, m;
    cin>>n>>v>>m;

    auto get_bit = [](int s, int i) {
        return (s>>i) & 1; 
    };

    vector<int> cur(1<<n);
    iota(cur.begin(), cur.end(), 0);
    for (int i=0; i<m; ++i) {
        int x, y;
        cin>>x>>y;
        x--; y--;
        for (int& s : cur)
            if (get_bit(s, x) < get_bit(s, y)) {
                s ^= (1<<y) | (1<<x);
            }
    }

    auto is_sorted = [](int s) {
        int k = __builtin_popcount(s);
        return ((1<<k)-1) == s;
    };

    const int mod = 1e9 + 7;
    auto _mod = [&](int& x) {
        if (x >= mod) x -= mod;
    };

    auto mod_pow = [&](int a, int b) {
        int r = 1;
        while (b > 0) {
            if (b & 1) r = (r *1ll* a) % mod;
            a = (a *1ll* a) % mod;
            b >>= 1;
        } 
        return r;
    };

    auto binom = [&](int n, int m) {
        if (m > n) return 0;
        int res = 1;
        for (int i=1; i<=m; ++i) {
            res = res*1ll*(n - i + 1) % mod;
            res = res*1ll*mod_pow(i, mod-2) % mod;
        }
        return res;
    };

    vector<vector<int>> dp(2, vector<int>(1<<n));
    dp[0][0] = 1;
    int ans = 0;
    for (int i=1; i<=n; ++i) {  
        for (int j=0; j<1<<n; ++j) dp[i&1][j] = dp[(i&1)^1][j];    
        for (int j=0; j<n; ++j)
            for (int s=0; s<1<<n; ++s)
                if (s & (1<<j)) {
                    _mod(dp[i&1][s] += dp[i&1][s ^ (1<<j)]);
                }
        for (int j=0; j<1<<n; ++j) 
            if (is_sorted(cur[j])) 
                _mod(dp[i&1][j] += mod - dp[(i&1)^1][j]);
            else
                dp[i&1][j] = 0;
        _mod(ans += (binom(v, i) *1ll* dp[i&1][(1<<n)-1]) % mod);
    }

    cout << ans << '\n';
    return 0;
}