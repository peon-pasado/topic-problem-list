#include <bits/stdc++.h>
using namespace std;

using ll = __int128_t;
ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

int main() {
    int t;
    cin>>t;
    while (t--) {
        int n, k;
        cin>>n>>k;
        vector<long long> a(n);
        for (int i=0; i<n; ++i) {
            cin>>a[i];
        }
        vector<ll> g(n);
        g[0] = a[0];
        for (int i=1; i<n; ++i) {
            ll x, y;
            g[i] = euclid(a[i], g[i-1], x, y);
        }
        if (k % g.back() == 0) {
            cout << "YES\n";
            ll mt = k / g.back();
            vector<ll> ans(n);
            for (int i=n-2; i>=0; --i) {
                ll xg, yg;
                euclid(a[i+1], g[i], xg, yg);
                ll mod = a[i+1] / g[i+1] * 1ll * g[i];
                xg %= mod;
                yg %= mod;
                ans[i+1] = xg * mt;                
                mt *= yg;
            }
            ans[0] = mt;
            for (int i=0; i<n; ++i) {
                string s;
                int sign = 1;
                if (ans[i] < 0) ans[i] *= -1, sign = -1;
                if (ans[i] == 0) s = "0";
                while (ans[i] > 0) {
                    s += '0' + (ans[i] % 10);
                    ans[i] /= 10;
                }
                reverse(s.begin(), s.end());
                if (sign == -1) cout << '-';
                cout << s << " \n"[i+1==n];
            }
        } else {
            cout << "NO\n";
        }
    }        
    return 0;
}