#include <bits/stdc++.h>

using namespace std;

typedef stack<int> Storage;

struct Yard {
    vector<Storage> SV;

    void init() {
        int num, st, cont;
        cin >> num;
        while (num--) {
            Storage S;
            cin >> st;
            while (st--) {
                cin >> cont;
                S.push(cont);
            }
            SV.emplace_back(S);
        }
    }

    bool step() {
        Storage &s_largest = *max_element(SV.begin(), SV.end(), [](Storage &A, Storage &B) {
            int diff = A.size() - B.size();
            // if same size, check empty and use top container
            if (diff == 0 && !A.empty()) diff = A.top() - B.top();
            return diff < 0;
        });
        Storage &s_smallest = *min_element(SV.begin(), SV.end(), [](Storage &A, Storage &B) { return A.size() < B.size(); });
        // check ending
        if (s_largest.size() - s_smallest.size() <= 1) return false;
        // move container
        s_smallest.push(s_largest.top());
        s_largest.pop();
        return true;
    }

    void show_storage(Storage &S) {
        if (S.empty()) return;
        int cont = S.top();
        S.pop();
        // recursive print
        show_storage(S);
        printf("%d ", cont);
    }

    void show() {
        for (auto &S: SV) {
            if (S.empty()) cout << 0;
            else show_storage(S);
            cout << endl;
        }
    }
};

int main() {
    Yard Y;
    Y.init();
    while (Y.step());
    Y.show();
    return 0;
}
