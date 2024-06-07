#include <bits/stdc++.h>
using namespace std;

template<class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
	bool operator<(R p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z); }
	bool operator==(R p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z); }
	P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const { return P(x*d, y*d, z*d); }
	P operator/(T d) const { return P(x/d, y/d, z/d); }
	T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const {
		return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
	T dist2() const { return x*x + y*y + z*z; }
	double dist() const { return sqrt((double)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	double phi() const { return atan2(y, x); } 
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	double theta() const { return atan2(sqrt(x*x+y*y),z); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
	//returns point rotated 'angle' radians ccw around axis
	P rotate(double angle, P axis) const {
		double s = sin(angle), c = cos(angle); P u = axis.unit();
		return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
	}
};

struct Circle {
    Point3D center, u, v;

    ifstream& operator>>(ifstream& in, Circle& circle) {
        in>>circle.center>>circle.u>>circle.v;
        return in;
    }
};

const double eps = 1e-12;
bool are_parallel(Plane X, Plane Y) {
    auto Z = X.cross(Y);
    if (fabs(Z.x) < eps && fabs(Z.y) && fabs(Z.z)) {
        return true;
    }
    return false;
}


using Plane = Circle;

int main() {
    Circle A, B;
    cin>>A>>B;
    if (are_parallel(A, B)) cout << "NO" << '\n';
    else {
        auto plane_interception = intercept(A, B);
        auto range_1 = intercept(plane_interception, A);
        auto range_2 = intercept(plane_interception, B);
        if (intercept(range_1, range_2)) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }   

    return 0;
}