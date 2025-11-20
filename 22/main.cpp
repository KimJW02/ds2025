#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> Wall;
int Grid[25][25][4] = { 0, };
int n, t;

void init() {
    int w;
    cin >> n >> t;
    for (int i = 0; i < n; i++) {
        vector<int> W;
        for (int j = 0; j < n; j++) {
            cin >> w;
            W.push_back(w);
        }
        Wall.push_back(W);
    }
}

int isWall(int x, int y) {
    return x < 0 || n <= x || y < 0 || n <= y || Wall[y][x];
}

int solve() {
    // start 4-direction BFS
    queue<tuple<int, int, int, int, int>> Q;
    // add initial
    Q.emplace(0, n - 1, 0, -1, 0);
    while (!Q.empty()) {
        // pop
        auto [x, y, time, direction, isDirectionChanged] = Q.front();
        Q.pop();
        // check wall
        if (isWall(x, y)) continue;
        time += 1 + (isDirectionChanged ? t : 0);
        // check non-initial
        if (direction >= 0) {
            // compare with previous results, with direction
            int g = Grid[y][x][direction];
            // check less-value already exists
            if (g && g <= time) continue;
            // update value
            Grid[y][x][direction] = time;
        }
        // add 4-direction
        Q.emplace(x, y + 1, time, 0, direction != 0);
        Q.emplace(x + 1, y, time, 1, direction != 1);
        Q.emplace(x, y - 1, time, 2, direction != 2);
        Q.emplace(x - 1, y, time, 3, direction != 3);
    }
    // get non-zero min value
    int res = INT_MAX;
    for (int i = 0; i < 4; i++) {
        int g = Grid[0][n - 1][i];
        if (g) res = min(res, g);
    }
    if (res == INT_MAX) return -1;
    return res - t - 1;
}

int main() {
    init();
    cout << solve() << endl;
    return 0;
}
