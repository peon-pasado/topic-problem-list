#include <bits/stdc++.h>
using namespace std;

int A[1<<16];
int F[1<<16];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin>>q;
    vector<pair<int, int>> l;
    const int B = 1000;
    for (int i=0; i<q; ++i) {
        if (l.size() >= B) {
            for (auto [v, d] : l) A[v] += d;
            for (int i=0; i<1<<16; ++i) 
                F[i] = A[i];
            for (int i=0; i<16; ++i)
                for (int j=0; j<1<<16; ++j)
                    if (j & (1<<i))
                        F[j] += F[j ^ (1<<i)];
            l.clear();
        }
        string type;
        int x;
        cin>>type>>x; 
        if (type[0] == 'a') l.emplace_back(x, 1);
        else if (type[0] == 'd') l.emplace_back(x, -1);
        else {
            int ans = F[x];
            for (auto [v, d] : l) {
                if ((x & v) == v) {
                    ans += d;
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}