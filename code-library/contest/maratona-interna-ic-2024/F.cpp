#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;
#define double long double

const double pi = acos(-1);
const double eps = 1e-13;
double a, b, c;

auto tt(double theta) {
    return atan2(a * sin(theta), b * cos(theta));
}

double get_inte(double t, double x) {
    if (abs(2 * x - pi) < eps) return a * b * pi * 0.25 + c * b * 0.5;
    if (abs(x - pi) < eps) return a * b * pi * 0.5;
    if (abs(2 * x - 3 * pi) < eps) return a * b * pi * 0.75 - c * b * 0.5;
    if (abs(x - 2 * pi) < eps) return a * b * pi;

    if (2 * x < pi) t = tt(x);
    else if (x < pi) t = pi - tt(pi - x);
    else if (2 * x < 3 * pi) t = pi + tt(x - pi);
    else t = 2 * pi - tt(2 * pi - x);

    return 0.5 * c * b * sin(t) + 0.5 * a * b * t;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << setprecision(10) << fixed;
    int t;
    cin>>t;
    while (t--) {
        double p;
        cin>>b>>c>>p;
        a = sqrtl(b*b + c*c);
        double tot = a * b * p * pi / 100;
        double lo = 0, hi = 2 * pi;
        for (int i=0; i<200; ++i) {
            double mid = (lo + hi) / 2;
            auto inte = get_inte(0., mid);
            if (inte < tot) lo = mid;
            else hi = mid;
        }
        double t = 0;
        if (lo < pi / 2) t = atan2(a * sin(lo), b * cos(lo));
        else if (abs(lo - pi / 2) < eps) t = pi/2; 
        else if (lo < pi) t = pi - atan2(a * sin(pi - lo), b * cos(pi - lo)); 
        else if (abs(lo - pi) < eps) t = pi;
        else if (lo < 3 * pi / 2) t = pi + atan2(a * sin(lo - pi), b * cos(lo - pi));
        else if (abs(lo - 3 * pi / 2) < eps) t = 3 * pi / 2;
        else if (abs(lo - 2 * pi) < eps) t = 2 * pi;
        else t = 2 * pi - atan2(a * sin(2 * pi - lo), b * cos(2 * pi - lo));

        cout << a * cos(t) << ' ' << b * sin(t) << '\n';
    }

    return 0;
}