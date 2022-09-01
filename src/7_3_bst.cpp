#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
class BST {
protected:
    struct Node {
        T data;
        Node *left = nullptr, *right = nullptr;
        Node(T val) : data(val) {}
    };
    Node *root = nullptr;
    void dispCore(Node *current, int level) {
        for (int i = 0; i < level; i++) std::cout << "\t";
        std::cout << current->data << " :==> [" << (current->left ? std::to_string(current->left->data) :"")
                << ", " << (current->right ? std::to_string(current->right->data) : "") << "]" << std::endl;
        if (current->left) dispCore(current->left, level + 1);
        if (current->right) dispCore(current->right, level + 1);
    }
    Node *_insert(Node *current, T val) {
        if (!current) return new Node(val);
        else if (val > current->data) current->right = _insert(current->right, val);
        else if (val < current->data) current->left = _insert(current->left, val);
        else throw std::string{"Error: Duplicate values not allowed in BST"};
        return current;
    }
    bool _isPresent(Node *current, T val) {
        if (!current) return false;
        if (current->data == val) return true;
        else if (val > current->data) return _isPresent(current->right, val);
        else if (val < current->data) return _isPresent(current->left, val);
        throw __FUNCTION__ + std::string{"Error: Control should not be here! All values of val are covered."};
    }
public:
    void disp() {
        if (root == nullptr) return;
        dispCore(root, 0);
    }
    void insert(T val) {
        root = _insert(root, val);
    }
    bool isPresent(T val) {
        return _isPresent(root, val);
    }
    void InsertFromContainer(const auto &beg, const auto &end) {
        for (auto it = beg; it != end; it++) {
            insert(*it);
        }
    }
};

struct Node {
    int data;
    Node *left = nullptr, *right = nullptr;
    Node(int val) : data(val) {}
    Node(int val, Node *left, Node *right) : data(val), left(left), right(right) {}
};
void dispCore(Node *current, int level) {
    for (int i = 0; i < level; i++) std::cout << "\t";
    std::cout << current->data << " :==> [" << (current->left ? std::to_string(current->left->data) :"")
            << ", " << (current->right ? std::to_string(current->right->data) : "") << "]" << std::endl;
    if (current->left) dispCore(current->left, level + 1);
    if (current->right) dispCore(current->right, level + 1);
}
void disp(Node *root) {
    if (root == nullptr) return;
    dispCore(root, 0);
}
vector<Node *> genAllBstsCore(int low, int high) {
    if (low > high) return {};
    else if (low == high) return {new Node(low)};
    vector<Node *> res;
    for (int val = low; val <= high; val++) {
        vector<Node *> lefts = genAllBstsCore(low, val - 1);
        vector<Node *> rights = genAllBstsCore(val + 1, high);
        for (auto left : lefts) {
            for (auto right : rights) {
                res.push_back(new Node(val, left, right));
            }
            if (rights.empty()) res.push_back(new Node(val, left, nullptr));
        }
        if (lefts.empty()) {
            for (auto right : rights) {
                res.push_back(new Node(val, nullptr, right));
            }
            if (rights.empty()) res.push_back(new Node(val, nullptr, nullptr));
        }
    }
    return res;
}
vector<Node *> genAllBsts(int n) {
    if (n == 0) return {};
    return genAllBstsCore(1, n);
}

int main() {
    auto bsts = genAllBsts(8);

    for (auto elem : bsts) {
        disp(elem);
    }

    cout << bsts.size() << endl;
 
    return 0;
}






















