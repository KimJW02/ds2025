#include <bits/stdc++.h>

#define _USE_MATH_DEFINES
#define FOR(j) for (int i = 0; i < j; i++)
#define FORI(j, i) for (int i = 0; i < j; i++)
#define FORW(j) for (int i1 = 0, i2 = 1, i3 = 2; i1 < j; i1++, i2 = (i1 + 1) % j, i3 = (i1 + 2) % j)
#define GET(a, t) get<t>(a)
#define IDXM(c, i, n) c[i % n]
#define DEBUG

using namespace std;

typedef tuple<float, float> Point; // x, y
typedef vector<Point> Points;
typedef tuple<Point, float> Circle; // x, y, r
typedef tuple<Circle, Circle, vector<Point>, float> TangentProfile; // ..., four tangent points, angle(arc)

float distance_between(Point &A, Point &B) {
    float dx = get<0>(A) - get<0>(B);
    float dy = get<1>(A) - get<1>(B);
    return sqrt(dx * dx + dy * dy);
}

float area(vector<Point> &P) {
    int n = P.size();
    float sum1 = 0, sum2 = 0;
    FOR(n) {
        Point p1 = P[i], p2 = P[(i + 1) % n];
        sum1 += get<0>(p1) * get<1>(p2);
        sum2 += get<0>(p2) * get<1>(p1);
    }
    return abs(sum1 - sum2) / 2.0;
}

auto tangent_profile(Circle &A, Circle &B) {
    auto [p1, r1] = A; auto [x1, y1] = p1;
    auto [p2, r2] = B; auto [x2, y2] = p2;
    float distance = distance_between(p1, p2), angle_main = atan2(y1 - y2, x1 - x2), angle_delta = acos((r2 - r1) / distance);
    vector<Point> P;
    FORI(2, j) FORI(2, i) { // four tangent points
        bool k = i == j;
        float x = k ? x1 : x2, y = k ? y1 : y2, r = k ? r1 : r2, a = angle_main + (j ? angle_delta : -angle_delta);
        P.emplace_back(make_tuple(x + r * cos(a), y + r * sin(a)));
    }

#ifdef DEBUG
    cout << "distance: " << distance << endl;
    cout << "angle main: " << angle_main << endl;
    cout << "angle delta: " << angle_delta << endl;
    FOR(4) {
        auto [xd, yd] = P[i];
        cout << xd << ' ' << yd << endl;
    }
#endif // DEBUG

    return make_tuple(A, B, P, 2 * angle_delta); // FIXME to angle(arc)
}

int count_tangent_cross(TangentProfile &TP, Circle &C) {
    Points P = get<2>(TP);
    auto [center, radius] = C;
    int cross = 0;

    FOR(2) {
        Points S = { P[2 * i], P[2 * i + 1], center };
        cross += area(S) < radius * distance_between(S[0], S[1]) / 2.0;
    }

    return cross;
}

auto parse() {
    vector<Circle> C;
    vector<TangentProfile> TP;
    float x, y, r;

    FOR(3) {
        cin >> x >> y >> r;
        C.emplace_back(make_tuple(make_tuple(x, y), r));
    }

    FORW(3) {
        TangentProfile T = tangent_profile(C[i1], C[i2]);
        cout << "count: " << count_tangent_cross(T, C[i3]) << endl;
        TP.emplace_back(T);
    }

    return TP;
}

int main() {
    vector<TangentProfile> TP = parse();

    return 0;
}
