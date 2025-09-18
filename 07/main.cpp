#include <bits/stdc++.h>

#define PIF(i, j) printf("%d.%03d %d.%03d\n", i / 1000, i % 1000, j / 1000, j % 1000)

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

// skip whitespace
void skip(const char*& cp, const char* cp_end) {
    while (cp < cp_end && isspace(*cp)) ++cp;
}

Node* build() {
    int num, time, price, price_i, price_f;

    FILE* fp = fopen("Pitcoin.txt", "r");

    fseek(fp, 0, SEEK_END);
    size_t file_size = ftell(fp);
    rewind(fp);

    string buffer(file_size, '\0');
    fread(&buffer[0], 1, file_size, fp);
    fclose(fp);

    // get char pointer
    const char* cp = buffer.data();
    const char* cp_end = cp + buffer.size();

    // parse
    auto cp_read = [&]() {
        skip(cp, cp_end);
        cp = from_chars(cp, cp_end, time).ptr;
        skip(cp, cp_end);
        // float to int
        cp = from_chars(cp, cp_end, price_i).ptr;
        cp = from_chars(cp + 1, cp_end, price_f).ptr;
        price = price_i * 1000 + price_f;
    };

    skip(cp, cp_end);
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
        PIF(q_min, q_max);
    }

    return 0;
}
