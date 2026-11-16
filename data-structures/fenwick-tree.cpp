#include <bits/stdc++.h>
using namespace std;

struct FenwickRange {
   int numElements;
   vector<long long> bitSlope;      
   vector<long long> bitIntercept; 

   FenwickRange(int n = 0) {
      init(n);
   }

   void init(int n) {
      numElements = n;
      bitSlope.assign(n + 1, 0);
      bitIntercept.assign(n + 1, 0);
   }

   void build(const vector<long long>& initialValues) {
      init((int)initialValues.size() - 1);
      for (int idx = 1; idx <= numElements; ++idx) {
         long long diff = initialValues[idx] - initialValues[idx - 1];
         bitSlope[idx] += diff;
         bitIntercept[idx] += diff * (idx - 1);

         int parentIdx = idx + (idx & -idx);
         if (parentIdx <= numElements) {
            bitSlope[parentIdx] += bitSlope[idx];
            bitIntercept[parentIdx] += bitIntercept[idx];
         }
      }
   }

   void addPoint(vector<long long>& tree, int index, long long delta) {
      for (; index <= numElements; index += index & -index) {
         tree[index] += delta;
      }
   }

   long long queryPoint(const vector<long long>& tree, int index) const {
      long long total = 0;
      for (; index > 0; index -= index & -index) {
         total += tree[index];
      }
      return total;
   }

   // add [left, right]
   void rangeAdd(int left, int right, long long delta) {
      if (left > right) return;
      addPoint(bitSlope, left, delta);
      addPoint(bitSlope, right + 1, -delta);

      addPoint(bitIntercept, left, delta * (left - 1));
      addPoint(bitIntercept, right + 1, -delta * right);
   }

   // sum : [1, index]
   long long prefixSum(int index) const {
      if (index <= 0) return 0;
      return index * queryPoint(bitSlope, index) - queryPoint(bitIntercept, index);
   }

   // sum : [left, right]
   long long rangeSum(int left, int right) const {
      if (left > right) return 0;
      return prefixSum(right) - prefixSum(left - 1);
   }
};