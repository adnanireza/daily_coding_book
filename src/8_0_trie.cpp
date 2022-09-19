#include <map>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Trie {
    struct Node {
        map<char, shared_ptr<Node>> node;
        bool terminal = false;
    };
    shared_ptr<Node> trie;
public:
    Trie() : trie(make_shared<Node>()) {}
    void Insert(string word) {
        shared_ptr<Node> cur = trie;
        for (char c : word) {
            if (cur->node.count(c) == 0) {
                cur->node[c] = make_shared<Node>();
            }
            cur = cur->node[c];
        }
        cur->terminal = true;
    }
    bool Find(string word) {
        shared_ptr<Node> cur = trie;
        for (char c : word) {
            if (cur->node.count(c) == 0) return false;
            cur = cur->node[c];
        }
        return cur->terminal;
    }
};

int main() {
    Trie mytrie;
    mytrie.Insert("Factory");
    mytrie.Insert("Factual");

    cout << boolalpha << mytrie.Find("what") << endl;

    cout << "done" << endl;
    return 0;
}