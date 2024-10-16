#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 1;
bitset<maxn> b[61], aux;
string msk[maxn];
bitset<maxn> ss[20];
vector<int> pos;
int l;
long long tans = 0;
int sans = 0;
int n;
int taked = 0;

void backtrack(int i, long long mask) {
    if (taked + (l - i) <= sans) return;
    if (ss[i].count() < (n+1)/2) return;
    if (i == l) {
        if (taked > sans && ss[l].count() >= (n+1)/2) {
            sans = taked;
            tans = mask;
        }
        return;
    }
    ss[i+1] = (ss[i] & b[pos[i]]);
    taked++;
    backtrack(i+1, mask | (1ll<<pos[i]));
    taked--;
    ss[i+1] = ss[i];
    backtrack(i+1, mask);
    
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int m, p;
    cin>>n>>m>>p;
    for (int i=0; i<n; ++i) {
        string s;
        cin>>s;
        for (int j=0; j<m; ++j) {
            if (s[j] == '1') b[j][i] = 1;
        }
        msk[i] = s;
    }
    ss[0].set();
    for (int i=0; i<9; ++i) {
        int x = uniform_int_distribution<int>(0, n-1)(rng);
        pos.clear();
        for (int j=0; j<m; ++j)
            if (msk[x][j] == '1') pos.push_back(j);
        l = pos.size();
        backtrack(0, 0ll);
    }
    for (int i=0; i<m; ++i) 
        cout << ((tans>>i) & 1);
    cout << '\n';
    return 0;
}
