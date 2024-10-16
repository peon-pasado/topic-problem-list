#include <vector>
using namespace std;

const int maxn = 1e5 + 10;
vector<int> g[maxn];
vector<pair<int,int>> bridges;
vector<int> nodes;
int sum[maxn];
short state[maxn];

template<class Func>
void dfs(int x, int p, Func& F) {
    int sz_ = nodes.size();
    nodes.push_back(x);
    sum[x] = 0;
    state[x] = 1;
    for (int u : g[x]) {
        if (u==p) continue;
        if (state[u]==0) {
            dfs(u, x, F);
            sum[x] += sum[u];
        } else {
            sum[x] += state[u];
        }
    }
    state[x] = -1;
    if (sum[x]==0) {
        if (p) bridges.push_back({x, p});
        F(nodes.begin()+sz_, nodes.end()); //nodes in component
        nodes.resize(sz_);
    }
}


void dfs(int x, int p) {
    sum[x] = 0; //mantenes la suma en la arista (p, x)
    state[x] = 1;
    for (int u : g[x]) {
        if (u==p) continue;
        if (state[u]==0) {
            dfs(u, x);
            //subir la suma a la arista padre
            sum[x] += sum[u]; 
        } else if (state[u] == 1){
            //aumentar en 1 hacia arriba
            sum[x] += 1;
        } else if (state[u] == -1) {
            //disminuir en 1 desde abajo
            sum[x] -= 1;
        }
    }
    state[x] = -1;
    if (sum[x] == 0 && p != -1) {
        //(p, x) es un puente
    }
}
