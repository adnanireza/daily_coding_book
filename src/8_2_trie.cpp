#include <map>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Trie {
    struct Node {
        map<char, shared_ptr<Node>> node;
        int sum = 0;
        bool terminal = false;
        Node() = default;
        Node(int val) : sum(val) {}
    };
    shared_ptr<Node> trie;
    shared_ptr<Node> find(string word) {
        shared_ptr<Node> cur = trie;
        for (char c : word) {
            if (cur->node.count(c) == 0) return nullptr;
            cur = cur->node[c];
        }
        return cur;
    }
public:
    Trie() : trie(make_shared<Node>()) {}
    void Insert(string word, int val) {
        shared_ptr<Node> cur = trie;
        for (char c : word) {
            if (cur->node.count(c) == 0) {
                cur->node[c] = make_shared<Node>();
            }
            cur->sum += val;
            cur = cur->node[c];
        }
        cur->sum += val;
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
    int Sum(string word) {
        shared_ptr<Node> cur = find(word);
        return cur == nullptr ? 0 : cur->sum;
    }
};

int main() {
    Trie mytrie;
    mytrie.Insert("Factory", 5);
    mytrie.Insert("Factual", 10);
    mytrie.Insert("Fan", 2);
    mytrie.Insert("other" , 4);

    cout << mytrie.Sum("Fa") << endl;



    cout << "done" << endl;
    return 0;
}