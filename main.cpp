#include <iostream>
#include <vector>

using namespace std;


vector<int> function(int n, int W, int l, vector<int> weight, vector<int> value) {
    //defining opt(i,w,k) based on recursive equation
    //
    vector<vector<vector<int>>> OPT(n + 1, vector<vector<int>>(W + 1, vector<int>(l + 1, 0)));
    for (int i = 0; i < n; i++) {
        for (int w = 1; w <= W; w++) {
            for (int k = 1; k <= 1; k++) {
                //if wi is > w
                if (weight[i] > w) {
                    OPT[i+1][w][k] = OPT[i][w][k];
                }
                //otherwise
                else {
                    OPT[i + 1][w][k] = max(OPT[i][w][k], value[i] + OPT[i][w - weight[i]][k - 1]);
                }
            }
        }
    }
}

int main() {
    vector<int> testWeight = { 3, 4, 21, 4, 6, 7, 8 };
    vector<int> testValue = { 1, 1, 3, 5, 10, 8, 8 };
    vector<int> result = function(7, 9, 2, testWeight, testValue);
    //Should be {3, 6} <-- Max weight of 9, with a max value of 11
    return 0;
}
