#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define logvar(var) #var << " = " << var << ", "

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
        return static_cast<bool>(_find(current, val));
    }
    Node *_find(Node *current, T val) {
        if (current == nullptr) return nullptr;
        else if (val > current->data) return _find(current->right, val);
        else if (val < current->data) return _find(current->left, val);
        else return current;
    }
    T _rightmost(Node *current) {    // Assumes current != nullptr
        if (current->right) return _rightmost(current->right);
        return current->data;
    }
    T _leftmost(Node *current) {    // Assumes current != nullptr
        if (current->left) return _leftmost(current->left);
        return current->data;
    }
    void _inOrderBracket(Node *current, T val, bool &isLeft, T &left, bool &isRight, T &right,
        bool &printStarted, T &lastPrinted, bool &leftFound, bool &rightFound) {
        if (rightFound) return;
        if (current == nullptr) return;
        _inOrderBracket(current->left, val, isLeft, left, isRight, right,
            printStarted, lastPrinted, leftFound, rightFound);
        if (rightFound) return;
        if (leftFound == false) {   // Looking for lower value
            if (current->data == val) {
                if (printStarted) {
                    isLeft = true;
                    left = lastPrinted;
                }
                leftFound = true;
            }
            lastPrinted = current->data;
            printStarted = true;
        } else {                    // Looking for higher value
            // This is the higher value
            isRight = true;
            right = current->data;
            rightFound = true;
        }
        // cout << "*** " << current->data << endl;
        _inOrderBracket(current->right, val, isLeft, left, isRight, right,
            printStarted, lastPrinted, leftFound, rightFound);
    }
    void _treeBracket(Node *current, T val, bool &isLeft, T &left, bool &isRight, T &right, T &minSofar, T &maxSofar) {
        if (current == nullptr) return;
        if (val > current->data) {
            if (val == minSofar) minSofar = current->data;
            else {
                minSofar = max(minSofar, current->data);
            }
            _treeBracket(current->right, val, isLeft, left, isRight, right, minSofar, maxSofar);
        } else if (val < current->data) {
            if (val == maxSofar) maxSofar = current->data;
            else {
                maxSofar = min(maxSofar, current->data);
            }
            _treeBracket(current->left, val, isLeft, left, isRight, right, minSofar, maxSofar);
        } else {        // Equality
            if (current->left) {
                minSofar = val == minSofar ? current->left->data : max(minSofar, current->left->data);
                T rightest = _rightmost(current->left);
                minSofar = max(minSofar, rightest);
            }
            if (current->right) {
                maxSofar = val == maxSofar ? current->right->data : min(maxSofar, current->right->data);
                T leftest = _leftmost(current->right);
                maxSofar = min(maxSofar, leftest);
            }
        }
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
    int getFloor(T val, T &res) {
        Node *current = _find(root, val);
if (current) cout << "Found: " << current->data << endl; else cout << "Not found" << endl;
        if (current == nullptr || current->left == nullptr) return -1;
        res = _rightmost(current->left);
        return 0;   // success;
    }
    void getBracket(T val, bool &isLeft, T &left, bool &isRight, T &right) {
        bool printStarted = false;
        T lastPrinted = T {};
        bool leftFound = false;
        bool rightFound = false;
        _inOrderBracket(root, val, isLeft, left, isRight, right, printStarted, lastPrinted, leftFound, rightFound);
    }
    void getBracketLog(T val, bool &isLeft, T &left, bool &isRight, T &right) {
        T minSofar = val, maxSofar = val;
        _treeBracket(root, val, isLeft, left, isRight, right, minSofar, maxSofar);
        if (minSofar != val) {
            isLeft = true;
            left = minSofar;
        }
        if (maxSofar != val) {
            isRight = true;
            right = maxSofar;
        }
    }
};

int main() {
    cout << boolalpha;
    vector<int> v {43, 22, 49, 82, 19, 42, 81, 33, 21};
    BST<int> bst;
    bst.InsertFromContainer(v.begin(), v.end());
    bst.disp();

    bool isLeft = false;
    int left;
    bool isRight = false;
    int right;
    int val = 82;
    // bst.getBracket(val, isLeft, left, isRight, right);
    bst.getBracketLog(val, isLeft, left, isRight, right);
    cout << val << ": [" << (isLeft ? to_string(left) : "") << ", " << (isRight ? to_string(right) : "") << "]" << endl;
 
    return 0;
}
