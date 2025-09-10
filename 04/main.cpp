#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

typedef tuple<int, int, int, int> PTT; // point with direction-related time (clockwise, counter-clockwise)

int scan(vector<PTT> &V, int start, bool clockwise) {
    int sum = 0, time = 0, i = start, len = V.size();

    do {
        auto [x, y, t1, t2] = V[i];
        x += y; // sum
        time += sum == 0 ? 0 : abs(sum - x); // time-delta
        sum = x;

        if (clockwise)
            get<2>(V[i]) = time;
        else
            get<3>(V[i]) = time;

        i = (len + i + (clockwise ? 1 : -1)) % len; // circular loop
    } while (i != start);

    return time + abs(sum - get<0>(V[i]) - get<1>(V[i]));  // total time
}

int prepare(vector<PTT> &V) { // parse input
    int num, x, y;

    cin >> num;

    for (int i = 0; i < num; i++) {
        cin >> x >> y;
        V.emplace_back(make_tuple(x, y, 0, 0));
    }

    return num;
}

auto by_time(bool clockwise) {
    return [clockwise](const PTT &a, int b) {
        return ((clockwise ? get<2>(a) : get<3>(a)) < b);
    };
}

auto find_point(vector<PTT> &V, int query, bool clockwise) {
    int index = lower_bound(V.begin(), V.end(), query, by_time(clockwise)) - V.begin(); // end index
    index -= index > 0 ? 1 : 0; // start index

    int len = V.size();
    auto [x1, y1, t11, t12] = V[index % len]; // start
    auto [x2, y2, t21, t22] =  V[(index+1) % len]; // end
    int t1 = clockwise ? t11 : t12;
    int x = x1, y = y1, delta = query - t1;

    if (y1 == y2) { // line-x
        x += (x1 < x2 ? delta : -delta);
    } else { // line-y
        y += (y1 < y2 ? delta : -delta);
    }

    return make_tuple(x, y);
}

int main() {
    vector<PTT> V;
    int num = prepare(V) / 2 - 1; // second robocop
    int time = scan(V, 0, true);
    scan(V, num, false);
    PTT f = V.front(), b = V.back();

    int query;
    cin >> query;
    query %= time;

    auto [x1, y1] = find_point(V, query, true);
    rotate(V.begin(), V.begin() + num + 1, V.end());
    reverse(V.begin(), V.end());
    auto [x2, y2] = find_point(V, query, false);

    query  *= 2;

    if ((get<2>(f) + get<3>(f)) <= query && query < (get<2>(b) + get<3>(b)))
        cout << x2 << ' ' << y2 << endl << x1 << ' ' << y1 << endl;
    else
        cout << x1 << ' ' << y1 << endl << x2 << ' ' << y2 << endl;

    return 0;
}
