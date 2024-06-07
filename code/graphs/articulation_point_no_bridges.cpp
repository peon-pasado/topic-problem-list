#include<bits/stdc++.h>
using namespace::std;

const int N = 400000 + 5;

int n;
int m;
int a;
int b;
int c;
int cnt;
int len;
int timer;
int tin[N];
int low[N];
int vis[N];
stack<int> S;
int parent[N];
vector<int> G[N];
vector<int> T[N];

void add_edge(int u, int v) {
	T[u].emplace_back(v);
	T[v].emplace_back(u);
}

void DFS(int u, int p = -1) {
	low[u] = tin[u] = ++timer;
	S.emplace(u);
	for(int v : G[u]) {
		if(v == p) continue;
		if(tin[v]) low[u] = min(low[u], tin[v]);
		else {
			DFS(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] == tin[u]) {
				cnt += 1;
				add_edge(u, cnt);
				int y;
				do {
					y = S.top(); S.pop();
					add_edge(cnt, y);
				} while(y != v);
			}
		}
	}
}

int main() {
	cin>>n>>m;
	cnt = n;
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
 		G[v].emplace_back(u);
	}
	DFS(1);
    for (int v=1; v<=n; ++v) {
        cout << v << ": ";
        for (int u : T[v]) {
            cout << u << ' ';
        }
        cout << endl;
    }
	return 0;
}