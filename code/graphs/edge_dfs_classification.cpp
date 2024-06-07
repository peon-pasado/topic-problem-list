

const int maxn = 5e5 + 10;
vector<int> g[maxn];
int state[maxn];
void dfs(int x, int parent) {
    state[x] = 1; //visitando sub-arbol
    for (int u : g[x]) {
        //clasificacion de arista (x, u)
        if (u == parent) continue; //arista hacia atras especial
        if (state[u] == 0) {//estado no visitado
            dfs(u, x);
        } else if (state[u] == 1) {
            //arista hacia atras
        } else if (state[u] == -1) {
            //arista hacia adelante
        }
    }
    state[x] = -1; //terminar de visitar un sub-arbol
}
