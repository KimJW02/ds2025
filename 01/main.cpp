#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef tuple<string, int> Bid;

bool by_cost(const Bid& a, const Bid& b) {
    return(get<1>(a) > get<1>(b) ) ;
}

int main () {
    vector<Bid> B;
    string name;
    int num, cost;

    cin >> num;

    for (int i = 0; i < num; i++) {
        cin >> name >> cost;
        B.emplace_back(make_tuple(name, cost));
    }
    B.emplace_back(make_tuple("UPPER_BOUND", 10001));
    B.emplace_back(make_tuple("LOWER_BOUND", 0));

    sort(B.begin(), B.end(), by_cost) ;

    for (int i = 1; i < num - 1; i++) {
        if (by_cost(B[i-1], B[i]) && by_cost(B[i], B[i+1])) {
            cout << get<0>(B[i]);
            return 0;
        }
    }

    cout << "NONE";

    return 0;
}
