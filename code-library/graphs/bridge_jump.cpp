#include <vector>
using namespace std;

const int maxn = 1e5 + 10;
vector<pair<int, int>> g[maxn];
vector<pair<int, int>> E;
int lo[maxn], up[maxn];
int state[maxn];
bool cut[maxn];
vector<int> edges;

void add_edges(int a, int b) {
    int i = E.size();
    g[a].emplace_back(b, i);
    g[b].emplace_back(a, i);
    E.emplace_back(a, b);
}

template<class Func>
void dfs(int x, int p, Func& F) {
    lo[x] = up[x] = ti++;
    state[x] = 1;
    for (auto [u, id] : g[x]) {
        if (u == p) continue;
        if (state[u]==0) {
            int sz_ = edges.size();
            edges.push_back(id);
            dfs(u, x, F);
            up[x] = min(up[x], up[u]); 
            if (lo[x] < up[u]) {
                F({edges.begin() + sz_ + 1, edges.end()});
                bridges.push_back(edges[sz_]); //a bridge
                edges.resize(sz_);
            }
        } else if (state[u]==1) {
            up[x] = min(up[x], lo[u]);
            edges.push_back(id); //rease if dont need extra edges.
        }
    }
    if (p == 0 && !edges.empty()) {
        F(edges);
        edges.clear();
    }
}

int ti;
vector<int> nodes;
template<class Func>
void dfs(int x, int p, Func& F) {
    int sz_ = nodes.size();
    nodes.push_back(x);
    lo[x] = up[x] = ti++;
    state[x] = 1;
    for (auto [u, id] : g[x]) {
        if (u == p) continue;
        if (state[u]==0) {
            dfs(u, x, F);
            up[x] = min(up[x], up[u]); 
        } else {
            up[x] = min(up[x], lo[u]);
        }
    }
    if (p != 0 && lo[x] == up[x]) {
        //componente fuertemente conexa
        F(nodes.begin()+sz_, nodes.end());
    }
}

