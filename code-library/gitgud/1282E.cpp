#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
vector<pair<int, pair<int, int>>> g[maxn];
vector<int> order;
deque<int> poly[maxn];
vector<int> tri[maxn];

void dfs(int x, int p) {
    vector<int> sons;
    pair<int, int> ep;
    for (auto [v, e] : g[x]) {
        if (v == p) {
            ep = e;
            continue;
        }
        dfs(v, x);
        sons.push_back(v);
    }
    int t = tri[x][0] ^ tri[x][1] ^ tri[x][2];
    if (sons.empty()) {
        if (p != -1) {
            t ^= ep.first ^ ep.second;
            poly[x] = {ep.first, t, ep.second};
        } else {
            poly[x] = {tri[x].begin(), tri[x].end()};
        }
    } else if (sons.size() == 1) {
        swap(poly[x], poly[sons[0]]);    
        t ^= poly[x][0] ^ poly[x].back();
        if (p == -1) poly[x].push_back(t);
        else {
            auto q = make_pair(poly[x][0], t);
            if (q.first > q.second) swap(q.first, q.second);
            if (q == ep) poly[x].push_back(t);
            else poly[x].push_front(t);
        }
    } else {
        auto& p = poly[sons[0]];
        auto& q = poly[sons[1]];
        if (p.size() < q.size()) swap(p, q);
        if (p.back() == q[0]) for (int i=1; i<q.size(); ++i) p.push_back(q[i]);
        else if (p.back() == q.back()) {
            reverse(q.begin(), q.end());
            for (int i=1; i<q.size(); ++i) p.push_back(q[i]);
        } else if (p[0] == q[0]) for (int i=1; i<q.size(); ++i) p.push_front(q[i]);
        else {
            reverse(q.begin(), q.end());
            for (int i=1; i<q.size(); ++i) p.push_front(q[i]);
        }
        swap(poly[x], p);
    }
    order.push_back(x);
}

int main() {
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        for (int i=0; i<n; ++i) g[i].clear(), poly[i].clear(), tri[i].clear();
        order.clear();
        map<pair<int, int>, int> id;
        for (int i=0; i<n-2; ++i) {
            vector<int> r(3);
            for (int j=0; j<3; ++j) cin>>r[j];
            tri[i] = r;
        }
        for (int i=0; i<n-2; ++i) {
            for (int j = 0; j < 3; ++j) {
                auto q = make_pair(tri[i][j], tri[i][(j+1)%3]);
                if (q.first > q.second) swap(q.first, q.second);
                if (id.count(q)) {
                    g[i].push_back({id[q], q});
                    g[id[q]].push_back({i, q});
                } else {
                    id[q] = i;
                }
            }
        }
        int r = 0;
        for (int i=1; i<n-2; ++i) {
            if (g[i].size() < 3) {
                r = i;
                break;
            }
        }
        dfs(r, -1);
        for (auto x : poly[r]) cout << x << ' ';
        cout << '\n';
        for (auto x : order) cout << x+1 << ' ';
        cout << '\n';
    }
    return 0;
}