#include <iostream>
#include <string>
using namespace std;

bool get_is_down(int idx, int n) {
    return idx % ((n - 1) * 2) < n - 1;
}
int get_num_space(int n, int line, bool is_down) {
    return is_down ? (2 * n - 3) - line * 2 : (2 * n - 3) - (n - 1 - line) * 2;
}
int get_num_letter_skip(int n, int line, bool is_down) {
    return is_down ? (n - line - 1) * 2 : (n - (n - line)) * 2;
}
void zigzag(string s, int n) {
    for (int line = 0; line < n; line++) {
        for (int j = 0; j < line; j++) {
            cout << " ";
        }
        for (int i = line; i < s.length();) {
            cout << s[i];
            bool is_down = get_is_down(i, n);
            int num_space = get_num_space(n, line, is_down);
            int num_letter_skip = get_num_letter_skip(n, line, is_down);
// cout << "line = " << line << endl;
// cout << is_down << ", " << num_space << ", " << num_letter_skip << endl;
// if () return;
            for (int j = 0; j < num_space; j++) {
                cout << " ";
            }
            i += num_letter_skip;
        }
        cout << endl;
    }
}

int main() {
    string s = "thisisazigjag";
    int n = 5;
    zigzag(s, n);
    return 0;
}