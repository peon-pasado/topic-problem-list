#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
vector<pair<int, char>> g[maxn];
int nxt[maxn];
char val[maxn];
bool cmp(int i, int j) {
    for (; nxt[i] > 0 && nxt[j] > 0; i = nxt[i], j = nxt[j]) {
        if (val[i] > val[j]) return 1;
        if (val[j] > val[i]) return 0;
    }
    return val[i] != 0;
}

vector<int> suffix_array(vector<int> &s) {
	int n = s.size();
	vector<int> a(n);
	vector<int> mapeo(n);
	iota(a.begin(), a.end(), 0);
	sort(a.begin(), a.end(), [&] (int i, int j){
		return s[i] < s[j];
	});
	mapeo[a[0]] = 0;
	for(int i = 1; i < n; i++){
		mapeo[a[i]] = mapeo[a[i - 1]] + (s[a[i - 1]] != s[a[i]]);
	}
	int len = 1;
	vector<int> head(n);
	vector<int> new_mapeo(n);
	vector<int> sorted_by_second(n);
	while(len < n){
		for(int i = 0; i < n; i++) sorted_by_second[i] = (a[i] + n - len) % n;
		for(int i = n - 1; i >= 0; i--) head[mapeo[a[i]]] = i;
		for(int i = 0; i < n; i++){
			int x = sorted_by_second[i];
			a[head[mapeo[x]]++] = x;
		}
		new_mapeo[a[0]] = 0;
		for(int i = 1; i < n; i++){
			if(mapeo[a[i]] != mapeo[a[i - 1]]){
				new_mapeo[a[i]] = new_mapeo[a[i - 1]] + 1;
			}
			else{
				int pre = mapeo[(a[i - 1] + len) % n];
				int cur = mapeo[(a[i] + len) % n];
				new_mapeo[a[i]] = new_mapeo[a[i - 1]] + (pre != cur);
			}
		}
		swap(mapeo, new_mapeo);
		len <<= 1;
	}
	return a;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        for (int i=1; i<=n; ++i) g[i].clear(), val[i] = 0;
        for (int i=2; i<=n; ++i) {
            int pi;
            char c;
            cin>>pi>>c;
            g[pi].emplace_back(i, c);
        }
        for (int i=n; i >= 1; --i) {
            if (g[i].empty()) nxt[i] = -1;
            else {
                char x = 'a';
                for (auto [u, c] : g[i]) {
                    x = max(x, c);
                }
                int v = -1;
                for (auto [u, c] : g[i]) {
                    if (x == c) {
                        if (v == -1 || cmp(u, v)) {
                            v = u;
                        }
                    }
                }
                //cout << i << " -- " << nxt[i] << endl;
                nxt[i] = v;
                val[i] = x;
            }
        }
        vector<bool> vis(n + 1);
        string r = "";
        vector<int> sz(n + 1);
        for (int i=1; i<=n; ++i) {
            if (vis[i] == 1) continue;
            //if (nxt[i] == -1) continue;
            vector<int> s;
            for (int j = i; nxt[j] > 0; j = nxt[j]) {
                vis[j] = 1;
                s.push_back(val[j]);
            }
            int nn = s.size();
            for (int j = i; nxt[j] > 0; j = nxt[j]) {
                sz[j] = nn--;
            }
            s.push_back(-1);
            int idx = suffix_array(s).back();
            string ss;
            for (int i=idx; i+1<s.size(); ++i) {
                ss += s[i];
            }
            r = max(r, ss);
        }
        for (int i=1; i<=n; ++i) {
            cout << sz[i] << " \n"[i==n];
        }
        cout << r << '\n';
    }

    return 0;
}