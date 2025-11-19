#include <bits/stdc++.h>
#define N 3

using namespace std;

map<char, vector<char>> Graph;

char Friends[N] = { 0 };

void init() {
    int num, i;
    cin >> num;
    for (int i = 0; i < N; i++) cin >> Friends[i];
    while (num--) {
        char vertex, adj = 0;
        cin >> vertex;
        while (1) {
            cin >> adj;
            if (adj == '$') break;
            Graph[vertex].push_back(adj);
        }
    }
}

int calc_distance(char from) {
    unordered_map<char, int> g_distance;
    queue<char> g_queue;

    g_distance[from] = 0;
    g_queue.push(from);

    while (!g_queue.empty()) {
        char head = g_queue.front();
        g_queue.pop();
        for (auto adj: Graph[head]) {
            // check self-routing
            if (!g_distance[adj] && adj != from) {
                g_distance[adj] = g_distance[head] + 1;
                g_queue.push(adj);
            }
        }
    }

    int max_distance = -1;
    for (int i = 0; i < N; i++) {
        char f = Friends[i];
        int f_distance = g_distance[f];
        // check disconnected
        if (!f_distance && f != from) return -1;
        max_distance = max(max_distance, f_distance);
    }

    return max_distance;
}

void process() {
    char place = '@';
    int min_distance = INT_MAX;
    for (auto g: Graph) {
        int result = calc_distance(g.first);
        if (result == -1) continue;
        if (min_distance > result) {
            min_distance = result;
            place = g.first;
        }
    }
    if (place == '@') printf("@\n-1");
    else printf("%c\n%d", place, 3 * min_distance - 2);
}

int main() {
    init();
    process();
    return 0;
}
