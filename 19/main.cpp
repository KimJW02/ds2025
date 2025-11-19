#include <bits/stdc++.h>

using namespace std;

struct Node {
    string data;
    Node *left, *right;
    Node(string d) : data(d), left(nullptr), right(nullptr) {}
};

Node* rightest(Node *node) {
    return node->right ? rightest(node->right) : node;
}

Node* leftest(Node *node) {
    return node->left ? leftest(node->left) : node;
}

void pushNode(Node *&node, string &data) {
    // check and create
    if (!node) {
        node = new Node(data);
        return;
    }
    // left
    if (data < node->data) return pushNode(node->left, data);
    // right
    if (data > node->data) return pushNode(node->right, data);
}

void deleteNode(Node *&node, string &data) {
    // check existance
    if (!node) return;
    // left
    if (data < node->data) return deleteNode(node->left, data);
    // right
    if (data > node->data) return deleteNode(node->right, data);
    // equal
    Node* m;
    // left subtree
    if (node->left) {
        m = rightest(node->left);
        node->data = m->data;
        return deleteNode(node->left, m->data);
    }
    // right subtree
    if (node->right) {
        m = leftest(node->right);
        node->data = m->data;
        return deleteNode(node->right, m->data);
    }
    // leaf
    delete node;
    node = nullptr;
}

void queryDepth(Node *node, int depth, int query, vector<string> &out) {
    // check existance
    if (!node) return;
    // inorder
    queryDepth(node->left, depth + 1, query, out);
    if (depth == query) out.push_back(node->data);
    queryDepth(node->right, depth + 1, query, out);
}

void queryLeaf(Node *node, vector<string> &out) {
    // check existance
    if (!node) return;
    // inorder
    queryLeaf(node->left, out);
    if (!node->left && !node->right) out.push_back(node->data);
    queryLeaf(node->right, out);
}

int main() {
    // root
    Node *root = nullptr;
    string cmd;

    while (cin >> cmd) switch (cmd[0]) {
        case 'q': return 0;
        case '+': {
            string s;
            cin >> s;
            pushNode(root, s);
            break;
        }
        case '-': {
            string s;
            cin >> s;
            deleteNode(root, s);
            break;
        }
        case 'd': {
            int k;
            cin >> k;
            vector<string> v;
            queryDepth(root, 1, k, v);
            if (v.empty()) cout << "NO";
            else for (auto d: v) cout << d << ' ';
            cout << endl;
            break;
        }
        case 'l': {
            vector<string> v;
            queryLeaf(root, v);
            for (auto d: v) cout << d << ' ';
            cout << endl;
            break;
        }
    }
}
