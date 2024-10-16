#include <bits/stdc++.h>
using namespace std;

const int maxn = 4'000'002;
bitset<maxn> pos, neg;

int main() {
    int n;
    cin>>n;
    vector<int> a;
    for (int i=0; i<n; ++i) {
        int x;
        cin>>x;
        if (x != 0) a.push_back(x); 
    }
    sort(a.begin(), a.end());
    if (a.empty()) {
        cout << 0 << '\n';
        exit(0);
    }
    n = a.size();
    if (a[n-1] * a[0] > 0) {
        cout << a[n-1] << '\n';
        exit(0);
    }
    pos[0] = 1;
    neg[0] = 1;
    for (int i=0; i+1<n; ++i) {
        if (a[i] >= 0) pos |= pos<<a[i];
        else neg |= neg<<(-a[i]);    
    }
    int ans = -1e9;
    int last = 0;
    for (int i=1; i<maxn; ++i) {
        if (pos[i]) last = i;
        if (neg[i]) ans = max(ans, last - i + a[n-1]);
    }
    cout << ans << '\n';
    return 0;
}