#include <iostream>
#include <vector>
#include<tuple>
#include<algorithm>

using namespace std;

typedef tuple<int, int, int> PT; // point with time

int diff(int a, int b) {
    return a > b ? a - b : b - a;
}

int prepare(vector<PT> &V) {
    int num, x, y, sum = 0, time = 0;

    cin >> num;

    for (int i = 0; i < num; i++) {
        cin >> x >> y;
        time += i == 0 ? 0 : diff(sum, (x + y));
        sum = x + y;
        V.emplace_back(make_tuple(x, y, time));
    }

    time += diff(sum, get<0>(V[0]) + get<1>(V[0]));

    return time;
}

bool by_time(const PT &a, int b) {
    return (get<2>(a) < b);
}

PT find_point(vector<PT> &V, int query) {
    int index = lower_bound(V.begin(), V.end(), query, by_time) - V.begin(); // end index
    index -= index > 0 ? 1 : 0;

    int len = V.size();
    PT from = V[index % len], to = V[(index+1) % len];

    auto [x1, y1, t1] = from;
    auto [x2, y2, t2] = to;
    int x = x1, y = y1, delta = query - t1;

    if (y1 == y2) { // line-x
        x += (x1 < x2 ? delta : -delta);
    } else { // line-y
        y += (y1 < y2 ? delta : -delta);
    }

    return make_tuple(x, y, query);
}

int main() {
    PT pt;
    vector<PT> V;
    int num = 5, query, total = prepare(V);

    while (num--) {
        cin >> query;
        pt = find_point(V, query % total);
        cout << get<0>(pt) <<  ' ' << get<1>(pt) << endl;
    }

    return 0;
}
