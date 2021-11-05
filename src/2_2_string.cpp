#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

string rev_str(string s) {
    reverse(s.begin(), s.end());
    return s;
}

bool is_pal(string s) {
    for (int i = 0; i < s.size() / 2; i++) {
        if (s[i] != s[s.size() - 1 - i]) {
            return false;
        }
    }
    return true;
}

vector<pair<int, int>> pal_pairs(vector<string> words) {
    vector<pair<int, int>> res;
    unordered_map<string, int> words_map;
    for (int i = 0; i < words.size(); i++) {
        words_map[words[i]] = i;
    }
    for (int i = 0; i < words.size(); i++) {
        string word = words[i];
        // Find suffixes
        for (int j = word.length(); j >= 0; j--) {
            string word_check_rev = word.substr(0, j);
            string word_check_pal = word.substr(j, word.length() - j);
            if (is_pal(word_check_pal)) {
                string reversed_word = rev_str(word_check_rev);
                if (int idx = words_map[reversed_word]) {
                    if (idx != i) res.push_back(make_pair(i, idx));
                }
            }
            
        }
        // Find prefixes
        for (int j = 0; j < word.length(); j++) {
            string word_check_rev = word.substr(j, word.length() - j);
            string word_check_pal = word.substr(0, j);
// cout << "i = " << i << ": " << word_check_rev << ", " << word_check_pal << endl;
            if (is_pal(word_check_pal)) {
                string reversed_word = rev_str(word_check_rev);
                if (int idx = words_map[reversed_word]) {
                    if (idx != i) res.push_back(make_pair(idx, i));
                }
            }
            
        }
    }
    return res;
}

int main() {
    vector<string> words = {"code", "edoc", "da", "d"};
    vector<pair<int, int>> res = pal_pairs(words);
    for (auto iter = res.begin(); iter != res.end(); iter++) {
        cout << "(" << (*iter).first << ", " << (*iter).second << ")" << endl;
    }
}


