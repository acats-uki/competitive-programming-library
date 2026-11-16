#include <bits/stdc++.h>
using namespace std;

struct Matrix {
   int numRows;
   int numCols;
   long long mod;
   vector<vector<long long>> mat;

   Matrix(int r = 0, int c = 0, long long m = 1000000007LL) {
      init(r, c, m);
   }

   void init(int r, int c, long long m = 1000000007LL) {
      numRows = r;
      numCols = c;
      mod = m;
      mat.assign(r, vector<long long>(c, 0));
   }

   vector<long long>& operator[](int row) {
      return mat[row];
   }

   const vector<long long>& operator[](int row) const {
      return mat[row];
   }

   static Matrix identity(int n, long long m = 1000000007LL) {
      Matrix res(n, n, m);
      for (int i = 0; i < n; ++i) {
         res[i][i] = 1 % m;
      }
      return res;
   }

   Matrix operator+(const Matrix& other) const {
      Matrix res(numRows, numCols, mod);
      for (int i = 0; i < numRows; ++i) {
         for (int j = 0; j < numCols; ++j) {
            long long sum = mat[i][j] + other[i][j];
            if (sum >= mod) sum -= mod;
            res[i][j] = sum;
         }
      }
      return res;
   }

   Matrix operator-(const Matrix& other) const {
      Matrix res(numRows, numCols, mod);
      for (int i = 0; i < numRows; ++i) {
         for (int j = 0; j < numCols; ++j) {
            long long diff = mat[i][j] - other[i][j];
            if (diff < 0) diff += mod;
            res[i][j] = diff;
         }
      }
      return res;
   }

   Matrix operator*(const Matrix& other) const {
      Matrix res(numRows, other.numCols, mod);
      for (int i = 0; i < numRows; ++i) {
         for (int k = 0; k < numCols; ++k) {
            if (mat[i][k] == 0) continue;
            long long pivot = mat[i][k];
            for (int j = 0; j < other.numCols; ++j) {
               res[i][j] = (res[i][j] + (__int128)pivot * other[k][j]) % mod;
            }
         }
      }
      return res;
   }

   Matrix power(long long exp) const {
      Matrix res = identity(numRows, mod);
      Matrix base = *this;
      while (exp > 0) {
         if (exp & 1) {
            res = res * base;
         }
         base = base * base;
         exp >>= 1;
      }
      return res;
   }
};