#include <bits/stdc++.h>
using namespace std;

int main() {
    cout<<setprecision(10)<<fixed;
    int n, k;
    cin>>n>>k;
    vector<long long> x(n); 
    for (int i=0; i<n; ++i) {
        cin>>x[i];
    }
    long long s = 0, s2 = 0;
    for (int i=0; i<k; ++i) {
        s += x[i];
        s2 += x[i] * x[i];
    }   
    long long res = s2*k - s*s; 
    int l = 1, r = k;
    for (int i=k; i<n; ++i) {
        s += x[i] - x[i - k];
        s2 += x[i]*x[i] - x[i-k]*x[i-k];
        auto res2 = s2*k - s*s;
        if (res > res2) {
            res = res2;
            l = i - k + 2;
            r = i + 1;
        }
    }
    cout << l << ' ' << r << endl;
    long double ans = sqrtl((long double)res / (k *1ll* k));
    cout << ans << '\n';
    return 0;
}