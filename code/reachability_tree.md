```c++
struct reachability_tree {
    vector<vector<int>> tree;
    vector<int> parent;
    vector<int> value;
    vector<int> ord;
    int n;

    reachability_tree(int n): n(n) {
        tree.resize(2 * n - 1);
        value.resize(2 * n - 1);
        parent.resize(2 * n - 1);
        iota(all(parent), 0);
    }

    int get_root(int x) {
        return x != parent[x] ? parent[x] = get_root(parent[x]) : x;
    }

    void merge(int x, int y, int time) {
        x = get_root(x); y = get_root(y);
        if (x == y) return;
        parent[x] = parent[y] = n;
        value[n] = time;
        parent[n] = n;
        tree[n] = {x, y};
        n++;
    }
};

const int maxn = 1e5 + 5;
int st[19][2 * maxn]; // 19 = floor(log(leaves - 1)) + 1
int range[2 * maxn][2];
int ord[maxn];
int T;

void dfs(int x, int p, auto& dsu) {
    if (g[x].empty()) {
        range[x][0] = range[x][1] = ord[x] = T++;
        return;
    }
    range[x][0] = INT_MAX;
    range[x][1] = INT_MIN;
    for (int i=0; i<2; ++i) {
        int v = dsu.g[x][0];
        dfs(v, x, dsu);
        range[x][0] = min(range[x][0], range[v][0]);
        range[x][1] = max(range[x][1], range[v][1]);
    }
}

void make_jumps(auto& dsu) {
    T = 0;
    int n = dsu.n;  
    for (int i=n-1; i>=0; --i) {
        st[0][i] = dsu.parent[i];
        for (int k=1; k<=18; ++k) { 
            st[k][i] = st[k-1][st[k-1][i]];
        }
    }
    for (int i = 0; i < n; ++i) {
        if (st[0][i] == i) {
            dfs(i, -1, dsu);
        }
    }
}

int get_value(int x, int s, auto& dsu) {
    for (int k=18; k>=0; --k) {
        if (range[st[k][x]][1] - range[st[k][x]][0] + 1 <= s) {
            x = st[k][x];
        }
    }
    return dsu.value[x];
}

pair<int, int> get_range(int x, int v, auto& dsu) {
    for (int k=18; k>=0; --k) {
        if (dsu.value[st[k][x]] <= v) {
            x = st[k][x];
        }
    }
    return {range[x][0], range[x][1]};
}
```