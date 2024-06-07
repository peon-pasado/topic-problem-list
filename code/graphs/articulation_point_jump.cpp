#include <vector>
using namespace std;

const int maxn = 1e5 + 10;
vector<pair<int, int>> g[maxn];
vector<pair<int, int>> E;
int lo[maxn], up[maxn];
int state[maxn];
bool cut[maxn];
vector<int> edges;
int ti;

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
    int child = 0;
    for (auto [u, id] : g[x]) {
        if (u == p) continue;
        if (state[u]==0) {
            child++;
            int sz_ = edges.size();
            //note que la arista de arbol
            //es colocada primero, esto
            //es debido a que si es un bridge
            //forma una propia BCC (degenerada)
            edges.push_back(id);
            dfs(u, x, F);
            up[x] = min(up[x], up[u]); 
            if ((p==0 && child > 1) || (p!=0 && lo[x] <= up[u])) {
                cut[x] = 1;
                //note que x es el punto de corte 
                //mas arriba que tiene.
                F({edges.begin() + sz_, edges.end()});
                edges.resize(sz_);
            }
        } else {
            up[x] = min(up[x], lo[u]);
            edges.push_back(id);
        }
    }
    state[x] = -1;
    //en caso de que toda la componente sea BCC
    if (p == 0 && !edges.empty()) {
        F(edges);
        edges.clear();
    }
}

int bcc_color = 0;
int comp[maxn]; //M
vector<int> block_t[2 * maxn]; //N + M
int comp_node[maxn];
//agregamos el nodo u al bloque c, en caso de no ser un 
//corte este bloque es unico.
void add_bedge(int u, int c) {
    if (cut[u]) {
     if (block_t[u].empty() || block_t[u].back() != c)
        block_t[u].push_back(c);
    } else {
        comp_node[u] = c;
    }
}

//analizamos las aristas del bloque
void BlockCutTree(vector<int>&& edges) {
    //|edges| == 1 -> bridge
    for (auto id : edges) {
        comp[id] = bcc_color;
        auto [a, b] = E[id];
        add_bedge(a, bcc_color);
        add_bedge(b, bcc_color);
    }
    bcc_color++;
}

