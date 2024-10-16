#include <bits/stdc++.h>
using namespace std;

int main() {
    int m;
    cin>>m;
    string n;
    cin>>n;
    reverse(n.begin(), n.end());
    for (auto& c : n) c = (c - '0') * 2;
    int last = 1;
    for (int i=0; i<m; ++i) {
        n[i] += last;
        last = n[i] / 10;
        n[i] %= 10;
    }
    while (last > 0) {
        n += last % 10;
        last /= 10;
    }
    for (auto& c : n) c += '0';
    reverse(n.begin(), n.end());
    cout << n << '\n';
    return 0;
}