#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
int a[maxn];
int F[1<<22];
int n;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n;
    for (int i=0; i<n; ++i) {
        cin>>a[i];
    }
    for (int i=0; i<n; ++i) {
        F[a[i]] = a[i];
    }
    for (int i=0; i<22; ++i) {
        for (int j=0; j<(1<<22); ++j) {
            if (j & (1<<i)) {
                F[j] = max(F[j], F[j ^ (1<<i)]);
            }
        }
    }
    for (int i=0; i<n; ++i) {
        int other = F[((1<<22)-1) ^ a[i]];
        if (other == 0) other--;
        cout << other << " \n"[i+1==n];
    }
    return 0;
}