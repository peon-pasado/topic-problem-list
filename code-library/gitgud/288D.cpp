/**
 * @topics: combinatorics, dp, tree
 * @idea:
 *      - count for every separator path, the number of paths in both extremes
 *      - this method overcount if we select every edge in this path
 *      - only count for extreme edges in separator path
 *      - this method overcount too:
 * 
 *                  x _
 *                 / \  \
 *                u  v   w
 *      
 *      u count subtree paths from v and w, v count from u and w, and so on 
 *      (note that some paths are count twice and others not)
 *   
 *      - observation: to no count paths in visited subtrees, we can divide
 *      in three regions. 
 * 
 *          a. x subtree
 *          b, visited but not in a and not in root-path
 *          c. others
 *  
 *      now we need count paths going from x in (a) multiplied by paths in ((C) u paths going from (b) to (c))
 * 
 *      ((C) u paths going from (b) to (c)) == paths in (b) u (C) - (paths in (b)).
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 8e4 + 20l;
vector<int> g[maxn];
long long ans;
long long dp[maxn];
long long sz[maxn];
int n;

long long calc(long long n) {
    return n * (n - 1) / 2;
}

void dfs(int x, int p, long long d) {
    sz[x] = 1;
    for (int v : g[x]) {
        if (v == p) continue;
        dfs(v, x, d);
        dp[x] += sz[x] * sz[v];
        sz[x] += sz[v]; 
        ans += dp[v] * (calc(n - sz[v]) - d);
        d += calc(sz[v]);
    }
}

int main() {
    cin>>n;
    for (int i=0; i<n-1; ++i) {
        int u, v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0, 0ll);
    cout << 2 * ans << endl;
    return 0;
}