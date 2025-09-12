#include <bits/stdc++.h>

#define _USE_MATH_DEFINES
#define FOR(j) for (int i = 0; i < j; i++)
#define FORI(j, i) for (int i = 0; i < j; i++)
#define FORL(i, b, e) for (int i = b; i < e; i++)
#define FORW(j) for (int i1 = 0, i2 = 1, i3 = 2; i1 < j; i1++, i2 = (i1 + 1) % j, i3 = (i1 + 2) % j)
#define CCW(A, B, C) (A.x*B.y+B.x*C.y+C.x*A.y-B.x*A.y-C.x*B.y-A.x*C.y)
#define MODP(a) fmod(2 * M_PI + a, 2 * M_PI)
#define TP(T, a) { T->x + T->r * cos(a), T->y + T->r * sin(a), T }
#define PRP(P) scanf("%f %f %f", &P.x, &P.y, &P.r)

using namespace std;

struct Circle; // forward declaration;

struct Point {
    float x, y;
    bool operator < (Point &P) { // sort
        return y == P.y ? x < P.x : y < P.y;
    }
    float distance(Point &P) { // distance
        float dx = x - P.x, dy = y - P.y;
        return sqrt(dx * dx + dy * dy);
    }
    float angle(Point &P) {
        return atan2(y - P.y, x - P.x);
    }
};

struct CPoint : Point { // circle-referenced point
    Circle *C;
};

struct Circle : Point {
    float r;
    void tangent_points(Circle &C, vector<CPoint> &P) {
        float distance = this->distance(C), angle_main = this->angle(C), angle_delta = acos((C.r - r) / distance);
        //cout << distance << ' ' << angle_main << ' ' << angle_delta << endl;
        FORI(2, i) FORI(2, j) { // four tangent points
            Circle *T = i ? this : &C;
            float a = angle_main + (j ? angle_delta : -angle_delta);
            CPoint CP = TP(T, a);
            P.emplace_back(CP);
        }
    }
};

int main() {
    Circle C[3];
    vector<CPoint> CP;

    FOR(3) PRP(C[i]);
    FORW(3) C[i1].tangent_points(C[i2], CP);

    // convex hull
    // https://david0506.tistory.com/62
    // https://klloo.github.io/convex-hull/
    sort(CP.begin(), CP.end());
    sort(CP.begin() + 1, CP.end(), [CP](Point &A, Point &B) {
        CPoint FP = CP[0];
        float direction = CCW(FP, A, B);
        return direction == 0 ? FP.distance(A) < FP.distance(B) : direction > 0;
    });
    stack<CPoint> ST({ CP[0], CP[1] });
    CPoint A, B;
    for (int i = 2; i < CP.size(); i++) {
        while (ST.size() >= 2) {
            B = ST.top();
            ST.pop();
            A = ST.top();
            if (CCW(CP[i], A, B) > 0) {
                ST.push(B);
                break;
            }
        }
        ST.push(CP[i]);
    }
    ST.push(CP[0]);
    B = ST.top();

    //cout << endl;

    float area, segment; // shoelace formula

    while (!ST.empty()) {
        A = ST.top();
        area += A.x * B.y - B.x * A.y;
        //cout << A.x << ' ' << A.y << endl;
        if (A.C == B.C) {
            Circle C = *A.C;
            float diff = MODP(C.angle(B) - C.angle(A));
           segment += C.r * C.r * (diff - sin(diff));
            //cout << diff << ' ' << sin(diff) << endl;
        }
        ST.pop();
        B = A;
    }
    cout << floor((abs(area) + segment) / 2);

    return 0;
}
