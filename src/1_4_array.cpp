#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
void disp(vector<T> v) {
    for (auto elem : v) {
        cout << elem << endl;
    }
}

template <typename T>
vector<T> less_right(vector<T> v) {
    vector<T> res (v.size(), 0);
    for (int i = v.size() - 2; i >= 0; i--) {
        if (v[i] > v[i + 1]) {
            res[i] = res[i + 1] + 1;
        } else if (v[i] == v[i + 1]) {
            res[i] = res[i + 1];
        } else {    // v[i] < v[i + 1]
            for (int j = i + 1; j < v.size() && res[i] < res[i + 1]; j++) {
                if (v[i] > v[j]) {
                    res[i]++;
                }
            }
        }
    }
    return res;
}

template<typename T>
int insert_sorted(vector<T> &v, T val) {
    if (v.size() == 0) {
        v.insert(v.end(), val);
        return 0;
    }
    int beg_idx = 0, end_idx = v.size() - 1;
    while (beg_idx < end_idx) {
        int mid_idx = beg_idx + (end_idx - beg_idx) / 2;
        if (val > v[mid_idx]) {
            beg_idx = mid_idx + 1;
            end_idx = end_idx;
        } else if (val <= v[mid_idx]) {
            beg_idx = beg_idx;
            end_idx = mid_idx;
        }
    }
    if (val > v[beg_idx]) {
        v.insert(v.begin() + beg_idx + 1, val);
        return beg_idx + 1;
    } else if (val <= v[beg_idx]) {
        v.insert(v.begin() + beg_idx, val);
        return beg_idx;
    }
    return -1;  // error
}
template <typename T>
vector<T> less_right2(vector<T> v) {
    vector<T> res (v.size(), 0);
    vector<T> seen {};
    seen.reserve(v.size());
    for (int i = v.size() - 1; i >= 0; i--) {
        int idx = insert_sorted(seen, v[i]);
        res[i] = idx;
    }
    return res;
}

int main() {
    vector<int> v {3, 4, 7, 9, 9, 6, 4, 1};
    vector<int> res = less_right2(v);
    disp(res);
    cout << "HHHHHHHHHHHello" << endl;
}