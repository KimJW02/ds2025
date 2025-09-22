#include <bits/stdc++.h>

#define FOR(j) for (int i = 0; i < j; i++)
#define N 5

using namespace std;

typedef vector<int> Scores;
typedef pair<string, Scores> Student;

int count_score(Scores &S, int score) {
    return count(S.begin(), S.end(), score);
}

// filter zero-score
bool with_attendance(int a, int b) {
    return a == 0 ? false : b == 0 ? true : a < b;
}

int pr_attendance(Scores &S) {
    return -count_score(S, 0);
}

int pr_total(Scores &S) {
    return accumulate(S.begin(), S.end(), 0);
}

int pr_minimum(Scores &S) {
    return *min_element(S.begin(), S.end(), with_attendance);
}

int pr_maximum(Scores &S) {
    return *max_element(S.begin(), S.end());
}

int pr_hundreds(Scores &S) {
    return count_score(S, 100);
}

constexpr array prioritizer = { pr_attendance, pr_total, pr_minimum, pr_maximum, pr_hundreds };

auto comparator(int order[N]) {
    return [order](Student &A, Student &B) {
        FOR(N) {
            int diff = prioritizer[order[i]](A.second) - prioritizer[order[i]](B.second);
            if (diff != 0) return diff > 0;
        }
        return A.first > B.first;
    };
}

void parse(vector<Student> &ST, int order[N]) {
    int number_students, number_scores;
    cin >> number_students >> number_scores;

    FOR(5) {
        cin >> order[i];
        order[i]--;
    }

    FOR(number_students) {
        string name;
        cin >> name;

        Scores SC(number_scores);
        for (int &s : SC) cin >> s;

        ST.emplace_back(name, SC);
    }
}

int main() {
    vector<Student> ST;
    int order[N];

    parse(ST, order);

    sort(ST.begin(), ST.end(), comparator(order));

    for (auto student: ST) cout << student.first << endl;

    return 0;
}
