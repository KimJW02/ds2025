#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Customer;
typedef pair<int, queue<Customer>> Counter;


struct Mall {
    vector<Counter> counters;

    Mall(int k) : counters(k) {};

    void push(int id, int cart) {
        // select counter by total cart
        auto counter = min_element(counters.begin(), counters.end(), [](auto &a, auto &b) { return a.first < b.first; });
        counter->first += cart;
        counter->second.push(make_pair(id, cart));
    }

    static int c_priority(Counter &a) {
        return a.second.empty() ? INT_MAX : a.second.front().second;
    }

    void pop() {
        // select counter by front's cart, with reverse
        auto counter = min_element(counters.rbegin(), counters.rend(), [](auto &a, auto &b) { return c_priority(a)< c_priority(b); });
        auto [id, cart] = counter->second.front();
        cout << id << endl;
        // proceed time
        for (auto &c: counters) c.second.front().second -= cart;
        counter->first -= cart;
        counter->second.pop();
    }
};

int main() {
    int num, k, id, cart;
    cin >> num >> k;

    Mall mall(k);

    int i = num;
    while (i--) {
        cin >> id >> cart;
        mall.push(id, cart);
    }

    while (num--) {
        mall.pop();
    }

    return 0;
}
