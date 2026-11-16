#include <bits/stdc++.h>
using namespace std;

struct SegmentTreeLazy {
   int numElements;
   long long neutralValue;
   vector<long long> tree;
   vector<long long> lazy;

   SegmentTreeLazy(int n = 0, long long neutral = 0) {
      init(n, neutral);
   }

   void init(int n, long long neutral = 0) {
      numElements = n;
      neutralValue = neutral;
      tree.assign(4 * n + 5, neutralValue);
      lazy.assign(4 * n + 5, 0);
   }

   long long merge(long long leftVal, long long rightVal) const {
      return leftVal + rightVal;
   }

   void apply(int node, int leftBound, int rightBound, long long delta) {
      tree[node] += delta * (rightBound - leftBound + 1);
      lazy[node] += delta;
   }

   void pushDown(int node, int leftBound, int rightBound) {
      if (lazy[node] == 0) return;
      int mid = (leftBound + rightBound) >> 1;
      apply(node << 1, leftBound, mid, lazy[node]);
      apply(node << 1 | 1, mid + 1, rightBound, lazy[node]);
      lazy[node] = 0;
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

   void update(int node, int leftBound, int rightBound, int updateLeft, int updateRight, long long delta) {
      if (updateRight < leftBound || rightBound < updateLeft) {
         return;
      }
      if (updateLeft <= leftBound && rightBound <= updateRight) {
         apply(node, leftBound, rightBound, delta);
         return;
      }
      pushDown(node, leftBound, rightBound);
      int mid = (leftBound + rightBound) >> 1;
      update(node << 1, leftBound, mid, updateLeft, updateRight, delta);
      update(node << 1 | 1, mid + 1, rightBound, updateLeft, updateRight, delta);
      tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
   }

   void update(int updateLeft, int updateRight, long long delta) {
      if (updateLeft > updateRight) return;
      update(1, 1, numElements, updateLeft, updateRight, delta);
   }

   long long query(int node, int leftBound, int rightBound, int queryLeft, int queryRight) {
      if (queryRight < leftBound || rightBound < queryLeft) {
         return neutralValue;
      }
      if (queryLeft <= leftBound && rightBound <= queryRight) {
         return tree[node];
      }
      pushDown(node, leftBound, rightBound);
      int mid = (leftBound + rightBound) >> 1;
      long long leftResult = query(node << 1, leftBound, mid, queryLeft, queryRight);
      long long rightResult = query(node << 1 | 1, mid + 1, rightBound, queryLeft, queryRight);
      return merge(leftResult, rightResult);
   }

   long long query(int queryLeft, int queryRight) {
      if (queryLeft > queryRight) return neutralValue;
      return query(1, 1, numElements, queryLeft, queryRight);
   }
};