#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

template <typename T>
void disp(vector<T> v) {
    for (auto elem : v) {
        cout << elem << endl;
    }
}
// template <typename T>
// void disp_range(unordered_set<T>::iterator &begin) { //, std::unordered_set<T>::iterator &end) {
    // for (auto iter = begin; iter != end; iter++) {
    //     cout << *iter << endl;
    // }
// }

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

void gen_ana(string prefix, string sub_w, vector<string> &anagrams) {
    if (sub_w.size() == 0) {
        anagrams.push_back(prefix);
        return;
    }
    for (int i = 0; i < sub_w.size(); i++) {
        char prefix_char = sub_w[i];
        string sub_sub_w(sub_w);
        sub_sub_w.erase(i, 1);
        gen_ana(prefix + prefix_char, sub_sub_w, anagrams);
    }
}

vector<string> gen_all_anagram(string w) {
    vector<string> anagrams;
    gen_ana("", w, anagrams);
    return anagrams;
}

vector<int> anagram_pos2(string w, string s) {
    vector<string> all_anagrams_vector = gen_all_anagram(w);
    unordered_set<string> all_anagrams_set(all_anagrams_vector.begin(), all_anagrams_vector.end());
    // for (auto iter = all_anagrams_set.begin(); iter != all_anagrams_set.end(); iter++) {
    //     cout << *iter << endl;
    // }
    vector<int> res;
    res.reserve(s.size());
    for (int i = 0; i < s.size(); i++) {
        string sub_s_of_len_w = s.substr(i, w.size());
        if (all_anagrams_set.count(sub_s_of_len_w)) res.push_back(i);
    }
    return res;
}

int main() {
    string s("abxaba");
    string w("ab");
    // vector<string> res = gen_all_anagram(w);
    // disp(res);
    vector<int> res = anagram_pos2(w, s);
    disp(res);
}