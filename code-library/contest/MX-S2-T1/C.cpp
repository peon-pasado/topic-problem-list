#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e3 + 10;
int f[maxn][maxn];

//f[i][j] = f[i-1][i-1] + sum_{i <= k <= j} sum_{d | k} f[d][i-1]

//f[i][i] = f[i-1][i-1] + sum_{d | i} f[d][i-1]; 
//f[i][j] = f[i][j - 1] + sum_{d | j} f[d][i-1];

int main() {
    int n, p;
    cin>>n>>p;
    f[0][0] = 1;
    for (int i=1; i<=n; ++i) {
        for (int d=1; d<i; ++d) {
            for (int j=2*d; j<=n; j += d) {
                f[i][j] += f[d][i-1];
                if (f[i][j] >= p) f[i][j] -= p;
            }
        }
        f[i][i] += f[i-1][i-1];
        if (f[i][i] >= p) f[i][i] -= p;
        for (int j=i+1; j<=n; ++j) {
            f[i][j] += f[i][j-1];
            if (f[i][j] >= p) f[i][j] -= p;
        }        
    }
    cout << f[n][n] << '\n';
    return 0;
}