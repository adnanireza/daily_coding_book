#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
    Node *_constructFromSortedArray(const auto &beg, const auto &end) {
        if (beg > end) return nullptr;
        int diff = distance(beg, end);
        int midInc;
        if (diff & 1) {     // odd diff, meaning even number of elements
            midInc = diff / 2 + 1;  // Select the right element of the middle pair
        } else {            // even diff, meaning odd number of elements
            midInc = diff / 2;
        }
        Node *cur = new Node(*next(beg, midInc));
        cur->left = _constructFromSortedArray(beg, next(beg, midInc - 1));
        cur->right = _constructFromSortedArray(next(beg, midInc + 1), end);
        return cur;
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
    void constructFromSortedArray(const auto &beg, const auto &end) {   // Assumes all internal class memory released
        root = _constructFromSortedArray(beg, prev(end, 1));
    }
};

int main() {
    cout << boolalpha;
    vector<float> v {43,89,81,82,18,21,19,42,33,42.5,22,44,49,47,45,100};
    sort(v.begin(), v.end());
    BST<float> bst;
    try {
        // for (auto elem : v) {
        //     bst.insert(elem);
        // }
        bst.constructFromSortedArray(v.begin(), v.end());
        bst.disp();
        cout << bst.isPresent(41) << endl;
    }
    catch (string err) {
        cout << "Error: the following exception was thrown:" << endl;
        cout << err << endl;
    }

 
    return 0;
}