
const Real EPS = 1e-9;
struct Point {
	Real x,y;
	Point(Real x, Real y) : x(x), y(y) {}
};
Real sqr(Real x) { return x*x; }
Real dist(const Point& a, const Point& b) {
	return sqrt(sqr(a.x-b.x) + sqr(a.y-b.y));
}

struct Line {
	Real a,b,c; //ax + by + c = 0
	Line(Real a, Real b, Real c) : a(a), b(b), c(c) {}
	Line(Point u, Point v) {
		//a*ux + b*uy = a*vx + b*vy
		//a(ux-vx) + b(uy-vy) = 0
		a = u.y-v.y, b = v.x-u.x;
		c = -(a*u.x + b*u.y);
	}
};
Real dist(const Point& p, const Line& d) {
	return (d.a*p.x + d.b*p.y + d.c) / sqrt(sqr(d.a) + sqr(d.b));
}

const Real LIM = 1e9;
Point init(LIM+1, LIM+1);
Point intersect(const Line& u, const Line& v) {
	//a1*x + b1*y + c1 = 0
	//a2*x + b2*y + c2 = 0
	//a1*b2*x + b2*c1 = a2*b1*x + b1*c2
	Real det = u.a*v.b - u.b*v.a;
	if (!det) return init;
	Real x = (u.b*v.c - u.c*v.b) / det, y;
	if (v.b) y = -(v.c + v.a*x) / v.b;
	else y = -(u.c + u.a*x) / u.b;
	return Point(x,y);
}
