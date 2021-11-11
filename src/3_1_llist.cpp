#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node *next;
    Node(T value) : data(value), next(nullptr) {

    }
};

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
         if (current == nullptr) return;
         cout << current->data << endl;
         dispCore(current->next);
     }
     void reverseCore(Node<T> *current, Node<T> *saved) {
         if (saved == nullptr) {
             root = current;
             return;
         }
         Node<T> *newSaved = saved->next;
         Node<T> *newCurrent = saved;
         saved->next = current;
         reverseCore(newCurrent, newSaved);
     }
public:
    LinkedList() : root(nullptr) {

    }
    void insertToEnd(T value) {
        Node<T> *newNode = new Node<T>(value);
        Node<T> *last = findLast(root);
        if (last) last->next = newNode;
        else root = newNode;
    }
    void disp() {
        dispCore(root);
    }
    void reverse() {
        if (root == nullptr) return;
        if (root->next == nullptr) return;
        if (root->next->next == nullptr) {
            Node<T> *savedRoot = root;
            root = savedRoot->next;
            root->next = savedRoot;
            root->next->next = nullptr;
        }
        Node<T> *savedNode = root->next->next;
        Node<T> *nextNode = root->next;
        root->next->next = root;
        root->next = nullptr;
        reverseCore(nextNode, savedNode);
    }
};

int main() {
    LinkedList<int> llist;
    llist.insertToEnd(45);
    llist.insertToEnd(4);
    llist.insertToEnd(5);
    llist.insertToEnd(8);
    llist.disp();
    llist.reverse();
    llist.disp();
    return 0;
}