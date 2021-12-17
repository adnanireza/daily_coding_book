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
        for (int i = 0; i < level; i++) cout << "\t";
        cout << current->data << " :==> [" << (current->left ? to_string(current->left->data) :"")
                << ", " << (current->right ? to_string(current->right->data) : "") << "]" << endl;
        if (current->left) dispCore(current->left, level + 1);
        if (current->right) dispCore(current->right, level + 1);
    }
    Node *_insert(Node *current, T val) {
        if (!current) return new Node(val);
        else if (val > current->data) current->right = _insert(current->right, val);
        else if (val < current->data) current->left = _insert(current->left, val);
        else throw string{"Error: Duplicate values not allowed in BST"};
        return current;
    }
    bool _isPresent(Node *current, T val) {
        if (!current) return false;
        if (current->data == val) return true;
        else if (val > current->data) return _isPresent(current->right, val);
        else if (val < current->data) return _isPresent(current->left, val);
        throw __FUNCTION__ + string{"Error: Control should not be here! All values of val are covered."};
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
};

int main() {
    cout << boolalpha;
    vector<int> v {43, 22, 49, 82, 19, 42, 81, 33, 22};
    BST<int> bst;
    try {
        for (auto elem : v) {
            bst.insert(elem);
        }
        bst.disp();
        cout << bst.isPresent(41) << endl;
    }
    catch (string err) {
        cout << "Error: the following exception was thrown:" << endl;
        cout << err << endl;
    }
 
    return 0;
}