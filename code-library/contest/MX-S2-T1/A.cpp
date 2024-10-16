#include <bits/stdc++.h>
using namespace std;

int main() {
    int k;
    string s;
    cin>>k>>s;
    int n = s.size();
    vector<int> divisors;
    for (int i=1; i*i<=n; ++i) {
        if (n % i == 0) {
            divisors.emplace_back(i);
            if (i*i!=n) {
                divisors.emplace_back(n/i);
            }
        }
    }
    sort(divisors.begin(), divisors.end());
    for (int d : divisors) {
        int res=0;
        for (int i=0; i<d; ++i) {
            vector<int> cnt(26);
            for (int j=i; j<n; j += d) {
                cnt[s[j] - 'a']++;
            }       
            res += n/d - *max_element(cnt.begin(), cnt.end());
        }
        if (res <= k) {
            cout << d << '\n';
            break;
        }
    }
    return 0;
}