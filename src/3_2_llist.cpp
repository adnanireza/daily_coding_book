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
    void addAsNum(LinkedList<int> *num) {
        int carry = 0;
        Node<int> *current1 = root, *current2 = num->getRoot();
        Node<int> *prev1 = nullptr, *prev2 = nullptr;
        if (current1 == nullptr && current2) root = current1 = new Node<int> (0);
        while (current1 || current2 || carry) {
            int digitSum = (current1 ? current1->data : 0) + (current2 ? current2->data : 0) + carry;
// cout << __LINE__ << ": " << digitSum << endl;
            carry = digitSum / 10;
            if (current1 == nullptr) {
                prev1->next = new Node<int> (digitSum % 10);
                current1 = prev1->next;
// cout << __LINE__ << endl;
            } else {
// cout << __LINE__ << ": " << digitSum % 10 << endl;
                current1->data = digitSum % 10;
            }
// cout << __LINE__ << endl;
            prev1 = current1;
            current1 = current1->next;
            current2 = current2 ? current2->next : current2;
        }
    }
    void disp() {
        dispCore(root);
    }
};
using NumInList = LinkedList<int>;



int main() {
    NumInList num1;
    num1.insertToEnd(1);
    num1.insertToEnd(2);
    num1.insertToEnd(3);
    num1.insertToEnd(4);
    num1.insertToEnd(5);
    NumInList num2;
    num2.insertToEnd(4);
    num2.insertToEnd(8);
    num2.insertToEnd(0);
    num2.insertToEnd(9);
    num2.insertToEnd(1);

    num1.addAsNum(&num2);
    num1.disp();

    return 0;
}