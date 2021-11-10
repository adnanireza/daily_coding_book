#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string smallest_rotated_str(string s, int k) {
    string sorted = s;
    sort(sorted.begin(), sorted.end());
    string new_s = s;
    for (int i = 0; i < k; i++) {
// cout << new_s << endl;
        char c = sorted[i];
        int find_idx = new_s.find(c, i);
// cout << find_idx << endl;
        string save_left = new_s.substr(i, find_idx - i);
// cout << save_left << " --" << endl;
        new_s[i] = c;
        new_s.replace(i + 1, new_s.length() - (find_idx + 1), new_s, find_idx + 1, new_s.length() - (find_idx + 1));
// cout << "First replace <<" << new_s << ">>" << endl;
        new_s.replace(s.length() - save_left.length(), save_left.length(), save_left);
    }

    return new_s;
}

int main() {
    string s = "wordwhatever";
    int k = 6;
    for (int i = 0; i < k; i++) {
        cout << smallest_rotated_str(s, i) << endl;
    }
}