#include <iostream>
#include <cmath>

using namespace std;


int main() {
    int tmp,
    x1, y1, r1,
    x2, y2, r2;

    double d, w, a, p, t, s,
    d1, w1, a1, c1,
    d2, w2, a2, c2,
    PI = 3.14159265358979;

    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); // distance

    if (r1 == r2) { // same radius

        a1 = 2 * PI * r1; // two arcs

        p = floor(a1 + d + d); // perimeter

        c1 = PI * pow(r1, 2); // circle

        t = 2 * r1 * d; // square

        s = floor(c1 + t); // space

    } else { // different radius

        if (r2 > r1) { // ensure r1 > r2
            tmp = x1; x1 = x2; x2 = tmp;
            tmp = y1; y1 = y2; y2 = tmp;
            tmp = r1; r1 = r2; r2 = tmp;
        }

        d2 = d * r2 / (r1 - r2);
        d1 = d2 + d;

        w1 = sqrt(pow(d1, 2) - pow(r1, 2));
        w2 = sqrt(pow(d2, 2) - pow(r2, 2));
        w = w1 - w2; // straight line

        a = acos(r1 / d1); // angle
        a1 = r1 * 2 * (PI - a); // big arc
        a2 = r2 * 2 * a; // small arc

        p =  floor(a1 + a2 + w + w); // perimeter

        t = (r1 + r2) * w; // triangle x 2

        c1 = r1 * a1 / 2; // big sector
        c2  = r2 * a2 / 2; // small sector

        s = floor(t + c1 + c2); // space

    }

    cout << s << ' ' << p << endl;

    return 0;
}
