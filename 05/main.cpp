#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> Chair;
typedef  vector<Chair> Room;

bool by_front(const Chair &C, int person) {
    return C.front() < person;
}

int index_chair(Room &R, int person) {
    return lower_bound(R.begin(), R.end(), person, by_front) - R.begin();
}

auto iter_person(Chair &C, int person) {
    return lower_bound(C.begin(), C.end(), person);
}

void push(Room &R, int person, int k) {
    if (R.size() == 0) { // empty room
        Chair C(1, person); // new chair
        R.emplace_back(C);
        return;
    }

    int i = index_chair(R, person) - 1;
    i += (i < 0); // first chair

    R[i].insert(iter_person(R[i], person), person);

    if (R[i].size() == k * 2) { // split
        auto b = R[i].begin(), e = R[i].end();
        Chair C(b + k, e); // new chair
        R[i].erase(b + k, e);
        R.insert(R.begin() + i + 1, C);
    }
}

void pop(Room &R, int person, int k) {
    if (R.size() == 0) return; // empty room

    int i = index_chair(R, person + 1); // except equality
    i -= (i > 0); // first chair

    auto iter = iter_person(R[i], person);
    if (iter != R[i].end() && *iter == person) {
        R[i].erase(iter);
        if (R[i].size() == 0) R.erase(i + R.begin()); // compaction
    }
}

int main() {
    Room R;
    int n, k, p;
    char op;

    cin >> n >> k;
    while (n--) {
        cin >> op >> p;
        (op == '+' ? push : pop)(R, p, k);
    }

    for (auto C: R) {
        cout << C.front() << endl;
    }

    return 0;
}
