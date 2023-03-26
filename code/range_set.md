```c++
const int inf = 1e9;
struct range_set {

    set<pair<pair<int, int>, int>> s;

    range_set() {}

    int intersect(pair<int, int> p, pair<int, int> q) {
        return min(p.second, q.second) - max(p.first, q.first) + 1;
    }

    int add(int l, int r, int x, int delta) {
        auto q = s.lower_bound({{l, r}, -inf});
        if (q != s.begin()) q = prev(q);
        int sum = 0;
        if (q != s.end()) {
            //cout << "here" << endl;
            auto L = q;
            if (intersect(L->first, {l, r}) <= 0) L = next(L);
            auto R = L;
            while (R != s.end() && intersect(R->first, {l, r}) > 0) R = next(R);
            vector<pair<pair<int, int>, int>> to_add;
            for (auto it = L; it != R; ++it) {
                //cout << "iteration" << endl;
                int tot = intersect(it->first, {l, r});
                if (x - delta >= it->second) sum += tot;
                if (it->first.first < l) to_add.push_back({{it->first.first, l - 1}, it->second});
                if (r < it->first.second) to_add.push_back({{r + 1, it->first.second}, it->second});
            }
            s.erase(L, R);
            for (auto r : to_add) s.insert(r);
        }
        s.insert({{l, r}, x});
        return sum;
    }   
};
```