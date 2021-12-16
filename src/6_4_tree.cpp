#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
using namespace std;

template <typename T>
class Tree {
protected:
    struct Node {
        T data;
        Node *left = nullptr, *right = nullptr;
        Node(T val) : data(val) {}
    };
    Node *root;
    void dispCore(Node *current, int level) {
        for (int i = 0; i < level; i++) cout << "\t";
        cout << current->data << " :==> [" << (current->left ? (current->left->data) : (char)0)
                << ", " << (current->right ? (current->right->data) : (char)0) << "]" << endl;
        if (current->left) dispCore(current->left, level + 1);
        if (current->right) dispCore(current->right, level + 1);
    }

public:
    void disp() {
        if (root == nullptr) return;
        dispCore(root, 0);
    }
};

class IntTree : public Tree<int> {
protected:
    unordered_map<int, int> *levelToSum;
    void minSumCore(Node *current, int level) {
        if (current == nullptr) return;
        (*levelToSum)[level] += current->data;
        minSumCore(current->left, level + 1);
        minSumCore(current->right, level + 1);
    }
public:
    IntTree() {
        this->root = new Node(10);
        this->root->left = new Node(2);
        this->root->right = new Node(3);
        this->root->right->left = new Node(4);
        this->root->right->right = new Node(5);
    }
    tuple<int, int> minSum() {
        if (this->root == nullptr) throw "Error: root is null";
        levelToSum = new unordered_map<int, int>;
        minSumCore(root, 0);
        int minVal = numeric_limits<int>::max();
        int level;
        for (auto [key, val] : *levelToSum) {
            if (val < minVal) {
                level = key;
                minVal = val;
            }
        }
        delete levelToSum;
        return make_tuple(level, minVal);
    }
};

int main() {
    cout << boolalpha;
    IntTree t;
    auto [level, sum] = t.minSum();
    cout << level << endl << sum << endl;
 
    return 0;
}