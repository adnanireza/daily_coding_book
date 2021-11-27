#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

template <typename T>
class SparceArray {
protected:
    unordered_map<int, T> arrayMap;
    int size;
public:
    SparceArray(const vector<T> &array) {
        for (int i = 0; i < array.size(); i++) {
            if (array[i]) arrayMap[i] = array[i];
        }
        size = array.size();
    }
    T operator[](int i) {
        if (i >= size) throw "Error: Array bouds check failed.";
        return arrayMap[i] ? arrayMap[i] : 0;
    }
    void set(int i, T val) {
        if (val) arrayMap[i] = val;
        else arrayMap.erase(i);
        if (i >= size) size = i + 1;
    }
};

int main() {
    // vector<int> v {4, 0, 0, 2, 9, 0, 7, 0, 0, 0, 0, 6, 1, 0, 0};
    vector<int> v {4, 0, 0};
    SparceArray<int> sa(v);

    // cout << sa[3] << endl;
    cout << sa[2] << endl;
    sa.set(7, 76);
    cout << sa[7] << endl;
    cout << sa[5] << endl;


    return 0;
}