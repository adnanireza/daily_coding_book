#include <iostream>
#include <unordered_set>
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

template <typename T>
T getIntersect(LinkedList<T> &list1, LinkedList<T> &list2) {
    unordered_set<T> list1Set;
    for (Node<T> *current = list1.getRoot(); current; current = current->next) {
        list1Set.insert(current->data);
    }
    for (Node<T> *current = list2.getRoot(); current; current = current->next) {
        if (list1Set.count(current->data)) return current->data;
    }
    return 0;   // error
}

int main() {
    LinkedList<int> llist;
    llist.insertToEnd(7);
    llist.insertToEnd(6);
    llist.insertToEnd(5);
    llist.insertToEnd(4);
    llist.insertToEnd(3);
    llist.insertToEnd(2);
    llist.insertToEnd(1);
    LinkedList<int> llist2;
    llist2.insertToEnd(93);
    llist2.insertToEnd(63);
    llist2.insertToEnd(15);
    llist2.insertToEnd(4);
    llist2.insertToEnd(432);
    llist2.insertToEnd(10);
    llist2.insertToEnd(99);
    
    cout << getIntersect(llist, llist2) << endl;

    return 0;
}