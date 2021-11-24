#include <iostream>
#include <queue>
using namespace std;

template <typename T>
void disp(vector<T> v) {
    for (auto elem : v) {
        cout << elem << endl;
    }
}

vector<int> decode(const vector<char> &code) {
    int len = code.size();
    int lastVal = len - 1;
    if (len == 0) return vector<int> {0};
    int numPlus = 0, numMinus = 0;
    for (int i = 0; i < len; i++) {
        if (code[i] == '+') numPlus++;
        else if (code[i] == '-') numMinus++;
    }
    int divideNum = lastVal - numPlus;
    queue<int> plusQ;
    for (int i = divideNum; i <= lastVal; i++) plusQ.push(i);

    queue<int> minusQ;
    for (int i = divideNum - 1; i >= 0; i--) minusQ.push(i);

    // main loop
    vector<int> res; res.reserve(len);
    res.push_back(plusQ.front()); plusQ.pop();
    for (int i = 1; i < len; i++) {
        if (code[i] == '+') {
            res.push_back(plusQ.front()); plusQ.pop();
        } else if (code[i] == '-') {
            res.push_back(minusQ.front()); minusQ.pop();
        }
    }
    return res;
}

int main() {
    vector<char> code {'\0', '+', '+', '-', '+', '-', '-', '+', '-'};
    // vector<char> code {'\0', '+', '+', '+', '+', '+', '+', '+', '+'};
    disp(decode(code));

    return 0;
}