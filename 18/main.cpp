#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<bool>> Canvas;

// quad-tree node
struct Qode {
    int x, y, size;
    bool data;
    vector<Qode> children;

    Qode(int _x, int _y, int _s): x(_x), y(_y), size(_s) {}

    auto add_child(int quad) {
        int csize = size / 2;
        children.emplace_back(quad == 0 || quad == 3 ? x + csize : x, quad < 2 ? y : y + csize, csize);
        return &children.back();
    }

    void encode(Canvas &canvas) {
        // check leaf
        if (size == 1) {
            data = canvas[y][x];
            return;
        }
        for (int quad = 0; quad < 4; quad++) {
            add_child(quad)->encode(canvas);
        }
        if (all_of(children.begin(), children.end(), [&](auto &child) {
        return !child.children.size() && child.data == children[0].data;
        })) {
            data = children[0].data;
            children.clear();
        }
    }

    void serialize() {
        // check leaf
        if (children.size()) {
            cout << '(';
            for (auto &child: children) child.serialize();
            cout << ')';
        } else cout << data;
    }

    void decode(string &input, int &index) {
        // check leaf
        if (input[index] != '(') data = input[index++] == '1';
        // build children
        else {
            // skip '('
            index++;
            // decode recursively
            for (int quad = 0; quad < 4; quad++) add_child(quad)->decode(input, index);
            // skip '('
            index++;
        }
    }

    void embed(Canvas &canvas) {
        for (int i = 0; i < size; i++) for (int j = 0; j < size; j++) canvas[y + j][x + i] = data;
        for (auto &child: children) child.embed(canvas);
    }
};

int main() {
    int size, index = 0;
    cin >> size;
    size = pow(2, size);

    auto canvas = Canvas(size, vector<bool>(size, false));
    Qode Q(0, 0, size);

    char c;
    string data;
    cin >> data;

    switch (data[0]) {
    case 'I':
        // input
        for (int i = 0; i < size; i++) for (int j = 0; j < size; j++) {
                cin >> c;
                canvas[i][j] = c == '1';
            }
        Q.encode(canvas);
        Q.serialize();
        break;
    case 'Q':
        cin >> data;
        Q.decode(data, index);
        Q.embed(canvas);
        // output
        for (auto a: canvas) {
            for (auto b: a) cout << b;
            cout << endl;
        }
    }

    return 0;
}
