#include <bits/stdc++.h>
using namespace std;

struct Gauss {
   static constexpr double EPS = 1e-9;

   static int solve(vector<vector<double>> augMatrix, vector<double>& solution) {
      int numRows = (int)augMatrix.size();
      if (numRows == 0) {
         solution.clear();
         return 1;
      }
      int numCols = (int)augMatrix[0].size() - 1;
      vector<int> pivotRow(numCols, -1);

      int row = 0;
      for (int col = 0; col < numCols && row < numRows; ++col) {
         int bestRow = row;
         for (int i = row + 1; i < numRows; ++i) {
            if (abs(augMatrix[i][col]) > abs(augMatrix[bestRow][col])) {
               bestRow = i;
            }
         }
         if (abs(augMatrix[bestRow][col]) < EPS) {
            continue;
         }

         swap(augMatrix[bestRow], augMatrix[row]);
         pivotRow[col] = row;

         double pivotVal = augMatrix[row][col];
         for (int j = col; j <= numCols; ++j) {
            augMatrix[row][j] /= pivotVal;
         }

         for (int i = 0; i < numRows; ++i) {
            if (i != row && abs(augMatrix[i][col]) > EPS) {
               double factor = augMatrix[i][col];
               for (int j = col; j <= numCols; ++j) {
                  augMatrix[i][j] -= factor * augMatrix[row][j];
               }
            }
         }
         ++row;
      }

      solution.assign(numCols, 0.0);
      for (int col = 0; col < numCols; ++col) {
         if (pivotRow[col] != -1) {
            solution[col] = augMatrix[pivotRow[col]][numCols];
         }
      }

      for (int i = 0; i < numRows; ++i) {
         double lhs = 0.0;
         for (int j = 0; j < numCols; ++j) {
            lhs += solution[j] * augMatrix[i][j];
         }
         if (abs(lhs - augMatrix[i][numCols]) > EPS) {
            return 0;
         }
      }

      for (int col = 0; col < numCols; ++col) {
         if (pivotRow[col] == -1) {
            return 2;
         }
      }
      return 1;
   }
};