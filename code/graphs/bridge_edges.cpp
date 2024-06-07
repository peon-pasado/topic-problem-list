#include <vector>
using namespace std;

const int maxn = 1e5 + 10;
vector<pair<int, int>> g[maxn];
vector<pair<int,int>> bridges;
vector<int> edges;
int sum[maxn];
short state[maxn];

int n_edges = 0;
void add_edge(int a, int b) {
    g[a].emplace_back(b, n_edges);
    g[b].emplace_back(a, n_edges++);
}

template<class Func>
void dfs(int x, int p, Func& F) {
    int sz_ = edges.size(), id_p = -1;
    sum[x] = 0; 
    state[x] = 1;
    for (auto [u, id] : g[x]) {
        if (u==p) {
            id_p = id;
            continue;
        }
        if (state[u]==0) {
            dfs(u, x, F);
            sum[x] += sum[u];
        } else {
            sum[x] += state[u];
            if (state[u] == -1) {
                edges.push_back(id); //remove if just need tree-edge
            }
        }
    }
    state[x] = -1;
    if (sum[x]==0) {
        if (p) bridges.push_back({x, p});
        F(edges.begin()+sz_, edges.end()); //nodes in component
        edges.resize(sz_);
    }
    if (p) edges.push_back(id_p); 
}