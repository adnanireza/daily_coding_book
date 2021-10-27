#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void disp(vector<T> v) {
    for (auto elem : v) {
        cout << elem << endl;
    }
}

template <typename T>
pair<int, int> unsorted_range(vector<T> v) {
    int len = v.size();
    int left = 0, right = len - 1;
    T running_min = v[len - 1];
    for (int i = len - 1; i >= 0; i--) {
        if (v[i] < running_min) {
            running_min = v[i];
        } else {
            left = i;
        }
    }
    T running_max = v[0];
    for (int i = 0; i < len; i++) {
        if (v[i] > running_max) {
            running_max = v[i];
        } else {
            right = i;
        }
    }
    return make_pair(left, right);
}

int main() {
    vector<int> v {4, 7, 8, 19, 60, 7, 55, 89};
    auto res = unsorted_range(v);
    cout << res.first << ", " << res.second << endl;
}