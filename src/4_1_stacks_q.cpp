#include <iostream>
#include <stack>
using namespace std;

template<typename T>
class MaxStack {
protected:
    stack<T> *dataStack = nullptr;
    stack<T> *maxStack = nullptr;
public:
    MaxStack() {
        dataStack = new stack<T>;
        maxStack = new stack<T>;
    };
    void push(T val) {
        dataStack->push(val);
        maxStack->push(maxStack->empty() || (val > maxStack->top()) ? val : maxStack->top());
    }
    void pop() {
        if (dataStack->empty()) throw "Error: Empty stack!";
        dataStack->pop();
        maxStack->pop();
    }
    T top() {
        return dataStack->top();
    }
    T max() {
        if (maxStack->empty()) throw "Error: Empty maxStack";
        return maxStack->top();
    }
};

int main() {
    MaxStack<int> ms;
    ms.push(4);
    cout << ms.max() << endl;
    ms.push(8);
    cout << ms.max() << endl;
    ms.push(2);
    cout << ms.max() << endl;
    ms.push(9);
    cout << ms.max() << endl;

    cout << "------------" << endl;

    ms.pop();
    cout << ms.max() << endl;
    ms.pop();
    cout << ms.max() << endl;
    ms.pop();
    cout << ms.max() << endl;
    ms.pop();
 

    return 0;
}