#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

bool isOpening(char c) {
    return c == '[' || c == '{' || c == '(';
}
bool isClosing(char c) {
    return c == ']' || c == '}' || c == ')';
}
unordered_map<char, char> bracketMap{
    {'[', ']'},
    {'{', '}'},
    {'(', ')'},
};
bool isMatch(char cOpen, char cClose) {
    return bracketMap[cOpen] == cClose;
}

bool bracketBalance(string str) {
    stack<char> stk;
    for (int i = 0; i < str.length(); i++) {
        if (isOpening(str[i])) {
            stk.push(str[i]);
        } else if (isClosing(str[i])) {
            if (stk.empty() || !isMatch(stk.top(), str[i])) return false;
            stk.pop();
        }
    }
    return stk.empty();
}

int main() {
    string s {"([])[sdf]sfdsdf({})"};
    // string s {"((()"};
    cout << boolalpha;
    cout << bracketBalance(s) << endl;

    return 0;
}