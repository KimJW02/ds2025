#include <bits/stdc++.h>

using namespace std;
using Applicant = pair<int, int>;
using Applicants = vector<Applicant>;
using Record = pair<string, Applicants>;


struct DB {
    static int sum_applicants(Record &T) {
        return accumulate(T.second.begin(), T.second.end(), 0, [](int A, Applicant &B) { return A + B.second; });
    }

    static bool compare_record(Record &A, Record &B) {
        int diff = A.second.size() - B.second.size();
        // if same size, use total score
        if (diff == 0) diff = sum_applicants(A) - sum_applicants(B);
        // if same sum, use name
        return diff ? diff > 0 : A.first < B.first;
    }

    static void sort_scores(Record &R) {
        // filter popped(zero-marked) applicants
        R.second.erase(remove_if(R.second.begin(), R.second.end(), [](Applicant &A) { return A.first == 0; }), R.second.end());
        // sort by score
        sort(R.second.begin(), R.second.end(), [](Applicant &A, Applicant &B) {
                int diff = A.second - B.second;
                // if same score, use id
                return diff ? diff > 0 : A.first > B.first;
        });
    }

    int threshold = 0;

    // dataset
    vector<Record> RV;

    auto flatten() {
        // sort scores with compaction
        for_each(RV.begin(), RV.end(), sort_scores);
        // sort records
        sort(RV.begin(), RV.end(), compare_record);
        // create flatten view
        vector<Applicant*> RA;
        if (RV.size() > 0) for (int col = 0; col < RV[0].second.size(); col++) {
            for (auto &[univ, R]: RV) {
                // check boundary
                if (R.size() <= col || R.size() < threshold) break;
                RA.emplace_back(&R[col]);
            }
        }

        return RA;
    }

    void pop(int from, int to) {
        // sort only if pop
        auto RA = flatten();

        to = min(to, (int)RA.size() - 1);
        for (int i = from; i <= to; i++) {
            printf("%06d ", RA[i]->first);
            // mark as zero(deleted)
            RA[i]->first = 0;
        }
        cout << endl;
    }

    void push(string univ, Applicant A) {
        auto iter = find_if(RV.begin(), RV.end(), [&](Record &R) { return R.first == univ; });
        // create new
        if (iter == RV.end()) RV.emplace_back(univ, Applicants{ A });
        // just push
        else iter->second.emplace_back(A);
    }
};

int main() {
    DB db;
    int number, code, score;
    string query;

    cin >> number >> db.threshold;

    while (number--) {
        cin >> query >> code >> score;
        if (query == "POP") db.pop(code - 1, score - 1);
        else db.push(query, make_pair(code, score));
    }

    return 0;
}
