#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> arr = {1, 2, 3, 4};

    for (auto v : arr | views::transform([](int i) {
        return i * i;
    })) {
        cout << v << endl;
    }


    return 0;
}