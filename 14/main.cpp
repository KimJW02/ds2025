#include <bits/stdc++.h>

using namespace std;

struct Range {
    int64_t from, to;
    bool value;
    Range(int64_t _from, int64_t _to, bool _value) : from(_from), to(_to), value(_value) {};
};

typedef list<Range> Ranges;

void flip(Ranges &R, int64_t from, int64_t to) {
    auto iter = R.begin();
    while (iter != R.end()) {
        auto [_from, _to, _value] = *iter;
        // <-->--[--]
        if (to < _from) return;
        // [--]--<-->
        else if (_to < from) {
            // noop
        }
        // [--<-->--]
        else if (_from < from && to < _to) {
            // left
            iter->to = from - 1;
            // mid
            iter = R.insert(next(iter), Range(from, to, !_value));
            // right
            iter = R.insert(next(iter), Range(to + 1, _to, _value));
        }
        // <--[--]--> ~ <[--]>
        else if (from <= _from && _to <= to) {
            // entire
            iter->value = !_value;
        }
        // [--<--]-->
        else if (_from < from && _to <= to) {
            // left
            iter->to = from - 1;
            // right
            iter = R.insert(next(iter), Range(from, _to, !_value));
        }
        // <--[-->--]
        else if (from <= _from && to < _to) {
            // left
            iter->to = to;
            iter->value = !_value;
            // right
            iter = R.insert(next(iter), Range(to + 1, _to, _value));
        }
        iter++;
    }
}

void compact(Ranges &R) {
    auto iter = R.begin(), niter = next(iter);
    while (niter != R.end()) {
        if (iter->to + 1 == niter->from && iter->value == niter->value) {
            // compaction
            iter->to = niter->to;
            R.erase(niter);
        } else {
            // skip
            iter = niter;
        }
        niter = next(iter);
    }
}

void show(Ranges &R) {
    int64_t run = 0, length = 0;
    for (auto iter = R.begin(); iter != R.end(); iter++) {
        if (iter->value) {
            // closed interval
            length += iter->to - iter->from + 1;
            run++;
        }
    }
    cout << run << ' ' << length << endl;
}

int main() {
    int64_t from = 0, to;
    int n;
    cin >> to >> n;
    Ranges R = { Range(from, to - 1, false) };

    while (n--) {
        cin >> from >> to;
        flip(R, from, to);
    }
    compact(R);
    show(R);

    return 0;
}
