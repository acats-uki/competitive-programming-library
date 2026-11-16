#include <bits/stdc++.h>
using namespace std;

struct Hungarian {
   static constexpr long long INF = 4e18;

   int numLeft;
   int numRight;
   vector<vector<long long>> costMatrix;
   vector<int> matchLeft;
   vector<int> matchRight;

   Hungarian(int leftSize = 0, int rightSize = 0) {
      init(leftSize, rightSize);
   }

   void init(int leftSize, int rightSize) {
      numLeft = leftSize;
      numRight = rightSize;
      costMatrix.assign(numLeft + 1, vector<long long>(numRight + 1, INF));
      matchLeft.assign(numLeft + 1, 0);
      matchRight.assign(numRight + 1, 0);
   }

   void setCost(int leftIdx, int rightIdx, long long cost) {
      costMatrix[leftIdx][rightIdx] = cost;
   }

   pair<long long, vector<int>> solveInternal(int n, int m, const vector<vector<long long>>& cost) {
      vector<long long> potentialLeft(n + 1, 0);
      vector<long long> potentialRight(m + 1, 0);
      vector<int> matchedRow(m + 1, 0);
      vector<int> prevCol(m + 1, 0);

      for (int i = 1; i <= n; ++i) {
         matchedRow[0] = i;
         int freeCol = 0;
         vector<long long> minSlack(m + 1, INF);
         vector<bool> usedCol(m + 1, false);

         do {
            usedCol[freeCol] = true;
            int currRow = matchedRow[freeCol];
            long long delta = INF;
            int nextCol = 0;

            for (int j = 1; j <= m; ++j) {
               if (!usedCol[j]) {
                  long long reducedCost = cost[currRow][j] - potentialLeft[currRow] - potentialRight[j];
                  if (reducedCost < minSlack[j]) {
                     minSlack[j] = reducedCost;
                     prevCol[j] = freeCol;
                  }
                  if (minSlack[j] < delta) {
                     delta = minSlack[j];
                     nextCol = j;
                  }
               }
            }

            if (nextCol == 0) {
               return {INF, vector<int>(m + 1, 0)};
            }

            for (int j = 0; j <= m; ++j) {
               if (usedCol[j]) {
                  potentialLeft[matchedRow[j]] += delta;
                  potentialRight[j] -= delta;
               } else {
                  minSlack[j] -= delta;
               }
            }

            freeCol = nextCol;
         } while (matchedRow[freeCol] != 0);

         do {
            int backCol = prevCol[freeCol];
            matchedRow[freeCol] = matchedRow[backCol];
            freeCol = backCol;
         } while (freeCol != 0);
      }

      return {-potentialRight[0], matchedRow};
   }

   long long solve() {
      matchLeft.assign(numLeft + 1, 0);
      matchRight.assign(numRight + 1, 0);
      if (numLeft == 0 || numRight == 0) {
         return 0;
      }

      if (numLeft <= numRight) {
         auto [minCost, matchedRow] = solveInternal(numLeft, numRight, costMatrix);
         if (minCost >= INF) {
            return INF;
         }
         matchRight = matchedRow;
         for (int j = 1; j <= numRight; ++j) {
            if (matchRight[j] != 0) {
               matchLeft[matchRight[j]] = j;
            }
         }
         return minCost;
      } else {
         vector<vector<long long>> transposed(numRight + 1, vector<long long>(numLeft + 1));
         for (int i = 1; i <= numLeft; ++i) {
            for (int j = 1; j <= numRight; ++j) {
               transposed[j][i] = costMatrix[i][j];
            }
         }
         auto [minCost, matchedCol] = solveInternal(numRight, numLeft, transposed);
         if (minCost >= INF) {
            return INF;
         }
         matchLeft = matchedCol;
         for (int i = 1; i <= numLeft; ++i) {
            if (matchLeft[i] != 0) {
               matchRight[matchLeft[i]] = i;
            }
         }
         return minCost;
      }
   }
};