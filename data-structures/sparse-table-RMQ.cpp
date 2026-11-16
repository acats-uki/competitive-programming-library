#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
   int numElements;
   int maxLog;
   vector<vector<long long>> table;
   vector<int> log2Floor;

   SparseTable() : numElements(0), maxLog(0) {}

   SparseTable(const vector<long long>& initialValues) {
      build(initialValues);
   }

   long long merge(long long leftVal, long long rightVal) const {
      return min(leftVal, rightVal);
   }

   void build(const vector<long long>& initialValues) {
      numElements = (int)initialValues.size() - 1;
      if (numElements <= 0) return;

      log2Floor.assign(numElements + 1, 0);
      for (int i = 2; i <= numElements; ++i) {
         log2Floor[i] = log2Floor[i >> 1] + 1;
      }

      maxLog = log2Floor[numElements];
      table.assign(maxLog + 1, vector<long long>(numElements + 1));

      for (int i = 1; i <= numElements; ++i) {
         table[0][i] = initialValues[i];
      }

      for (int k = 1; k <= maxLog; ++k) {
         int halfStep = 1 << (k - 1);
         int maxStart = numElements - (1 << k) + 1;
         for (int i = 1; i <= maxStart; ++i) {
            table[k][i] = merge(table[k - 1][i], table[k - 1][i + halfStep]);
         }
      }
   }

   long long query(int leftBound, int rightBound) const {
      int k = log2Floor[rightBound - leftBound + 1];
      return merge(table[k][leftBound], table[k][rightBound - (1 << k) + 1]);
   }
};