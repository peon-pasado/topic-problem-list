```c++
struct dsu_rollback {

    vector<int> parent;
    vector<size_t> subtree_sz;
    stack<int> changes;

    dsu_rollback(int n) {
        parent.resize(n);
        iota(all(parent), 0);
        subtree_sz.resize(n, 1);
    }

    int get_root(int x) {
        return parent[x] != x ? get_root(parent[x]) : x;
    }

    void merge(int u, int v) {
        u = get_root(u); v = get_root(v);
        if (u == v) {
            return changes.push(-1);
        }
        if (subtree_sz[u] < subtree_sz[v]) swap(u, v);
        
        subtree_sz[u] += subtree_sz[v];
        parent[v] = u;
        changes.push(v);
    } 

    bool same(int u, int v) {
        return get_root(u) == get_root(v);
    }

    void undo() {
        if (changes.empty()) return;
        if (changes.top() >= 0) {
            int v = changes.top();
            subtree_sz[parent[v]] -= subtree_sz[v];
            parent[v] = v;          
        }
        changes.pop();
    }
};

struct Edge {
    int u, v;
};

/**
 * supporting remove first update
*/

struct QueueLike {
    using event = pair<bool, Edge>;
    dsu_rollback dsu;
    vector<event> changes;
    int m;

    QueueLike(int n): dsu(n), m(0) {}

    void merge(int u, int v) {
        changes.push_back({1, {u, v}});
        dsu.merge(u, v);
    }

    void pop() {
        assert(!changes.empty());
        if (m == 0) {
            m = changes.size();
            for (int i=0; i<m; ++i) dsu.undo();
            reverse(all(changes));
            for (auto& [t, e] : changes) {
                assert(t == 1);
                t=0; dsu.merge(e.u, e.v);
            }
        }
        if (changes.back().first) {
            vector<stack<event>> tmp(2);
            while (changes.back().first) {
                tmp[1].push(changes.back());
                dsu.undo();
                changes.pop_back();
            }
            int lso = (m & -m);
            for (int i=0; i<lso; ++i) {
                assert(!changes.back().first);
                tmp[0].push(changes.back());
                dsu.undo();
                changes.pop_back();
            }
            for (int i=1; i>=0; --i) {
                while (!tmp[i].empty()) {
                    auto [t, e] = tmp[i].top(); tmp[i].pop();
                    dsu.merge(e.u, e.v);
                    changes.push_back({t, e});
                }
            }
        }
        changes.pop_back();
        dsu.undo();
        m--;
    }
};
```