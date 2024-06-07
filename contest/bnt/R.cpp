#include <iostream>
using namespace std;

int gcdex(int a, int b, int& x, int& y) {
    if (!b) return x=1, y=0, a;
    int g = gcdex(b, a%b, y, x);
    return y -= a/b*x, g;
}

int x, y, m, n, L;
inline int modL(long long x) { return x % L + (x<0) * L;}

int main() {
    cin>>x>>y>>m>>n>>L;
    int A = modL(x-y);
    int B = modL(n-m);
    int x0, y0, g = gcdex(B, L, x0, y0);
    if (A % g != 0) return cout<<"Impossible"<<'\n', 0;
    A /= g; L /= g;
    int k = modL(1LL * x0 * A);
    cout << k << '\n';
    return 0;
}