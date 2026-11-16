#include <bits/stdc++.h>
using namespace std;

struct Fenwick2D {
   int numRows;
   int numCols;
   vector<vector<long long>> tree;

   Fenwick2D(int r = 0, int c = 0) {
      init(r, c);
   }

   void init(int r, int c) {
      numRows = r;
      numCols = c;
      tree.assign(r + 1, vector<long long>(c + 1, 0));
   }

   void add(int row, int col, long long delta) {
      for (int r = row; r <= numRows; r += r & -r) {
         for (int c = col; c <= numCols; c += c & -c) {
            tree[r][c] += delta;
         }
      }
   }

   long long prefixSum(int row, int col) const {
      long long total = 0;
      for (int r = row; r > 0; r -= r & -r) {
         for (int c = col; c > 0; c -= c & -c) {
            total += tree[r][c];
         }
      }
      return total;
   }

   long long queryRect(int r1, int c1, int r2, int c2) const {
      if (r1 > r2 || c1 > c2) return 0;
      return prefixSum(r2, c2)
           - prefixSum(r1 - 1, c2)
           - prefixSum(r2, c1 - 1)
           + prefixSum(r1 - 1, c1 - 1);
   }
};