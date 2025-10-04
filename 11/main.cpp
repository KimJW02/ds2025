#include <bits/stdc++.h>

using namespace std;

struct Program {
    vector<string> Log;
    map<string, vector<string>> Function;
    stack<pair<string, int>> Call;

    int max_stack = 0;

    void init(int defines) {
        // set max stack equal to function defines (pigeonhole principle)
        max_stack = defines;
        // parse functions
        while (defines--) {
            string name, token;
            vector<string> body;
            cin >> name;
            while (cin >> token && token != "$") {
                body.emplace_back(token);
            }
            Function.insert({ name, body });
        }
    }

    bool is_func(string token) {
        return token.size() == 1 && isupper(token[0]);
    }

    string f_name;
    vector<string> f_body;
    int f_pointer;

    int f_begin(string name) {
        // stack overflow (deadlock)
        if (Call.size() == max_stack) return 1;
        // push call stack
        if (!f_name.empty()) Call.push(make_pair(f_name, f_pointer));
        f_name = name;
        f_body = Function.at(name);
        f_pointer = 0;
        return 0;
    }

    int f_end() {
        // check main function
        if (Call.empty()) return 1;
        // retrieve
        auto [name, pointer] = Call.top();
        Call.pop();
        f_name = name;
        f_body = Function.at(name);
        f_pointer = pointer;
        return 0;
    }

    int evaluate() {
        // start main function
        f_begin("M");
        while (1) {
            // check end of current function
            if (f_pointer == f_body.size()) {
                if (f_end()) return 0;
                continue;
            }
            string token = f_body[f_pointer++];
            // check start of child function
            if (is_func(token)) {
                if (f_begin(token)) return 1;
                continue;
            }
            // logging
            Log.push_back(f_name + "-" + token);
        }
    }

    void print(int index) {
        // normalize
        if (index <= 0) index += Log.size();
        else index--;
        // check index and print
        cout << (index < Log.size() ?  Log[index] : "NONE") << endl;
    }
};

int main() {
    int defines, k1, k2;
    cin >> defines >> k1 >> k2;

    Program P;
    P.init(defines);

    // check error (return code != 0)
    if (P.evaluate()) cout << "DEADLOCK";
    else {
        P.print(k1);
        P.print(k2);
    }

    return 0;
}
