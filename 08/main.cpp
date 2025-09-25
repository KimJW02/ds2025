#include <bits/stdc++.h>

using namespace std;

typedef vector<int> Order;
typedef vector<int> Scores;
typedef pair<string, Scores> Student;

int pr_attendance(Scores &S) {
    return -count(S.begin(), S.end(), 0);
}

int pr_total(Scores &S) {
    return accumulate(S.begin(), S.end(), 0);
}

int pr_minimum(Scores &S) {
    return *min_element(S.begin(), S.end(), [](int a, int b) {
        return a == 0 ? false : b == 0 ? true : a < b;
    });
}

int pr_maximum(Scores &S) {
    return *max_element(S.begin(), S.end());
}

int pr_hundreds(Scores &S) {
    return count(S.begin(), S.end(), 100);
}

constexpr array prioritizer = { pr_attendance, pr_attendance, pr_total, pr_minimum, pr_maximum, pr_hundreds };

auto comparator(Order &O) {
    return [O](Student &A, Student &B) {
        for (auto o: O) {
            int diff = prioritizer[o](A.second) - prioritizer[o](B.second);
            if (diff != 0) return diff > 0;
        }
        return A.first > B.first;
    };
}

void parse(vector<Student> &ST, Order &O) {
    int number_students, number_scores;
    cin >> number_students >> number_scores;

    for (int &o : O) cin >> o;

    for (int i = 0; i < number_students; i++) {
        string name;
        cin >> name;

        Scores SC(number_scores);
        for (int &s : SC) cin >> s;

        ST.emplace_back(name, SC);
    }
}

int main() {
    vector<Student> ST;
    Order O(5);

    parse(ST, O);

    sort(ST.begin(), ST.end(), comparator(O));

    for (auto student: ST) cout << student.first << endl;

    return 0;
}
