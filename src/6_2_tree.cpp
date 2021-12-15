#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
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
    Node *preInCore(vector<T> preOrder, vector<T> inOrder) {
        T value = preOrder[0];
        Node *currentNode = new Node(value);
        int inOrderIdxOfValue = find(begin(inOrder), end(inOrder), value) - begin(inOrder);
        int leftLen = inOrderIdxOfValue, rightLen = inOrder.size() - inOrderIdxOfValue - 1;
        if (leftLen) {
            currentNode->left = preInCore(vector<T>{preOrder.begin() + 1, preOrder.begin() + 1 + leftLen},
                    vector<T>{inOrder.begin(), inOrder.begin() + leftLen});
        }
        if (rightLen) {
            currentNode->right = preInCore(vector<T>{preOrder.begin() + 1 + leftLen, preOrder.end()},
                    vector<T>{inOrder.begin() + inOrderIdxOfValue + 1, inOrder.end()});
        }
        return currentNode;
    }

public:
    Tree() {}
    Tree(bool) {
        root = new Node(0);
        root->left = new Node(1);
        root->right = new Node(0);
        root->right->left = new Node(1);
        root->right->right = new Node(0);
        root->right->left->left = new Node(1);
        root->right->left->right = new Node(1);
    }
    void constructFromPreIn(vector<T> preOrder, vector<T> inOrder) {
        if (!preOrder.size()) return;
        root = preInCore(preOrder, inOrder);
    }
    void disp() {
        if (root == nullptr) return;
        dispCore(root, 0);
    }
};

int main() {
    cout << boolalpha;
    vector<char> preOrder {'a', 'b', 'd', 'e', 'c', 'f', 'g'};
    vector<char> inOrder {'d', 'b', 'e', 'a', 'f', 'c', 'g'};
    Tree<char> tree;
    tree.constructFromPreIn(preOrder, inOrder);
    tree.disp();

    return 0;
}