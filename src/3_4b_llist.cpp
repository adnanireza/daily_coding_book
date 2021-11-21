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
    int getLen() {
        int count = 0;
        for (Node<T> *current = root; current; current = current->next, count++);
        return count;
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
T getJoin(LinkedList<T> &list1, LinkedList<T> &list2) {
    Node<T> *current1 = list1.getRoot(), *current2 = list2.getRoot();
    int diff = list1.getLen() - list2.getLen();
    if (diff > 0) {
        for (; current1 && diff; current1 = current1->next, diff--);
    } else if (diff < 0) {
        for (; current2 && diff; current2 = current2->next, diff++);
    }
    for (; current1 && current2; current1 = current1->next, current2 = current2->next) {
        if (current1->data == current2->data) return current1->data;
    }
    return 0;   // error
}

int main() {
    LinkedList<int> llist;
    llist.insertToEnd(7);
    llist.insertToEnd(6);
    llist.insertToEnd(44);
    llist.insertToEnd(231);
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
    llist2.insertToEnd(3);
    llist2.insertToEnd(2);
    llist2.insertToEnd(1);
    
    cout << getJoin(llist, llist2) << endl;

    return 0;
}