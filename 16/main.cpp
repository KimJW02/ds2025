#include <bits/stdc++.h>

using namespace std;

int evaluate() {
    char c;
    int cpx = 0, depth = 0;
    while (cin.get(c)) {
        switch (c) {
            case '{':
                depth++;
                break;
            case '}':
                cpx += depth--;
                break;
        }
    }
    return cpx;
}

int main() {
    cout << evaluate();
    return 0;
}
