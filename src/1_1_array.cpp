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
vector<T> get_p(vector<T> v) {
    int len = v.size();
    vector<T> left(len, 1), right(len, 1), res(len);
    for (int i = 0; i < len; i++) {
        if (i == 0) {
            left[i] = v[i];
            right[len - 1 - i] = v[len - 1 - i];
            continue;
        }
        left[i] = left[i - 1] * v[i];
        right[len - 1 - i] = right[len - i] * v[len - 1 - i];
    }

    for (int i = 0; i < len; i++) {
        if (i == 0) {
            res[i] = right[i + 1];
            continue;
        } else if (i == len - 1) {
            res[i] = left[i - 1];
            continue;
        }
        res[i] = left[i - 1] * right[i + 1];
    }
    return res;
}

int main() {
    vector<int> v;
    vector<int> vp = get_p(v);
    disp(vp);
    cout << "HHHHHHHHHHHello" << endl;
}