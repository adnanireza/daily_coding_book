#include <iostream>
#include <string>
using namespace std;

struct ArithType {
    int num;
    string op;
    ArithType(int num) : num(num) { }
    ArithType(string op) : op(op) { }
    operator int() { return num; }
    int operator()(auto arg1, auto arg2) {
        if (op == "+") {
            return arg1 + arg2;
        } else if (op == "-") {
            return arg1 - arg2;
        } else if (op == "*") {
            return arg1 * arg2;
        } else if (op == "/") {
            return arg1 / arg2;
        } else {
            throw "Error: Lo legal operation defined in \"op\"";
        }
    }
};
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

class ArithTree : public Tree<ArithType> {
protected:
    int evalCore(Node *current) {
        if (current->left && current->right) {
            int left = evalCore(current->left);
            int right = evalCore(current->right);
            return current->data(left, right);
        }
        return current->data;
    }
public:
    ArithTree() {
        this->root = new Node(ArithType("*"));
        this->root->left = new Node(ArithType("+"));
        this->root->right = new Node(ArithType("+"));
        this->root->left->left = new Node(ArithType(3));
        this->root->left->right = new Node(ArithType(2));
        this->root->right->left = new Node(ArithType(4));
        this->root->right->right = new Node(ArithType(5));
    }
    int eval() {
        if (this->root == nullptr) throw "Error: root is null";
        return evalCore(root);
    }

};

int main() {
    cout << boolalpha;
    ArithTree at;
    cout << at.eval() << endl;
 
    return 0;
}