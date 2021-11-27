#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int leastCut(const vector<vector<int>> &wall) {
    unordered_map<int, int> countMap;
    for (int i = 0; i < wall.size(); i++) {
        int sum = 0;
        for (int j = 0; j < wall[i].size() - 1; j++) {
            sum += wall[i][j];
            countMap[sum] = countMap[sum] ? countMap[sum] + 1 : 1;
        }
    }
    int max = 0;
    for (auto const &[key, val] : countMap) {
        max = val > max ? val : max;
    }
    return wall.size() - max;
}

int main() {
    vector<vector<int>> wall = {
        {3, 5, 1, 1},
        {2, 3, 3, 2},
        {5, 5},
        {4, 4, 2},
        {1, 3, 3, 3},
        {1, 1, 6, 1, 1},
    };
    cout << leastCut(wall) << endl;


    return 0;
}