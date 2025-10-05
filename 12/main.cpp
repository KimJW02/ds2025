#include <bits/stdc++.h>

using namespace std;

struct Vueue {
    vector<queue<int>> queues;

    Vueue() : queues(5) {};

    void push(int id, int age, char sex) {
        int priority = 0, male = sex == 'M';

        // calculate priority
        if (age <= 15) priority = 2;
        else if (age <= 60) priority = male ? 4 : 3;
        else priority = male ? 0 : 1;

        queues[priority].push(id);
    }

    void print() {
        for (auto &q: queues) {
            while (!q.empty()) {
                cout << q.front() << endl;
                q.pop();
            }
        }
    }
};

int main() {
    Vueue V;
    int num, id, age;
    char sex;

    cin >> num;
    while (num--) {
        cin >> id >> age >> sex;
        V.push(id, age, sex);
    }
    V.print();

    return 0;
}
