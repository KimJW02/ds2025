#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/mman.h>

using namespace std;

struct Node {
    // coverage
    int from;
    int to;

    // price
    int p_min;
    int p_max;

    // children
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int _from, int _to) : from(_from), to(_to) {}

    template <typename F>
    void init(F func) {
        // leaf node
        if (from == to) {
            func(this);
            return;
        }

        int mid = (from + to) / 2;

        left = new Node(from, mid);
        right = new Node(mid + 1, to);
        left->init(func);
        right->init(func);

        // re-calculate coverage
        from = left->from;
        to = right->to;
        p_min = min(left->p_min, right->p_min);
        p_max = max(left->p_max, right->p_max);
    }

    pair<int, int> query(int q_from, int q_to) {
        // not-matched
        if (q_to < from || to < q_from) return make_pair(INT_MAX, -1.0);

        // fully-matched or leaf node
        if ((q_from <= from && to <= q_to) || left == nullptr || right == nullptr) return make_pair(p_min, p_max);

        // partial-matched, so query children recursively
        auto [left_min, left_max] = left->query(q_from, q_to);
        auto [right_min, right_max] = right->query(q_from, q_to);
        return make_pair(min(left_min, right_min), max(left_max, right_max));
    }
};

Node* build() {
    int num, time, price, price_i, price_f;

    int fd = open ("Pitcoin.txt", O_RDONLY);
    struct stat s;
    fstat(fd, & s);
    int file_size = s.st_size;
    const char* cp = (char *) mmap (0, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    const char* cp_end = cp + file_size;

    // skip whitespaces
    auto cp_skip = [&]() {
        while (cp < cp_end && isspace(*cp)) ++cp;
    };

    // parse
    auto cp_read = [&]() {
        cp_skip();
        cp = from_chars(cp, cp_end, time).ptr;
        cp_skip();
        // float to int
        cp = from_chars(cp, cp_end, price_i).ptr;
        cp = from_chars(cp + 1, cp_end, price_f).ptr;
        price = price_i * 1000 + price_f;
    };

    cp_skip();
    cp = from_chars(cp, cp_end, num).ptr;
    cp_read();
    time = 1;

    // segment tree
    Node* root = new Node(0, num - 1);
    root->init([&](Node* node) {
        node->p_min = node->p_max = price;
        node->from = time;
        if (--num) cp_read();
        else time = INT_MAX;
        node->to = time - 1;
    });

    return root;
}

int main() {
    int num, from, to;
    Node* root = build();

    scanf("%d", &num);
    while (num--) {
        scanf("%d %d", &from, &to);
        auto [q_min, q_max] = root->query(from, to);
        printf("%d.%03d %d.%03d\n", q_min / 1000, q_min % 1000, q_max / 1000, q_max % 1000);
    }

    return 0;
}
