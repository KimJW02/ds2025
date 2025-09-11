#include <bits/stdc++.h>

#define _USE_MATH_DEFINES
#define FOR(j) for (int i = 0; i < j; i++)
#define FORI(j, i) for (int i = 0; i < j; i++)
#define FORL(i, b, e) for (int i = b; i < e; i++)
#define FORW(j) for (int i1 = 0, i2 = 1, i3 = 2; i1 < j; i1++, i2 = (i1 + 1) % j, i3 = (i1 + 2) % j)

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
        cout << distance << ' ' << angle_main << ' ' << angle_delta << endl;
        FORI(2, i) FORI(2, j) { // four tangent points
            Circle *T = i ? this : &C;
            float a = angle_main + (j ? angle_delta : -angle_delta);
            CPoint CP = { T->x + T->r * cos(a), T->y + T->r * sin(a), T };
            P.emplace_back(CP);
        }
    }
};

float ccw(Point &A, Point &B, Point &C) {
    return A.x*B.y+B.x*C.y+C.x*A.y-B.x*A.y-C.x*B.y-A.x*C.y;
}

int main() {
    Circle C[3];
    vector<CPoint> CP;

    FOR(3) scanf("%f %f %f", &C[i].x, &C[i].y, &C[i].r);
    FORW(3) C[i1].tangent_points(C[i2], CP);

    // convex hull
    // https://david0506.tistory.com/62
    // https://klloo.github.io/convex-hull/
    sort(CP.begin(), CP.end());
    sort(CP.begin() + 1, CP.end(), [CP](Point &A, Point &B) {
        CPoint FP = CP[0];
        float direction = ccw(FP, A, B);
        return direction == 0 ? FP.distance(A) < FP.distance(B) : direction > 0;
    });
    stack<CPoint> ST({ CP[0], CP[1] });
    CPoint A, B, D;
    for (int i = 2; i < CP.size(); i++) {
        while (ST.size() >= 2) {
            B = ST.top();
            ST.pop();
            A = ST.top();
            if (ccw(CP[i], A, B) > 0) {
                ST.push(B);
                break;
            }
        }
        ST.push(CP[i]);
    }

    cout << endl;

    D = ST.top();
    while (!ST.empty()) {
        A = ST.top();
        if (A.C == B.C) {
            Circle C = *A.C;
            float sector = 0.5 * C.r * C.r * abs(C.angle(B) - C.angle(A));
            cout << C.angle(A) << ' ' << C.angle(B) << endl;
        }
        cout << A.x << ' ' << A.y << ' ' << (A.C == B.C) << endl;
        ST.pop();
        B = A;
    }

    return 0;
}
