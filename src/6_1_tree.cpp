#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

template <typename T>
struct DataType {
    T data;
    const bool isValid;
    DataType(T num) : data(num), isValid(true) {}
    DataType() : isValid(false) {}
    operator bool() { return isValid; }
    operator T() { return data; }
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
    int univalCount;
    void LoadDataCore(const unordered_map<int, vector<DataType<T>>> &payload, int level) {

    }
    pair<T, bool> numUnivalCore(Node *current) {
        // current != nullptr must be true as this point.
        pair<T, bool> leftResult, rightResult;
        if (!current->left && !current->right) {
            univalCount++;
            return make_pair(current->data, true);
        } else if (!current->left && current->right) {
            rightResult = numUnivalCore(current->right);
            if (rightResult.second == true && rightResult.first == current->data) {
                univalCount++;
                return make_pair(current->data, true);
            }
            return make_pair(current->data, false);
        } else if (current->left && !current->right) {
            leftResult = numUnivalCore(current->left);
            if (leftResult.second == true && leftResult.first == current->data) {
                univalCount++;
                return make_pair(current->data, true);
            }
            return make_pair(current->data, false);
        } else if (current->left && current->right) {
            leftResult = numUnivalCore(current->left);
            rightResult = numUnivalCore(current->right);
            // if (current == root->right) {
            //     cout << leftResult.first << endl;
            //     cout << leftResult.second << endl;
            //     cout << rightResult.first << endl << rightResult.second << endl;
            //     cout << univalCount << endl;
            //     cout << "current->data: " << current->data << endl;
            // }
            if (leftResult.second == true && rightResult.second == true &&
                    leftResult.first == current->data && rightResult.first == current->data) {
                univalCount++;
                return make_pair(current->data, true);
            }
            return make_pair(current->data, false);
        } else {
            // Should not be here
            throw "Error: Invalid condition";
        }
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

        // root = new Node('a');
        // root->left = new Node('a');
        // root->right = new Node('a');
        // root->right->left = new Node('a');
        // root->right->right = new Node('a');
        // root->right->right->right = new Node('b');

        // root = new Node('a');
        // root->left = new Node('c');
        // root->right = new Node('b');
        // root->right->left = new Node('b');
        // root->right->right = new Node('b');
        // root->right->right->right = new Node('b');
    }
    void LoadData(const unordered_map<int, vector<DataType<T>>> &payload) {
        //root = new Node<T>(payload[0][0])
    }
    int numUnival() {
        univalCount = 0;
        if (root == nullptr) return 0;
        numUnivalCore(root);
        return univalCount;
    }
};


typedef DataType<int> IntType;
int main() {
    cout << boolalpha;
    Tree<int> tree(true);
    cout << tree.numUnival() << endl;


    unordered_map<int, vector<DataType<int>>> treeData = {
        {0, {IntType(0)}},
        {1, {IntType(1), IntType(0)}},
        {2, {IntType(), IntType(), IntType(1), IntType(0)}},
        {3, {IntType(), IntType(), IntType(), IntType(), IntType(1), IntType(1), IntType(), IntType(),}}
    };
    return 0;
}