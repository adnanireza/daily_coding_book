#include <vector>
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
    shared_ptr<Node> trie_;
    shared_ptr<Node> find(string word) {
        shared_ptr<Node> cur = trie_;
        for (char c : word) {
            if (cur->node.count(c) == 0) return nullptr;
            cur = cur->node[c];
        }
        return cur;
    }
    void autoComplete(shared_ptr<Node> cur, vector<string> &res, string word) {
        if (cur->terminal) res.push_back(word);
        for (auto &[key, val] : cur->node) {
            autoComplete(val, res, word + key);
        }
    }
public:
    Trie() : trie_(make_shared<Node>()) {}
    void Insert(string word) {
        shared_ptr<Node> cur = trie_;
        for (char c : word) {
            if (cur->node.count(c) == 0) {
                cur->node[c] = make_shared<Node>();
            }
            cur = cur->node[c];
        }
        cur->terminal = true;
    }
    bool Find(string word) {
        shared_ptr<Node> cur = trie_;
        for (char c : word) {
            if (cur->node.count(c) == 0) return false;
            cur = cur->node[c];
        }
        return cur->terminal;
    }
    vector<string> AutoComplete(string word) {
        vector<string> res {};
        shared_ptr<Node> cur = find(word);
        if (cur == nullptr) return res;
        autoComplete(cur, res, word);
        return res;
    }
};

int main() {
    Trie mytrie;
    mytrie.Insert("Factory");
    mytrie.Insert("Factual");
    mytrie.Insert("Fantom");
    mytrie.Insert("Foto");
    mytrie.Insert("Fac");

    for (auto elem : mytrie.AutoComplete("Fac")) {
        cout << elem << endl;
    }


    cout << "done" << endl;
    return 0;
}