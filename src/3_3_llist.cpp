#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node *next;
    Node(T value) : data(value), next(nullptr) {

    }
};
int iter = 0;
template <typename T>
class LinkedList {
protected:
    Node<T> *root;
    Node<T> *find(T value, Node<T> *current) {
        if (current == nullptr) return nullptr;
        if (current->value == value) return current;
        return find(value, current->next);
    }
    Node<T> *findLast(Node<T> *current) {
        if (current == nullptr) return nullptr;
        if (current->next == nullptr) return current;
        return findLast(current->next);
    }
    void dispCore(Node<T> *current) {
// if (iter++ == 6) return;
        if (current == nullptr) return;
        cout << current->data << endl;
        dispCore(current->next);
    }

public:
    LinkedList() : root(nullptr) {

    }
    Node<T> *getRoot() { return root; }
    void insertToEnd(T value) {
        Node<T> *newNode = new Node<T>(value);
        Node<T> *last = findLast(root);
        if (last) last->next = newNode;
        else root = newNode;
    }
    void alternate() {
        if (root == nullptr || root->next == nullptr) return;
        if (root->data > root->next->data) {
            Node<T> *temp = root->next;
            root->next = root->next->next;
            temp->next = root;
            root = temp;
        }
        if (root->next->next == nullptr) return;
        if (root->next->next->data > root->next->data) {
            Node<T> *temp = root->next->next;
            root->next->next = root->next->next->next;
            temp->next = root->next;
            root->next = temp;
        }
        Node<T> *prev = root->next, *current = prev->next->next;
        while (current) {
// dispLine();
            if (prev->next->data > current->data) {
                prev->next->next = current->next;
                current->next = prev->next;
                prev->next = current;
                current = prev->next->next;
            }
            if (current->next == nullptr) break;
            if (current->next->data > current->data) {
                prev->next->next = current->next;
                current->next = prev->next->next->next;
                prev->next->next->next = current;
                current = prev->next->next;
            }
            prev = current;
            current = prev->next->next;
        }
    }
    void disp() {
        dispCore(root);
    }
    void dispLine() {
        for (Node<T> *current = root; current; current = current->next) {
            cout << current->data << ", ";
        }
        cout << endl;
    }
};

int main() {
    LinkedList<int> llist;
    llist.insertToEnd(7);
    llist.insertToEnd(6);
    llist.insertToEnd(5);
    llist.insertToEnd(4);
    llist.insertToEnd(3);
    llist.insertToEnd(2);
    llist.insertToEnd(1);
    llist.alternate();
    llist.disp();


    return 0;
}