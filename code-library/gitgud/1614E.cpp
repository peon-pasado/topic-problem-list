#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e7;
int maxv[maxn], lazy[maxn];
int minv[maxn];
int L[maxn], R[maxn];
int T;

void create(int nx, int l, int r) {
    int mid = (l+r)/2;
    L[nx] = ++T;
    minv[T] = l;
    maxv[T] = mid;

    R[nx] = ++T;
    minv[T] = mid+1;
    maxv[T] = r;
}

void push(int nx) {
    if (lazy[nx]) {
        int& v = lazy[nx];
        minv[L[nx]] += v;
        maxv[L[nx]] += v;
        lazy[L[nx]] += v;

        minv[R[nx]] += v;
        maxv[R[nx]] += v;
        lazy[R[nx]] += v;
        v = 0;
    }
}

void update(int x, int nx, int l, int r) {
    if (maxv[nx] < x) {
        maxv[nx]++;
        minv[nx]++;
        lazy[nx]++;
        return;
    } 
    if (minv[nx] > x) {
        maxv[nx]--;
        minv[nx]--;
        lazy[nx]--;
        return;
    }
    if (minv[nx] == maxv[nx]) return;
    if (L[nx] == 0) create(nx, l, r);
    push(nx);
    int mid = (l+r)/2;
    update(x, L[nx], l, mid);
    update(x, R[nx], mid+1, r);
    maxv[nx] = maxv[R[nx]];
    minv[nx] = minv[L[nx]];
}

int query(int x, int nx, int l, int r) {
    if (r < x || x < l) return 0;
    if (l == r) return minv[nx];
    if (!L[nx]) create(nx, l, r); 
    push(nx);
    int mid = (l+r)/2;
    if (mid < x) return query(x, R[nx], mid+1, r);
    return query(x, L[nx], l, mid);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int N = 1e9;
    minv[0] = 0;
    maxv[0] = N;
    int n;
    cin>>n;
    int lans = 0;
    for (int i=0; i<n; ++i) {
        int t, k;
        cin>>t>>k;
        update(t, 0, 0, N);
        for (int j=0; j<k; ++j) {
            int x;
            cin>>x;
            x = (x + lans) % (N + 1);
            lans = query(x, 0, 0, N);
            cout << lans << '\n';
        }
    }
    return 0;
}