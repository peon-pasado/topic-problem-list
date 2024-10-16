#include <bits/stdc++.h>
using namespace std;

long long mdc(long long a, long long b){
     long long loops = 0; // contador para fins da questão apenas
     while (a != b) {
        if (a > b) {
            if (a % b == 0) return loops + a / b - 1;
            loops += a / b;
            a %= b;
        } else {
            if (b % a == 0) return loops + b / a - 1;
            loops += b / a;
            b %= a;
        }
     }
     return loops;
}

int main() {
    long long t;
    cin>>t;
    while (t--) {
        long long a, b;
        cin>>a>>b;
        cout << mdc(a, b) << '\n';
    }
    return 0;
}