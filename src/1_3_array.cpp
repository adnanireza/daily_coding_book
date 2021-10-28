#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

template <typename T>
int max_sub_sum(vector<T> v) {
    int len = v.size();
    int starting_idx = 0, max_sum = 0, current_sum = 0;
    for (int i = 0; i < len; i++) {
        current_sum += v[i];
        if (current_sum > max_sum) {
            max_sum = current_sum;
        } else if (current_sum < 0) {
            current_sum = 0;
        }
    }
    return max_sum;
}

template <typename T>
int max_wrap_sum(vector<T> v) {
    int total_sum = accumulate(v.begin(), v.end(), 0);
    int len = v.size();
    int starting_idx = 0, min_sum = 0, current_sum = 0;
    for (int i = 0; i < len; i++) {
        current_sum += v[i];
        if (current_sum < min_sum) {
            min_sum = current_sum;
        } else if (current_sum > 0) {
            current_sum = 0;
        }
    }
    return total_sum - min_sum;
}


int main() {
    // vector<int> v {34, -50, 42, 14, -5, 86};
    // vector<int> v {34, -58, 42, 14, -60, 86};
    // vector<int> v {-34, -50, -42, -14, -5};
    // vector<int> v {8, -1, 3, 4};
    vector<int> v {8, 1, 3, 4, 2};
    // cout << max_sub_sum(v) << endl;
    cout << max_wrap_sum(v) << endl;
}