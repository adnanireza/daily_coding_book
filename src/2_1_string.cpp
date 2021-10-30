#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

template <typename T>
void disp(vector<T> v) {
    for (auto elem : v) {
        cout << elem << endl;
    }
}

vector<int> anagram_pos(string w, string s) {
    vector<int> res;
    res.reserve(s.size());
    unordered_map<char, bool> w_map;
    for (int i = 0; i < w.length(); i++) {
        w_map[w[i]] = true;
    }
    unordered_map<int, unordered_map<char, bool>> pos_to_map;
    for (int i = 0; i < s.length(); i++) {
        for (auto iter = pos_to_map.begin(); iter != pos_to_map.end();) {
            unordered_map<char, bool> current = iter->second;
            int pos = iter->first;
            if (current[s[i]]) {
                current[s[i]] = false;
                if (i - pos + 1 == w.size()) {  // Found
                    res.push_back(pos);
                    pos_to_map.erase(iter++);
                } else {
                    iter++;
                }
            } else {
                pos_to_map.erase(iter++);
            }
        }
        if (w_map[s[i]]) {
            unordered_map<char, bool> new_map (w_map);
            new_map[s[i]] = false;
            pos_to_map[i] = new_map;
        }
    }
    return res;
}

int main() {
    string s("abxaba");
    string w("ab");
    vector<int> res = anagram_pos(w, s);
    disp(res);
}