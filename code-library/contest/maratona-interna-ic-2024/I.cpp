//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 2;
int p[maxn];
int head_g[maxn], to_g[2 * maxn];
pair<int, int> val_g[2 * maxn];
int Eg;
int head_t[2*maxn], to_t[4 * maxn];
pair<int, int> val_t[4 * maxn];
int Et;

int color[2 * maxn];
int other[maxn];
int rnk[maxn], pr[maxn];
long long mw[maxn];
int n, m;

void add_edge_g(int u, int v, int w) {
    Eg++;
    to_g[Eg] = head_g[u]; 
    val_g[Eg] = {v, w};  
    head_g[u] = Eg;

    Eg++;
    to_g[Eg] = head_g[v];
    val_g[Eg] = {u, w};
    head_g[v] = Eg;
}

void add_edge_t(int u, int v, int w) {
    Et++;
    to_t[Et] = head_t[u]; 
    val_t[Et] = {v, w};  
    head_t[u] = Et;

    Et++;
    to_t[Et] = head_t[v];
    val_t[Et] = {u, w};
    head_t[v] = Et;
}

void dfs1(int x, int p=-1) {
    int last = x;
    bool fst = 1;
    for (int e = head_g[x]; e != -1; e = to_g[e]) {
        auto [v, w] = val_g[e];
        if (v == p) continue;
        dfs1(v, x);
        if (fst) {
            add_edge_t(last, v, w);
            fst = 0;
        } else {
            ++m;
            add_edge_t(last, m, 0);
            add_edge_t(m, v, w);
            last = m;
        }   
    }
}

bool block[2 * maxn];
int np[2 * maxn];
int ce = -1;
int cw;
int sz[2 * maxn];
void dfs(int v, int p, int ee, int n) {
    sz[v] = 1;
    np[v] = p;
    for (int e = head_t[v]; e != -1; e = to_t[e]) {
        auto [u, w] = val_t[e];
        if (block[u] || u == p) continue;
        dfs(u, v, w, n);
        sz[v] += sz[u]; 
    }
    if (p != -1) {
        if (ce == -1 || max(sz[ce], n - sz[ce]) > max(sz[v], n - sz[v])) {
            ce = v;
            cw = ee;
        }
    } 
}

long long dist[2 * maxn];
bool vis[2 * maxn];
int nodes[2][maxn];
int extra[maxn], nnn;
int nn[2];
int qu[2 * maxn], fr, bck;
void bfs(int u, int v) {
    vis[u] = vis[v] = 1;
    int no[2] = {u, v};
    nnn = 0;
    for (int i=0; i<2; ++i) {
        fr = bck = 0;
        qu[bck++] = no[i];
        dist[no[i]] = 0;
        while (fr != bck) {
            int q = qu[fr++];
            if (color[q] > 0) nodes[i][nn[i]++] = q;
            else extra[nnn++] = q;
            for (int e = head_t[q]; e != -1; e = to_t[e]) {
                auto [v, w] = val_t[e];
                if (block[v] || vis[v]) continue;
                qu[bck++] = v;
                dist[v] = dist[q] + w;
                vis[v] = 1;
            }
        }
    }
    for (int i=0; i<nnn; ++i) vis[extra[i]] = 0;
    for (int i=0; i<2; ++i) 
        for (int j=0; j<nn[i]; ++j) {
            vis[nodes[i][j]] = 0;
        }
}

void solve_edge(int u, int v, int w) {
    nn[0] = nn[1] = 0;
    bfs(u, v);
    pair<int, long long> best[2][2];
    for (int i=0; i<2; ++i)
        for (int j=0; j<2; ++j)
            best[i][j] = make_pair(0, 1e18);
    for (int i=0; i<2; ++i) {
        for (int j=0; j<nn[i]; ++j) {
            int v = nodes[i][j];
            if (best[i][0].second > dist[v] + p[v]) {
                best[i][0] = {color[v], dist[v] + p[v]};
            }
        }
        if (best[i][0].first == 0) continue;
        for (int j=0; j<nn[i]; ++j) {
            int v = nodes[i][j];
            if (color[v] == best[i][0].first) continue;
            if (best[i][1].second > dist[v] + p[v]) {
                best[i][1] = {color[v], dist[v] + p[v]};
            } 
        }
    }
    if (best[0][0].first == 0 || best[1][0].first == 0) return;
    for (int i=0; i<2; ++i) {
        for (int j=0; j<nn[i]; ++j) {
            int v = nodes[i][j];
            if (best[i ^ 1][0].first == color[v]) {
                if (best[i ^ 1][1].first > 0) {
                    long long we = dist[v] + w + best[i^1][1].second + p[v];
                    if (we < mw[color[v]]) {
                        mw[color[v]] = we;
                        other[color[v]] = best[i^1][1].first;
                    }
                }
            } else if (best[i^1][0].first > 0) {
                    long long we = dist[v] + w + best[i^1][0].second + p[v];
                    if (we < mw[color[v]]) {
                        mw[color[v]] = we;
                        other[color[v]] = best[i^1][0].first;
                    } 
            }
        }
    }
}

void decompose(int v, int n) {
    if (n == 1) return;

    ce = -1;
    dfs(v, -1, -1, n);
    
    solve_edge(ce, np[ce], cw);

    int u = ce, uu = np[ce]; 

    block[u] = 1;
    decompose(uu, n - sz[u]);
    block[u] = 0;

    block[uu] = 1;
    decompose(u, sz[u]);
    block[uu] = 0;
}

int get(int x) {
    return x == pr[x] ? x : pr[x] = get(pr[x]);
}

void merge(int u, int v) {
    u = get(u); v = get(v);
    if (u == v) return;
    if (rnk[u] < rnk[v]) swap(u, v);
    rnk[u] += rnk[u]==rnk[v];
    pr[v] = u;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n;
    memset(head_g, -1, sizeof head_g);
    memset(head_t, -1, sizeof head_t);
    for (int i=1; i<=n; ++i) cin>>p[i];
    for (int i=1; i<n; ++i) {
        int u, v, w;
        cin>>u>>v>>w;
        add_edge_g(u, v, w);
    }
    iota(color, color+n+1, 0);
    m = n;
    dfs1(1);
    iota(pr, pr+n+1, 0);
    long long mst = 0;
    int comp = n;
    while (comp != 1) {
        fill(mw + 1, mw + n + 1, 1e18);
        decompose(1, m);                  
        for (int i=1; i<=n; ++i) {
            if (other[i] == 0) continue;
            if (get(i) != get(other[i])) {
                comp--;
                merge(i, other[i]);
                mst += mw[i];
            }
        }
        for (int i=1; i<=n; ++i) {
            color[i] = color[get(i)];
        }
    }
    cout << mst << '\n';
    return 0;
}