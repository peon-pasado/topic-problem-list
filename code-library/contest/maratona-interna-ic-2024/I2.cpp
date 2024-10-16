#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 10;
int p[maxn];
vector<pair<int, int>> g[maxn];
pair<int, int> t[3][2*maxn];
//vector<pair<int, int>> t[2 * maxn];
int color[2 * maxn];
int other[maxn];
int rnk[maxn], pr[maxn];
long long mw[maxn];
int n, m;

void dfs1(int x, int p=-1) {
    int last = x;
    bool fst = 1;
    for (auto [v, w] : g[x]) {
        if (v == p) continue;
        dfs1(v, x);
        if (fst) {
            t[0][last] = {v, w};
            t[2][v] = {last, w}; 
            //add_edge(last, {v, w});
            fst = 0;
        } else {
            ++m;
            t[1][last] = {m, 0};
            t[2][m] = {last, 0};
            t[0][m] = {v, w};
            t[2][v] = {m, w};
            //add_edge(last, {m, 0});
            //add_edge(m, {v, w});
            last = m;
        }   
    }
}

bool block[2 * maxn];
int np[2 * maxn];
int ce = -1;
int cw;
int sz[2 * maxn];
void dfs(int v, int p, int e, int n) {
    sz[v] = 1;
    np[v] = p;
    for (int i=0; i<3; ++i) {
        auto [u, w] = t[i][v];
        if (u == -1) continue;
        if (block[u] || u == p) continue;
        dfs(u, v, w, n);
        sz[v] += sz[u]; 
    }
    if (p != -1) {
        if (ce == -1 || max(sz[ce], n - sz[ce]) > max(sz[v], n - sz[v])) {
            ce = v;
            cw = e;
        }
    } 
}

vector<int> nodes[2];
long long dist[2 * maxn];
bool vis[2 * maxn];
void bfs(int u, int v) {
    queue<int> Q;
    vis[u] = vis[v] = 1;
    Q.push(u);
    dist[u] = dist[v] = 0;
    while (!Q.empty()) {
        int q = Q.front(); Q.pop();
        nodes[0].push_back(q);
        for (int i=0; i<3; ++i) {
            auto [v, w] = t[i][q];
            if (v == -1) continue;
            if (block[v] || vis[v]) continue;
            Q.push(v);
            dist[v] = dist[q] + w;
            vis[v] = 1;
        }
    }
    Q.push(v);
    while (!Q.empty()) {
        int q = Q.front(); Q.pop();
        nodes[1].push_back(q);
        for (int i=0; i<3; ++i) {
            auto [v, w] = t[i][q];
            if (v == -1) continue;
            if (block[v] || vis[v]) continue;
            Q.push(v);
            dist[v] = dist[q] + w;
            vis[v] = 1;
        }
    }
    for (int i=0; i<2; ++i) 
        for (int v : nodes[i]) vis[v] = 0;
}

void solve_edge(int u, int v, int w) {
    for (int i=0; i<2; ++i) nodes[i].clear();
    bfs(u, v);
    pair<int, long long> best[2][2];
    for (int i=0; i<2; ++i)
        for (int j=0; j<2; ++j)
            best[i][j] = make_pair(0, 1e18);
    for (int i=0; i<2; ++i) {
        for (int v : nodes[i]) {
            if (color[v] == 0) continue;
            if (best[i][0].second > dist[v] + p[v]) {
                best[i][0] = {color[v], dist[v] + p[v]};
            }
        }
        if (best[i][0].first == 0) continue;
        for (int v : nodes[i]) {
            if (color[v] == 0) continue;
            if (color[v] == best[i][0].first) continue;
            if (best[i][1].second > dist[v] + p[v]) {
                best[i][1] = {color[v], dist[v] + p[v]};
            } 
        }
    }
    if (best[0][0].first == 0 || best[1][0].first == 0) return;
    for (int i=0; i<2; ++i) {
        for (int v : nodes[i]) {
            if (color[v] == 0) continue;
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
    
    //solve for this cut
    solve_edge(ce, np[ce], cw);

    int u = ce, uu = np[ce]; 

    block[u] = 1;
    decompose(uu, n - sz[u]);
    block[u] = 0;

    block[uu] = 1;
    decompose(u, sz[u]);
    block[uu] = 0;
}

void edge_decomposition() {
    decompose(1, m);
}

const int MOD = 1e9 + 7;
const int BUF_SZ = 1 << 20;

inline namespace Input {
char buf[BUF_SZ];
int pos;
int len;
char next_char() {
	if (pos == len) {
		pos = 0;
		len = (int)fread(buf, 1, BUF_SZ, stdin);
		if (!len) { return EOF; }
	}
	return buf[pos++];
}

int read_int() {
	int x;
	char ch;
	int sgn = 1;
	while (!isdigit(ch = next_char())) {
		if (ch == '-') { sgn *= -1; }
	}
	x = ch - '0';
	while (isdigit(ch = next_char())) { x = x * 10 + (ch - '0'); }
	return x * sgn;
}
}
int main() {
    //memset(t, -1, sizeof t);
    for (int i=0; i<3; ++i)
        for (int j=0; j<2*maxn; ++j) t[i][j] = {-1, -1};
    //cin.tie(nullptr)->sync_with_stdio(false);
    //cin>>n;
    n = read_int();
    for (int i=1; i<=n; ++i) p[i] = read_int(); //>>p[i];
    for (int i=1; i<n; ++i) {
        int u, v, w;
        u = read_int();
        v = read_int();
        w = read_int();
        //cin>>u>>v>>w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    iota(color, color+n+1, 0);
    m = n;
    dfs1(1);
    iota(pr, pr+n+1, 0);
    auto get = [&](auto&& get, int x) {
        if (x == pr[x]) return x;
        return pr[x] = get(get, pr[x]);
    };
    auto merge = [&](int u, int v) {
        u = get(get, u); v = get(get, v);
        if (u == v) return;
        if (rnk[u] < rnk[v]) swap(u, v);
        rnk[u] += rnk[u]==rnk[v];
        pr[v] = u;
    };
    long long mst = 0;
    int comp = n;
    while (comp != 1) {
        fill(mw + 1, mw + n + 1, 1e18);
        edge_decomposition();                    
        for (int i=1; i<=n; ++i) {
            if (other[i] == 0) continue;
            if (get(get, i) != get(get, other[i])) {
                comp--;
                merge(i, other[i]);
                mst += mw[i];
            }
        }
        for (int i=1; i<=n; ++i) {
            color[i] = color[get(get, i)];
        }
    }
    printf("%lld\n", mst);
    //cout << mst << '\n';
    return 0;
