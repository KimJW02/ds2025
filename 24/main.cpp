#include <bits/stdc++.h>

using namespace std;

map<set<int>, set<int, greater<>>> DB;

int input() {
    char cmd;
    int num = 1;
    set<int> key;
    cin >> cmd;
    switch (cmd) {
        case 'R': {
            while (1) {
                cin >> num;
                if (num <= 0) break;
                key.insert(num);
            }
            DB[key].insert(num);
            break;
        }
        case 'Q': {
            while (1) {
                cin >> num;
                if (num == 0) break;
                key.insert(num);
            }
            if (DB[key].size() == 0) cout << "None";
            else for (auto c: DB[key]) cout << c << ' ';
            cout << endl;
            break;
        }
        case '$': {
            return 0;
        }
    }
    return 1;
}

int main() {
    while (input());
    return 0;
}
