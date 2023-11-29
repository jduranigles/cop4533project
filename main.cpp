#include <iostream>
#include <vector>
#include <string>

using namespace std;


 void function(int n, int W, int l, vector<int> weight, vector<int> value) {
     //defining opt(i,w,k) based on recursive equation
     //
     vector<vector<vector<int>>> OPT(n + 1, vector<vector<int>>(W + 1, vector<int>(l + 1, 0)));
     for (int i = 0; i <= n; i++) {
         for (int w = 0; w <= W; w++) {
             for (int k = 0; k <= l; k++) {
                 if (i < k) {
                     //-1 indicates that there is no solution to OPT
                     OPT[i][w][k] = -1;
                 }
                 else if (w > 0 && k == 0) {
                     OPT[i][w][k] = -1;
                 }
                 else if (w == 0 && k > 0) {
                     OPT[i][w][k] = -1;
                 }
                 else if (k == 0 && w == 0) {
                     OPT[i][w][k] = 0; 
                 }
                 //if wi is > w
                 else if (weight[i] > w) {
                     //cout << "test" << endl;
                     OPT[i][w][k] = OPT[i - 1][w][k];
                 }
                 //otherwise
                 else {
                     //Currently having issues with overflow of i; calculating for OPT(7,x,x) calls from value[7], which is out of bounds
                     //cout << "i = " << i << endl << "w = " << w << endl << "k = " << k << endl;
                     //cout << weight[i] << endl;
                     OPT[i][w][k] = max(OPT[i - 1][w][k], value[i] + OPT[i - 1][w - weight[i]][k - 1]);
                 }
             }
         }
     }
     cout << "OPT(" + n << ", " << W << ", " << l << "): " << OPT[n][W][l] << endl;
 }

int main() {
     vector<int> testWeight = { 3, 4, 21, 4, 6, 7, 8 };
     vector<int> testValue = { 1, 1, 3, 5, 10, 8, 8 };
     function(7, 9, 2, testWeight, testValue);
     //Should be {3, 6} <-- Max weight of 9, with a max value of 11
     return 0;
}