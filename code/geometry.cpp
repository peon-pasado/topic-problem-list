#include <bits/stdc++.h>
#define sz(v) ((int)v.size())
using namespace std;

// Redefine epsilon and infinity as necessary. Be mindful of precision errors.
const long double eps = 1e-9, inf = 1e9; 

template<typename T>
struct Point {
    using P = Point;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}

    template<class U>
    explicit operator Point<U> () const {return Point<U>(x, y);}

    P operator+(P other) const {return P(x+other.x, y+other.y);}
    P operator-(P other) const {return P(x-other.x, y-other.y);}
    P operator*(const T& c) const {return P(x*c, y*c);}
    P operator/(const T& c) const {return P(x/c, y/c);}
    
    friend T dot(const P& p, const P& q) {return p.x * q.x + p.y * q.y;}
    friend T ccw(const P& p, const P& q) {return p.x * q.y - p.y * q.x;} 
    friend P perp(const P& p) {return P(-p.y, p.x);}
    friend double norm(const P& p) {return sqrtl(dot(p, p));}
    friend double dist(const P& p, const P& q) {return norm(p-q);}
    friend double angle(const P& p) {return atan2l(p.y, p.x);}
    friend istream& operator>>(istream& is, P& other) {return is >> other.x >> other.y;}
    friend ostream& operator<<(ostream& os, const P& other) {return os << other.x << " " << other.y;}

    bool operator<(const P& p) const {return x < p.x || (x == p.x && y < p.y);}
    bool operator>(const P& p) const {return p < *this;}
    bool operator==(const P& p) const {return x == p.x && y == p.y;}
};

template<typename T>
struct Line { 

    Point<T> a, ab; 

    Line() {}
    Line(const Point<T>& a, const Point<T>& b) : a(a), ab(b - a) {}

    Point<T> b() const {return a + ab;}

    template<typename U>
    explicit operator Line<U>() const {return Line<U>(Point<U>(a), Point<U>(b()));} 

    friend bool operator<(const Line& r, const Line& s) {        
        if (r.a < r.b() == s.a < s.b()) return ccw(r.ab, s.ab) > eps;
        return r.a < r.b();
    }

    friend Point<T> inter(const Line& I, const Line& J) {
        return I.a + I.ab * ccw(J.a - I.a, J.ab) / ccw(I.ab, J.ab);
    }

    friend bool out(const Line& I, const Point<T> p) {
        return ccw(I.ab, p - I.a) < 0;
    }

    //friend bool test(const Line& H, const Line& I, const Line& J) {
    //    return out(H, inter(I, J));
    //}

    friend bool test(const Line& H, const Line& I, const Line& J) { //infinite precision (needs integer type)
        if (ccw(I.ab, J.ab) > 0)
            return (__int128_t)ccw(H.ab, I.a - H.a) * ccw(I.ab, J.ab) < (__int128_t)ccw(J.ab, J.a - I.a) * ccw(H.ab, I.ab);
        else
            return (__int128_t)ccw(H.ab, I.a - H.a) * ccw(I.ab, J.ab) > (__int128_t)ccw(J.ab, J.a - I.a) * ccw(H.ab, I.ab);
    } 
};

template<typename T>
struct Frac {
    T x, y;

    Frac() {}
    Frac(T x, T y): x(x), y(y) {}
    Frac(long long x): x(x), y(1) {}

    long double operator()() const {return (long double) x / y;}
    Frac operator+(const Frac& p) const {return Frac(x * p.y + p.x * y, y * p.y);}
    Frac operator-(const Frac& p) const {return Frac(x * p.y - p.x * y, y * p.y);}
    Frac operator*(const T& k) const {return Frac(x * k, y);}
    Frac operator/(const T& k) const {return k > 0 ? Frac(x, y * k) : Frac(-x, -y * k);}
    Frac operator*(const Frac& p) const {return Frac(x * p.x, y * p.y);} 
    Frac operator/(const Frac& p) const {return Frac(x * p.y, y * p.x);} 
    bool operator<(const Frac& p) const {return x * p.y < p.x * y;}
    bool operator>(const Frac& p) const {return p < *this;}
    bool operator==(const Frac& p) const {return !(*this < p) && !(p < *this);}
};


template<typename T>
vector<Line<T>> hp_intersect(vector<Line<T>>& H) { 
    sort(H.begin(), H.end());
    deque<Line<T>> dq;
    for(auto h : H) {
        while (sz(dq) > 1 && test(h, dq[sz(dq)-1], dq[sz(dq)-2])) dq.pop_back();
        while (sz(dq) > 1 && test(h, dq[0], dq[1])) dq.pop_front();
        if (sz(dq) > 0 && fabs(ccw(h.ab, dq[sz(dq)-1].ab)) < eps) {
            if (ccw(h.ab, dq[sz(dq)-1].a - h.a) < -eps) dq.back() = h;
        } else dq.push_back(h);
    }
    while (sz(dq) > 2 && test(dq[0], dq[sz(dq)-1], dq[sz(dq)-2])) dq.pop_back();
    if (sz(dq) < 3) return {};
    return {dq.begin(), dq.end()};
}

template<typename T, typename U>
vector<Point<U>> get_points(vector<Line<T>> H) {
    vector<Point<U>> ret(sz(H));
    for(int i = 0; i < sz(H); i++) ret[i] = inter((Line<U>)H[i], (Line<U>)H[(i+1)%sz(H)]);
    auto equals = [&](const Point<U>& p, const Point<U>& q) {return p == q;};
    ret.erase(unique(ret.begin(), ret.end(), equals), ret.end());
    if (sz(ret) > 1 && equals(ret.back(), ret[0])) ret.pop_back();
    return ret;
}

int next(int i, int n) {
    return (i + 1) % n;
}

int back(int i, int n) {
    return (i + n - 1) % n;
}

template<class P>
long double sign_area(vector<P> p) {
    int n = p.size();
    long double res = 0.;
    for (int i=0;i<n; ++i) {
        res += ccw(p[i], p[next(i, n)]);
    }
    return res;
}

template<typename T>
struct Line { 

    T c;
    Point<T> v;

    Line() {}
    Line(const T& a, const T& b, const T& c) : v(a, b), c(c) {}

    template<typename U>
    explicit operator Line<U>() const {return Line<U>(U(v.x), U(v.y), U(c));} 

    friend bool operator<(const Line& r, const Line& s) {        
        if (Point<T>() < r.v == Point<T>() < s.v) return eps < ccw(r.v, s.v);
        return Point<T>() < r.v;
    }

    friend Point<T> inter(const Line& I, const Line& J) {
        T det = ccw(I.v, J.v); 
        T dx = ccw(Point<T>(-I.c, I.v.y), Point<T>(-J.c, J.v.y));
        T dy = ccw(Point<T>(I.v.x, -I.c), Point<T>(J.v.x, -J.c));
        return Point(dx, dy) / det;
    }

    friend bool out(const Line& I, const Point<T> p) {
        return eps < dot(I.v, p) + I.c;
    }

    friend bool test(const Line& H, const Line& I, const Line& J) {
        return out(H, inter(I, J));
    }

    friend bool dismiss(const Line& I, const Line& J) {
        //I.v.x / J.v.x * J.c <= I.c 
        if (fabs(J.v.x) > eps) {
            if (eps < J.v.x) return I.v.x * J.c <= J.v.x * I.c;
            return J.v.x * I.c <= I.v.x * J.c;
        } else {
            if (eps < J.v.y) return I.v.y * J.c <= J.v.y * I.c; 
            return J.v.y * I.c <= I.v.y * J.c;
        }
        return 0;
    }
};


//half plane intersection with Halfplane := ax + by + c <= 0
template<typename T>
vector<Line<T>> hp_intersect(vector<Line<T>>& H) { 
    sort(H.begin(), H.end());
    deque<Line<T>> dq;
    for(auto h : H) {
        while (sz(dq) > 1 && test(h, dq[sz(dq)-1], dq[sz(dq)-2])) dq.pop_back();
        while (sz(dq) > 1 && test(h, dq[0], dq[1])) dq.pop_front();
        if (sz(dq) > 0 && fabs(ccw(h.v, dq[sz(dq)-1].v)) < eps) {
            if (dismiss(dq[sz(dq)-1], h)) dq.back() = h;
        } else dq.push_back(h);
    }
    while (sz(dq) > 2 && test(dq[0], dq[sz(dq)-1], dq[sz(dq)-2])) dq.pop_back();
    if (sz(dq) < 3) return {};
    return {dq.begin(), dq.end()};
}

//halfplane intersection en O(n) by halfplane.
template<typename T>
vector<Point<T>> update(Line<T>& H, vector<Point<T>> p) { 
    vector<Point<T>> res;
    auto eval = [&](Line<T> H, Point<T> p) {
        return H.v.x * p.x + H.v.y * p.y + H.c > eps;
    };
    auto inter = [&](Line<T> H, Point<T> p, Point<T> q) {
        auto u = fabs(H.v.x * p.x + H.v.y * p.y + H.c);
        auto v = fabs(H.v.x * q.x + H.v.y * q.y + H.c);
        return Point<T>((p.x * v + q.x * u) / (u + v), (p.y * v + q.y * u) / (u + v));
    };
    for (int i = 0; i < sz(p); ++i) {
        if (eval(H, p[i])) res.push_back(p[i]);
        else {
            if (eval(H, p[back(i, sz(p))])) res.push_back(inter(H, p[i], p[back(i, sz(p))]));
            if (eval(H, p[next(i, sz(p))])) res.push_back(inter(H, p[i], p[next(i, sz(p))]));
        }
    }
    return res;
}


//given a circle(c, r) and a line(a, b), obtain intersection if exists.
pair<Point<double>, Point<double>> intersection_CL(Point<double> c, double r, Point<double> a, Point<double> b) {
    if (a == c) swap(a, b);
    Point<double> v(b - a);
    Point<double> A(c - a);
    double norm_v = dot(v, v);
    double X = dot(v, A);
    double Y = ccw(v, A);
    double d = sqrtl(r * r * norm_v - Y * Y); 
    Point<double> r1 = a + v * (X + d) / norm_v;
    Point<double> r2 = a + v * (X - d) / norm_v;
    if (r2 < r1) swap(r1, r2);
    return {r1, r2};
}

template<typename T>
struct Segment {
    using S = Segment<T>;
    using P = Point<T>;
    P a, ab;
    bool line;
    Segment() {}
    Segment(P a, P b, bool line=0): a(a), ab(b - a), line(line) {}
    P b() {return a + ab;}


    friend bool to_left(S s, P p) {
        return ccw(s.ab, p-s.a) > eps;
    }

    friend pair<bool, P> intersect(S p, S q) {
        T s = ccw(p.ab, q.ab);
        if (abs(s) < eps) {
            if (abs(ccw(q.a - p.a, p.ab)) < eps) { 
                if (p.line || q.line) return {1, p.a};
                P la = p.a, lb = p.b();
                P ra = q.a, rb = q.b();
                if (lb < la) swap(la, lb);
                if (rb < ra) swap(ra, rb);
                return {max(la, ra) <= min(lb, rb), max(la, ra)};
            } 
            return {0, P()};
        }
        T t1 = ccw(q.ab, p.a - q.a);
        T t2 = ccw(p.ab, p.a - q.a);
        if (s < 0) t1 = -t1, t2 = -t2, s = -s;
        bool r1 = (0 <= t1 && t1 <= s) || p.line;
        bool r2 = (0 <= t2 && t2 <= s) || q.line;
        return {r1 && r2, p.a + p.ab * t1 / s};
    }

    friend double dist(S s, P p) {
        if (!s.line) {
            if (dot(p - s.a, s.ab) <= 0) return dist(p, s.a);
            if (dot(p - s.b(), s.ab) >= 0) return dist(p, s.b());
        }
        return abs(ccw(p - s.a, s.ab)) / norm(s.ab);
    }

    friend bool operator<(S r, S s) {
        if (P() < r.ab == P() < s.ab) {
            return ccw(r.ab, s.ab) > eps;
        }
        return P() < r.ab;
    }    
};

pair<Point<double>, double> incenter(Point<double> a, Point<double> b, Point<double> c) {
    Point<double> ua = b - a;
    Point<double> va = c - a;
    Point<double> ub = a - b;
    Point<double> vb = c - b;
    Segment<double> s1(a, ua * norm(va) + va * norm(ua) + a);
    Segment<double> s2(b, ub * norm(vb) + vb * norm(ub) + b);
    Point<double> ce = intersect(s1, s2).second;
    return make_pair(ce, abs(ccw(b-a, ce-a) / norm(b-a)));
}

pair<Point<double>, double> circuncenter(Point<double> a, Point<double> b, Point<double> c) {
    Segment<double> s1(a+b, perp(b-a) + a+b, 1);
    Segment<double> s2(a+c, perp(c-a) + c+a, 1);
    Point<double> ce = intersect(s1, s2).second / 2;
    return make_pair(ce, dist(a, ce));
}

pair<Point<double>, Point<double>> intersect_CC(Point<double> c1, double r1, Point<double> c2, double r2) {
    Point<double> v(c2 - c1);
    double d = norm(v);
    double x = 0.5 * (d + (r1*r1 - r2*r2) / d);
    double t = sqrtl(r1*r1 - x*x);
    Point<double> i1 = c1 + (v * x + perp(v) * t) / d;
    Point<double> i2 = c1 + (v * x - perp(v) * t) / d;
    if (i2 < i1) swap(i1, i2);
    return make_pair(i1, i2);
}

Point<double> rotate(Point<double> p, double a, double b, double c) {
    return Point<double>(p.x * b - p.y * a, p.x * a + p.y * b) / c;
}


vector<Point<double>> tangentCC(Point<double> c1, double r1, Point<double> c2, double r2) {
    auto cc = c1;
    double rc = r1;
    if (r1 < r2) {
        swap(r1, r2);
        swap(c1, c2);
    }
    vector<Point<double>> vect;
    double d12 = dist(c1, c2);
    if (d12 + r2 > r1) {
        double a = r1 - r2;
        double c = norm(c1 - c2);
        double b = sqrtl(c*c - a*a);
        Point<double> v = c1 - c2;
        Point<double> u1 = perp(rotate(Point<double>() - v, -a, b, c));
        Point<double> u2 = perp(rotate(v, a, b, c));

        Point<double> r11 = c1 + u1 * r1 / norm(u1);
        Point<double> r12 = c2 + u1 * r2 / norm(u1);

        if (fabs(dist(cc, r11) - rc) < eps) vect.push_back(r11);
        if (fabs(dist(cc, r12) - rc) < eps) vect.push_back(r12);

        Point<double> r21 = c1 + u2 * r1 / norm(u2);
        Point<double> r22 = c2 + u2 * r2 / norm(u2);

        if (fabs(dist(cc, r21) - rc) < eps) vect.push_back(r21);
        if (fabs(dist(cc, r22) - rc) < eps) vect.push_back(r22);

    } else if (fabs(d12 + r2 - r1) < eps) {
        Point<double> v = c2 - c1;
        Point<double> r = c1 + v * r1 / norm(v);

        vect.push_back(r);
    }

    if (r1 + r2 < d12) {
        Point<double> v = c2 - c1;
        double b = r1;
        double c = d12 * r1 / (r1 + r2);
        double a = sqrtl(c*c - b*b);

        Point<double> cx = v * r1 / (r1 + r2);

        Point<double> v1 = rotate(v, -a, b, c);

        Point<double> u1 = v1 * r1 / norm(v1);
        Point<double> w1 = u1 + (cx - u1) * (r1 + r2) / r1;

        u1 = u1 + c1;
        w1 = w1 + c1;

        if (fabs(dist(cc, u1) - rc) < eps) vect.push_back(u1);
        if (fabs(dist(cc, w1) - rc) < eps) vect.push_back(w1);

        Point<double> v2 = rotate(v, a, b, c);

        Point<double> u2 = v2 * r1 / norm(v2);
        Point<double> w2 = u2 + (cx - u2) * (r1 + r2) / r1;

        u2 = u2 + c1;
        w2 = w2 + c1;

        if (fabs(dist(cc, u2) - rc) < eps) vect.push_back(u2);
        if (fabs(dist(cc, w2) - rc) < eps) vect.push_back(w2);
    } else if (fabs(d12 - r1 - r2) < eps) {
        Point<double> v = c2 - c1;
        Point<double> r = c1 + v * r1 / norm(v);

        vect.push_back(r);
    }

    sort(vect.begin(), vect.end());
    return vect;
}

double area_inter_CC(Point<double> c1, double r1, Point<double> c2, double r2) {
    double d = dist(c1, c2);
    if (d >= r1 + r2) return 0;
    if (r1 < r2) {
        swap(r1, r2);
        swap(c1, c2); //bah
    }
    if (d + r2 <= r1) {
        return acos(-1) * r2 * r2;
    }
    auto in = intersect_CC(c1, r1, c2, r2);
    auto x = in.first;
    auto y = in.second;

    if (ccw(x - c1, y - c1) < 0) swap(x, y);
    double ans = 0;
    auto a1 = atan2l(ccw(x-c1, y-c1), dot(x-c1, y-c1));
    ans += (a1*r1*r1 - ccw(x-c1, y-c1)) / 2;

    if (ccw(x - c2, y - c2) < 0) {
        auto a2 = atan2l(ccw(y-c2, x-c2), dot(y-c2, x-c2));
        ans += (a2*r2*r2 - ccw(y-c2, x-c2))/2;
    } else {
        ans += acos(-1)*r2*r2;
        auto a2 = atan2l(ccw(x-c2, y-c2), dot(x-c2, y-c2));
        ans -= (a2*r2*r2 - ccw(x-c2, y-c2))/2;
    }
    return ans;
}