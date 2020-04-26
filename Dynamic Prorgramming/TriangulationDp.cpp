//https://codeforces.com/contest/437/problem/E

#include<bits/stdc++.h>

using namespace std;

#define fRead(x)        freopen(x,"r",stdin)
#define fWrite(x)       freopen (x,"w",stdout)

#define LL              long long
#define ULL             unsigned long long
#define ff              first
#define ss              second
#define pb              push_back
#define PI              acos(-1.0)
#define mk              make_pair
#define pii             pair<int,int>
#define pll             pair<LL,LL>


#define min3(a,b,c)     min(a,min(b,c))
#define max3(a,b,c)     max(a,max(b,c))
#define min4(a,b,c,d)   min(a,min(b,min(c,d)))
#define max4(a,b,c,d)   max(a,max(b,max(c,d)))
#define SQR(a)          ((a)*(a))
#define FOR(i,a,b)      for(int i=a;i<=b;i++)
#define ROF(i,a,b)      for(int i=a;i>=b;i--)
#define REP(i,b)        for(int i=0;i<b;i++)
#define MEM(a,x)        memset(a,x,sizeof(a))
#define ABS(x)          ((x)<0?-(x):(x))

#define SORT(v)         sort(v.begin(),v.end())
#define REV(v)          reverse(v.begin(),v.end())
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FastRead        ios_base::sync_with_stdio(0);cin.tie(nullptr);
#ifdef VAMP
     #define debug(...) __f(#__VA_ARGS__, __VA_ARGS__)
    template < typename Arg1 >
    void __f(const char* name, Arg1&& arg1){
        cout << name << " = " << arg1 << std::endl;
    }
    template < typename Arg1, typename... Args>
    void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names+1, ',');
        cout.write(names, comma - names) << " = " << arg1 <<" | ";
        __f(comma+1, args...);
    }
#else
    #define debug(...)
#endif

/// Geo defines + constants
#define ll long long
#define eps 1e-9
#define sgn(x) (x==0?0:(x<0)?-1:1)
/// ----- Point/Vector Start ----- ///

typedef double VT;

struct Point{
    VT x, y;
    Point(VT _x=0, VT _y=0) : x(_x), y(_y){};
    Point(Point A, Point B){
        x=B.x-A.x;
        y=B.y-A.y;
    }
    Point operator + (Point a) { return {x+a.x, y+a.y};}
    Point operator - (Point a) { return {x-a.x, y-a.y};}
    Point operator * (VT d) { return {x*d, y*d};}
    Point operator / (VT d) { return {x/d, y/d};}
    bool operator == (Point a) { return (fabs(x-a.x)<eps && fabs(y-a.y)<eps);}
    bool operator != (Point a) { return !(*this == a);}
    bool operator < (const Point &a)const{ return (fabs(x-a.x)>eps) ? (x<a.x) : (y<a.y); }
};
typedef Point vec;

ostream& operator<<(ostream& os, Point P){return os << "(" << P.x << ", " << P.y <<")";}
VT dot(Point v, Point w) { return v.x*w.x + v.y*w.y;} // also, vA.vB = |vA|.|vB|.cos(Theta); returns <0 if obtuse angle
VT cross(Point v, Point w) { return v.x*w.y - v.y*w.x;} // also vA x vB = |vA|.|vB|.sin(Theta);
VT sq(Point p){ return p.x * p.x + p.y * p.y;} // square magnitude of a vector
double abs(Point p) {return sqrt(sq(p));}
VT det(Point p, Point q){return p.x * q.y - p.y * q.x;}
Point getUnitVec(Point p){return p/abs(p);}
Point translate(Point v, Point p) { return v+p;}
Point scale(Point v, double factor, Point C=Point(0, 0)){ return C + (v-C)*factor;}
Point perp(Point p) { return {-p.y, p.x};} // good for integers
VT isPerp(Point v, Point w) { return dot(v, w)<eps;}
VT orient(Point A, Point B, Point C) { return cross(B-A, C-A);} // positive on ccw, negative on cw
int orientation(Point A, Point B, Point C){
    VT val=orient(A, B, C);
    if(abs(val)<eps) return 0; // colinear
    return (val<0)?-1:1; // cw / ccw
}

double distToLine(Point a, Point b, Point p, Point &c){
    /// returns the distance from p to the line defined by
    /// two points a and b (a and b must be different)
    /// the closest point is stored in the 4th parameter (by ref)
    vec ap=p-a, ab=b-a;
    double u=dot(ap, ab)/sq(ab);
    /// formula: c=a+u*ab
    c=translate(a, scale(ab, u)); /// translate a to c
    return abs(c-p); /// euclidean distance between c and p
}


double distToLineSegment(Point a, Point b, Point p, Point &c){
    /// returns the distance from p to the line segment ab defined by
    /// two points a and b (a and b must be different)
    /// the closest point is stored in the 4th parameter (by ref)
    vec ap=p-a, ab=b-a;
    double u=dot(ap, ab)/sq(ab);
    if(u<0.0) {c=a; return abs(a-p);} /// closer to a
    else if(u>1.0) {c=b; return abs(b-p);} /// closer to b
    c=translate(a, scale(ab, u)); /// translate a to c
    return abs(c-p); /// euclidean distance between c and p
}

Point rotate(Point p, double rad, Point C=Point(0, 0)){ // rotates p rad degree CCW w.r.t. C
    p=p-C;
    return C+Point(p.x*cos(rad)-p.y*sin(rad), p.x*sin(rad)+p.y*cos(rad));
}
double angle(Point v, Point w){ // angle between two vectors in range [0 - PI]
    double cosTheta=dot(v, w)/abs(v)/abs(w); // vA.vB = |vA|.|vB|.cos(Theta);
    return acos(max(-1.0, min(1.0, cosTheta)));
}
double signedAngle(Point A, Point B, Point P){ /// angle between two vectors(AP w.r.t AB) in range [-PI to PI]
    double ampli=angle(B-A, P-A);
    if(orient(A, B, P)>=0) return ampli;
    return -ampli;
}
int windingNumber(vector<Point> p, Point a){
    double ampli=0;
    for(int i=0, n=p.size(); i<n; i++)
        ampli+=signedAngle(a, p[i], p[(i+1)%n]);
    return round(ampli/(2.0*PI));
}
double polarAngle(Point v){return atan2(v.y, v.x);}
double orientedAngle(Point A, Point B, Point C){ // Angle between vAB and vAC in range [0-360[
    if(orient(A, B, C)>=0) return angle(B-A, C-A);
    else return 2*PI - angle(B-A, C-A);
}
bool inAngle(Point a, Point b, Point c, Point p){
    assert(orient(a, b, c)!=0);
    if(orient(a, b, c)<0) swap(b, c);
    return orient(a, b, p)>=0 && orient(a, c, p)<=0;
}
VT sqrDistance(Point A, Point B){ // Returns the square distance between two points A, B
    return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
}
/// ===== Point/Vector End ===== ///

/// ----- Line start ----- ///

struct line{
    Point v;
    double c; // c is not the slope
    // from direction vector _v and offset _c
    line(Point _v, double _c): v(_v), c(_c){};
    // from equation ax+by=c
    line(VT a, VT b, double c): v({b, -a}), c(c){};
    // From points P and Q
    line(Point p, Point q): v(q-p), c(cross(v, p)){};
    double side(Point P){ // returns |vB|.(|vA|.cos(theta)=height) - c
        return cross(v, P)-c;
    }
    double dist(Point P){ // returns minimum distance between point and line
        return abs(side(P))/abs(v);
    }
    double sqDist(Point P){ // SQR(dist), exact when integer
        return SQR(side(P))/(double)sq(v);
    }
    line perpThrough(Point p){ // returns a perpendicular line that goes through p
        return {p, p+perp(v)};
    }
    bool cmpProj(Point p, Point q){ //sorting points along the line
        return dot(v, p)<dot(v, q);
    }
    line translate(Point t){ // returns a line moving it along t vector
        return {v, c+cross(v, t)};
    }
    line shiftLeft(double dist){ // ekhono clear na amar -_-
        return {v, c+dist*abs(v)};
    }
    Point proj(Point p){ // point p projected(in shortest distance) on v (alt: projOnLine)
        return {p - perp(v)*side(p)/sq(v)};
    }
    Point refl(Point p){ // reflected point based on line
        return {p - perp(v)*2*side(p)/sq(v)};
    }
};

Point projOnLine(Point A, Point B, Point P){ // Minimum dist point from P to Line AB
    Point C;
    Point AP=P-A, AB=B-A;
    double u=dot(AP, AB)/sq(AB);
    return C=A+AB*u;
}

bool lineLineIntersect(line l1, line l2, Point& out){
    VT d=cross(l1.v, l2.v);
    if(d==0) return false;
    out=(l2.v*l1.c - l1.v*l2.c)/d;
    return true;
}

line bisector(line l1, line l2, bool interior){
    assert(cross(l1.v, l2.v)!=0); // l1 and l2 cannot be parallel!
    double sign = interior? 1: -1;
    return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign,
            l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
}

// ALT
bool inDisk2(Point A, Point B, Point C){ // a, b = endpoints of diameter, if p is inside the circle, N.B: doesn't check if inside rectangle
    VT max_x=max(A.x, B.x), min_x=min(A.x, B.x);
    VT max_y=max(A.y, B.y), min_y=min(A.y, B.y);
    return (C.x+eps>=min_x && C.x-eps<=max_x && C.y+eps>=min_y && C.y-eps<=max_y);
}
// ALT
bool pointOnSegment2(Point A, Point B, Point C){ // returns 1 if p is on segment AB
    return (orientation(A, B, C)==0 && inDisk2(A, B, C));
}

bool inDisk(Point a, Point b, Point p){ // a, b = endpoints of diameter, if p is inside the circle, N.B: doesn't check if inside rectangle
    return dot(a-p, b-p)<=0;
}

bool pointOnSegment(Point a, Point b, Point p){ // returns 1 if p is on segment AB
    return abs(orient(a, b, p))<eps && inDisk(a, b, p); // use ==0 if calculating on integer
}

bool properIntersect(Point a, Point b, Point c, Point d, Point &out){ // ignore Point on segment
    VT  oa=orient(c, d, a),
        ob=orient(c, d, b),
        oc=orient(a, b, c),
        od=orient(a, b, d);
    if(oa*ob<0 && oc*od<0){
        out=(a*ob - b*oa) / (ob-oa);
        return true;
    }
    return false;
}
double triangleArea(Point &a, Point &b, Point &c){ // given three points
    return (( a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y) ))/2.0;
    // return abs(cross(b-a, c-a)) / 2.0; /// faster
}
const LL MOD = 1e9 + 7;
int n;
const int N = 205;
LL dp[N][N];
int flag[N][N];

Point ara[N];

double totalArea;
int go(int x,int y)
{
    if(x + 1 == y or (y + 1) % n == x)return 1;
    for(int i = x;i < y;i++){
        if(i == x or i == y)continue;
        if(pointOnSegment(ara[x],ara[y],ara[i]))return 0;
    }

    for(int i = 0;i < n;i++){
        int v1 = i;
        int v2 = (i + 1) % n;
        if(x == v1 or x == v2 or y == v1 or y == v2)continue;
        Point out;
        if(properIntersect(ara[v1],ara[v2],ara[x],ara[y],out) ||
        pointOnSegment(ara[v1],ara[v2],ara[x]) ||
        pointOnSegment(ara[v1],ara[v2],ara[y]) ||
        pointOnSegment(ara[x],ara[y],ara[v1]) ||
        pointOnSegment(ara[x],ara[y],ara[v2]))return 0;
    }
    double a1 = 0,a2 = 0;
    for(int i = x + 1;i < y;i++){
        a1 += triangleArea(ara[x],ara[i],ara[i + 1]);
    }
    for(int i = y + 1;i < x + n;i++){
        a2 += triangleArea(ara[y],ara[i % n],ara[(i + 1) % n]);
    }
    a1 = abs(a1);
    a2 = abs(a2);

    if(a1 < eps or a2 < eps)return 0;
    if(abs((a1 + a2 - totalArea)) < eps)return 1;
    else return 0;

}

LL call(int x,int y)
{
    if(x + 1 == y)return 1;
    if(dp[x][y] != -1)return dp[x][y];
    LL ret = 0;
    for(int i = x + 1;i < y;i++){
        if(flag[x][i] and flag[i][y])ret += (call(x,i) * call(i,y))% MOD;
        ret%= MOD;
    }

    return dp[x][y] = ret % MOD;
}
int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    FastRead
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> ara[i].x >> ara[i].y;
    }
    for(int i = 1;i < n - 1;i++){
        totalArea += triangleArea(ara[0],ara[i],ara[i + 1]);
    }
    totalArea = abs(totalArea);
    for(int i = 0;i < n;i++){
        for(int j = i + 1;j < n;j++){
            flag[i][j] = go(i,j);

        }
    }
    MEM(dp,-1);
    cout << call(0,n-1) << "\n";
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
