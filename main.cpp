#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

void traceback(vector<vector<vector<int>>> vec, vector<int> weight, int i, int w, int k) {

    vector<int> solution;
    //vector of ints in which we will record the i of each item in the optimal subset

    while (k > 0)
        //loop continues until we pull k items which means the subset is complete
    {

        if (vec[i][w][k] > vec[i - 1][w][k])
            //work backwards from OPT[i][w][k] to find which i causes a change in OPT, 
            //meaning that i is part of the solution subset
        {
            w -= weight[i - 1];
            k--;
            solution.push_back(i);
            //we add this i to our solution subset and subtract the weight, also decrement k so the loop can terminate
        }
        i--;
    }

    cout << "Items present in solution (1-based): ";

    //prints out the solution subset, "{i value of each item in the subset}"
    cout << "{";
    for (int i = solution.size() - 1; i >= 0; i--)
    {
        cout << solution[i];
        if (i != 0) cout << " ";
    }
    cout << "}";

}

void function(int n, int W, int l, vector<int> weight, vector<int> value) {
    //defining opt(i,w,k) based on recursive equation
    //
    //Vector dimensions must be 1 bigger to account for i, w, k = 0
    vector<vector<vector<int>>> OPT(n + 1, vector<vector<int>>(W + 1, vector<int>(l + 1, 0)));
    //Go through the matrix once to set INT_MIN and 0 values
    //Makes it easier to compute OPT later since the length of the matrix
    //and the length of the set are the same without 0 values
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            for (int k = 0; k <= l; k++) {
                if (i < k) {
                    //INT_MIN indicates there is no solution to the OPT
                    OPT[i][w][k] = INT_MIN;
                }
                else if (w > 0 && k == 0) {
                    OPT[i][w][k] = INT_MIN;
                }
                else if (w == 0 && k > 0) {
                    OPT[i][w][k] = INT_MIN;
                }
                else if (k == 0 && w == 0) {
                    OPT[i][w][k] = 0;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) { //Range 0 - 6; same as indices of set
        for (int w = 1; w <= W; w++) { //Range 1 - W
            for (int k = 1; k <= l; k++) { //Range 1 - L
                //if wi is > w
                if (weight[i] > w) {
                    //i + 1 is used such that i's range of 0-6 refers to 1-7; index 1 = item 1 
                    OPT[i + 1][w][k] = OPT[i][w][k];
                }
                //otherwise
                else {
                    //cout << "The OPT of " << i + 1 << " " << w << " " << k << " is the max of" << endl;
                    //cout << OPT[i][w][k] << " and " << value[i] + OPT[i][w - weight[i]][k - 1] << endl;
                    OPT[i + 1][w][k] = max(OPT[i][w][k], value[i] + OPT[i][w - weight[i]][k - 1]);
                }
            }
        }
    }
    cout << "OPT(" << n << ", " << W << ", " << l << "): " << OPT[n][W][l] << endl;

    //if opt returns a negative number then no solution, otherwise call traceback
    if (OPT[n][W][l] < 0)
    {
        cout << "No Solution";
    }
    else
    {
        traceback(OPT, weight, n, W, l);
    }
}

int main() {
    //Algorithm is tested just by hard coding the values and running
    //The values below can be changed
    vector<int> testWeight = { 1, 2, 2, 4, 2, 1, 3, 2 };
    vector<int> testValue = { 5, 4, 3, 6, 10, 3, 9, 3 };
    if (testWeight.size() != testValue.size()) {
        cout << "Size of weight array and value array do not match. Exiting" << endl;
        return 0;
    }
    cout << "Item List: " << endl;
    for (int i = 0; i < testWeight.size(); i++) {
        cout << "Item " << i + 1 << " Value = " << testValue.at(i) << "; Weight = " << testWeight.at(i) << endl;
    }
    function(8, 6, 3, testWeight, testValue);

    return 0;
}