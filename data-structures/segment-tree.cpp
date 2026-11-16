#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
   int numElements;
   long long neutralValue;
   vector<long long> tree;

   SegmentTree(int n = 0, long long neutral = 0) {
      init(n, neutral);
   }

   void init(int n, long long neutral = 0) {
      numElements = n;
      neutralValue = neutral;
      tree.assign(4 * n + 5, neutralValue);
   }

   long long merge(long long leftVal, long long rightVal) const {
      return leftVal + rightVal;
   }

   void build(const vector<long long>& initialValues, int node, int leftBound, int rightBound) {
      if (leftBound == rightBound) {
         tree[node] = initialValues[leftBound];
         return;
      }
      int mid = (leftBound + rightBound) >> 1;
      build(initialValues, node << 1, leftBound, mid);
      build(initialValues, node << 1 | 1, mid + 1, rightBound);
      tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
   }

   void build(const vector<long long>& initialValues) {
      init((int)initialValues.size() - 1, neutralValue);
      if (numElements > 0) {
         build(initialValues, 1, 1, numElements);
      }
   }

   void update(int node, int leftBound, int rightBound, int targetIndex, long long newValue) {
      if (leftBound == rightBound) {
         tree[node] = newValue;
         return;
      }
      int mid = (leftBound + rightBound) >> 1;
      if (targetIndex <= mid) {
         update(node << 1, leftBound, mid, targetIndex, newValue);
      } else {
         update(node << 1 | 1, mid + 1, rightBound, targetIndex, newValue);
      }
      tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
   }

   void update(int targetIndex, long long newValue) {
      update(1, 1, numElements, targetIndex, newValue);
   }

   long long query(int node, int leftBound, int rightBound, int queryLeft, int queryRight) const {
      if (queryRight < leftBound || rightBound < queryLeft) {
         return neutralValue;
      }
      if (queryLeft <= leftBound && rightBound <= queryRight) {
         return tree[node];
      }
      int mid = (leftBound + rightBound) >> 1;
      long long leftResult = query(node << 1, leftBound, mid, queryLeft, queryRight);
      long long rightResult = query(node << 1 | 1, mid + 1, rightBound, queryLeft, queryRight);
      return merge(leftResult, rightResult);
   }

   long long query(int queryLeft, int queryRight) const {
      if (queryLeft > queryRight) return neutralValue;
      return query(1, 1, numElements, queryLeft, queryRight);
   }
};