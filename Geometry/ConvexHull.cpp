#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
typedef long double Real;
const int MOD = 2004010501;

struct TVector {
    Int x,y;
    TVector() {}
    TVector(Int x, Int y) : x(x), y(y) {}
    TVector operator+ (const TVector& other) const {
    	return TVector(x + other.x, y + other.y);
    }
    TVector operator- (const TVector& other) const {
    	return TVector(x - other.x, y - other.y);
    }
    Int operator% (const TVector& other) const { //dot product
    	return x * other.x + y * other.y;
	}
	Int operator* (const TVector& other) const { //cross product
	    return x * other.y - y * other.x;
	}
};
typedef TVector TPoint;
Int sqr_length(const TVector& u) { return u.x * u.x + u.y * u.y; }
Real length(const TVector& u) { return sqrt(sqr_length(u)); }
//Int sqr_length(const TPoint& A, const TPoint& B) { return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y); }
//Real length(const TPoint& A, const TPoint& B) { return sqrt(sqr_length(A,B)); }

const int N = 1e6 + 100;
int num_points;
TPoint points[N];

TPoint origin;
bool is_lower(const TPoint& a, const TPoint& b) { return (a.y == b.y) ? a.x < b.x : a.y < b.y;}
bool by_angle(const TPoint& a, const TPoint& b) { 
	Int area = (a-origin) * (b-origin); 
	if (area == 0) return sqr_length(a-origin) < sqr_length(b-origin);
	return area > 0;
}
void graham_scan() {
	swap(points[0], *min_element(points, points + num_points, is_lower));
	origin = points[0];
	sort(points + 1, points + num_points, by_angle);
}
int num_vertex = 0; TPoint hull[N];
bool is_turn_left(const TPoint& a, const TPoint& b, const TPoint& c) { return (b-a) * (c-a) > 0; }
void find_convexhull() {
	graham_scan();
	hull[num_vertex++] = points[0];
	for (int i = 1; i < num_points; i++) {
		while (num_vertex >= 2 and !is_turn_left(hull[num_vertex-2], hull[num_vertex-1], points[i])) --num_vertex;
		hull[num_vertex++] = points[i];
	}
}

Int area(TPoint* p, int num_elems) {
//	cerr << "calculating : ";
//	for (int i = 0; i < num_elems; i++) cerr << '(' << p[i].x << ',' << p[i].y << ") "; cerr << '\n';
	Int res = 0;
	for (int i = 0; i+1 < num_elems; i++)
		res += (p[i].y + p[i+1].y) * (p[i+1].x - p[i].x);
//	cerr << "result = " << res << '\n';
	return res;
}

int main()
{
	#define task "watermov"
	if (fopen(task".inp", "r")) {
	    freopen(task".inp", "r", stdin);
	    freopen(task".out", "w", stdout);
    }
    scanf("%d", &num_points);
	Int sy = 0;
	points[0] = TPoint(0, 0);
    for (int i = 1, ai; i <= num_points; i++)
    	scanf("%d", &ai), points[i] = TPoint(i, sy += (Int) ai);
    Int ans = area(points, ++num_points);
    find_convexhull();
//    cerr << num_vertex << " is size of hull\n";
    for (int i = 0; i < num_vertex; i++) 
    	if (hull[i].x == num_points-1)
    		ans -= area(hull, num_vertex = i+1);
    printf("%lld", ans / 2);
    if (ans % 2) puts(".5"); else puts(".0");
}
