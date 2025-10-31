#include <bits/stdc++.h>

using namespace std;

char c; int cplx, depth;

main() {
    while (cin >> c) c - '{' ? c - '}' ? 0 : cplx += depth-- : depth++;
    cout << cplx;
}
