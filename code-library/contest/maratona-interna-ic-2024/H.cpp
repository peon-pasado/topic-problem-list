#include <bits/stdc++.h>
using namespace std;

unordered_map<long long, int> cnt;
vector<long long> t;
bool vis[60];
long long v[60];
bool ok = 0;
int n;

void f(int len, int st, long long cur) {
    if (ok) return;
    if (st + n - len >= 51) return;
    if (len == n) {
        ok = 1;
        cout << t.size() << '\n';
        for (int i=0; i<(int)t.size(); ++i) {
            cout << t[i] << " \n"[i+1==(int)t.size()];
        }
        return;
    }    
    for (int i=0; i<n; ++i) {
        if (!vis[i] && abs(cur - v[i]) % (1ll<<st) != 0) return;
    }
    for (auto v : {cur - (1ll<<st), cur + (1ll<<st)}) {
        t.emplace_back(v);
        if (cnt.count(v)) {
            vis[cnt[v]] = 1;
            f(len + 1, st+1, v);
            vis[cnt[v]] = 0;
        } else {
            f(len, st+1, v);
        }
        t.pop_back();
    }
}

int main() {
    int T;
    cin>>T;
    while (T--) {
        cin>>n;
        cnt.clear();
        for (int i=0; i<n; ++i) {
            cin>>v[i];
            cnt[v[i]] = i;
        }
        if (n == 1) {
            cout << 1 << '\n' << v[0] << '\n';
            continue;
        } 

        int c[2] = {0};
        for (int i=0; i<n; ++i) {
            c[abs(v[i]) & 1]++;
        }
        int idx = -1;
        for (int i=0; i<n; ++i) {
            if (c[abs(v[i]) & 1] == 1) {
                idx = i;   
                break;
            }
        }
        memset(vis, 0, sizeof vis);
        t.clear();
        ok = 0;
        vis[idx] = 1;
        t.push_back(v[idx]);
        f(1, 0, v[idx]);
    }
    return 0;
}