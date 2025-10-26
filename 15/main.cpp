#include <bits/stdc++.h>

using namespace std;

struct Block;
typedef list<Block> Blocks;
typedef Blocks::iterator BlockIter;

struct Block {
    int index, size;
    string name;
    BlockIter next;
    Block(int i, int s, string n): index(i), size(s), name(n) {}
};

struct FileSystem {
    int written = 0;
    int total = 0;

    map<string, BlockIter> table;
    Blocks disk;
    // end of disk (mimic of nullptr)
    BlockIter EOD = disk.end();

    auto open(string name) {
        // get file entry from file table
        auto entry = table.find(name);
        // check file existance
        if (entry == table.end()) return EOD;
        return entry->second;
    }

    void read(string name) {
        auto iter = open(name);
        if (iter == EOD) cout << "error";
        // iterate file blocks
        for (; iter != EOD; iter = iter->next) cout << iter->index << " ";
        cout << endl;
    }

    void write(string name, int size) {
        // check overwrite
        if (open(name) != EOD) {
            cout << "error\n";
            return;
        }
        // check size
        if (total - written < size) {
            cout << "diskfull\n";
            return;
        }
        // update stat
        written += size;

        int index = 0;
        vector<pair<BlockIter, int>> spaces;
        // scan empty spaces
        for (auto iter = disk.begin(); iter != EOD; iter++) {
            int delta = iter->index - index;
            // found perfect space
            if (delta >= size) {
                spaces = { { iter, delta } };
                break;
            }
            // found just empty space
            if (delta) spaces.emplace_back(iter, delta);
            // proceed
            index = iter->index + iter->size;
        }
        // allocate file blocks
        auto iter = EOD, next = iter;
        for (auto [space, delta]: spaces) {
            // new file block
            next = disk.insert(space, Block(space->index - delta, min(size, delta), name));
            // init as end of file
            next->next = EOD;
            // wire to file table or previous block
            if (iter == EOD) table[name] = next;
            else iter->next = next;
            // proceed
            iter = next;
            size -= delta;
            if (size <= 0) break;
        }
    }

    void del(string name) {
        auto iter = open(name);
        if (iter == EOD) {
            cout << "error\n";
            return;
        }
        while (iter != EOD) {
            auto next = iter->next;
            // update stat
            written -= iter->size;
            disk.erase(iter);
            iter = next;
        }
        // erase file from table
        table.erase(name);
    }

    void compact() {
        int index = 0;
        // full scan disk
        auto iter = disk.begin();
        // while end of disk
        while (iter->name != "") {
            auto i_next = next(iter);
            // reallocate index
            iter->index = index;
            // check next
            if (i_next->name == iter->name) {
                // merge
                iter->size += i_next->size;
                iter->next = i_next->next;
                disk.erase(i_next);
                // do not proceed, check again
                continue;
            }
            // update index as continuous
            index += iter->size;
            // proceed
            iter = i_next;
        }
    }

    FileSystem(int _total): total(_total) {
        // virtual file block which to simplify empty-disk-insert case
        disk.emplace_back(Block(total, 0, ""));
    }
};

int main() {
    int total, size;
    string op, name;

    cin >> total;

    FileSystem FS(total);

    while (true) {
        cin >> op;
        switch (op[0]) {
        case 'e':
            return 0;
        case 'c':
            FS.compact();
            break;
        case 's':
            cin >> name;
            FS.read(name);
            break;
        case 'd':
            cin >> name;
            FS.del(name);
            break;
        case 'w':
            cin >> name >> size;
            FS.write(name, size);
            break;
        }
    }
}
