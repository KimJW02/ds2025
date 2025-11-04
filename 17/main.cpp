#include <bits/stdc++.h>

using namespace std;

struct Member {
    string name, boss = "";
    int distance = -1, hands = 1;
    vector<string> men;
};

unordered_map<string, Member> mafia;

void parse() {
    int num;
    string man, boss;
    cin >> num;
    while (--num) {
        cin >> man >> boss;
        mafia[boss].name = boss;
        mafia[boss].men.emplace_back(man);
        mafia[man].name = man;
        mafia[man].boss = boss;
    }
}

void calculate(Member* member) {
    member->distance++;
    for (auto &man: member->men) {
        mafia[man].distance = member->distance;
        calculate(&mafia[man]);
        member->hands += mafia[man].hands;
    }
}

void process() {
    Member* king;
    for (auto &[_, member]: mafia) if (member.boss == "") {
        king = &member;
        break;
    }
    calculate(king);
}

void output() {
    vector<pair<string, Member>> members(mafia.begin(), mafia.end());
    sort(members.begin(), members.end(), [](auto &a, auto &b) {
         int delta_h = a.second.hands - b.second.hands;
         if (delta_h != 0) return delta_h > 0;
         int delta_d = a.second.distance - b.second.distance;
         if (delta_d != 0) return delta_d < 0;
        return a.first < b.first;
    });
    for (auto &m: members) {
        cout << m.first << endl;
    }
}

int main() {
    parse();
    process();
    output();
    return 0;
}
