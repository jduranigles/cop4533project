#include <iostream>
#include <vector>
#include <string>

using namespace std;


 void function(int n, int W, int l, vector<int> weight, vector<int> value) {
     //defining opt(i,w,k) based on recursive equation
     //
     //Vector dimensions must be 1 bigger to account for i, w, k = 0
     vector<vector<vector<int>>> OPT(n + 1, vector<vector<int>>(W + 1, vector<int>(l + 1, 0)));
     //Go through the array once to set INT_MIN and 0 values
     //Makes it easier to compute OPT later since the length of the array
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
             for (int k = 1; k <= l; k++) { //Range 1 - l
                 //if wi is > w
                 if (weight[i] > w) {
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
 }

int main() {
     vector<int> testWeight = { 3, 4, 21, 4, 6, 7, 8 };
     vector<int> testValue = { 1, 1, 3, 5, 10, 8, 8 };
     function(7, 9, 1, testWeight, testValue);
     //Should be {3, 6} <-- Max weight of 9, with a max value of 11
     return 0;
}