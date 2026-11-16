#include <bits/stdc++.h>
using namespace std;

struct PersistentSegmentTree {
   struct Node {
      int leftChild;
      int rightChild;
      long long sum;
   };

   int numElements;
   vector<Node> nodes;
   vector<int> versionRoots;

   PersistentSegmentTree(int n = 0, int expectedUpdates = 0) {
      init(n, expectedUpdates);
   }

   void init(int n, int expectedUpdates = 0) {
      numElements = n;
      nodes.clear();
      nodes.reserve(4 * n + expectedUpdates * 22 + 5);
      nodes.push_back({0, 0, 0});
      versionRoots.assign(1, 0);
   }

   int createNode(int leftChild = 0, int rightChild = 0, long long sum = 0) {
      nodes.push_back({leftChild, rightChild, sum});
      return (int)nodes.size() - 1;
   }

   int build(const vector<long long>& initialValues, int leftBound, int rightBound) {
      int currNode = createNode();
      if (leftBound == rightBound) {
         nodes[currNode].sum = initialValues[leftBound];
         return currNode;
      }
      int mid = (leftBound + rightBound) >> 1;
      int leftRoot = build(initialValues, leftBound, mid);
      int rightRoot = build(initialValues, mid + 1, rightBound);
      nodes[currNode].leftChild = leftRoot;
      nodes[currNode].rightChild = rightRoot;
      nodes[currNode].sum = nodes[leftRoot].sum + nodes[rightRoot].sum;
      return currNode;
   }

   void build(const vector<long long>& initialValues) {
      init((int)initialValues.size() - 1);
      if (numElements > 0) {
         versionRoots[0] = build(initialValues, 1, numElements);
      }
   }

   int updateAdd(int prevNode, int leftBound, int rightBound, int targetIndex, long long delta) {
      int currNode = createNode(nodes[prevNode].leftChild, nodes[prevNode].rightChild, nodes[prevNode].sum);
      if (leftBound == rightBound) {
         nodes[currNode].sum += delta;
         return currNode;
      }
      int mid = (leftBound + rightBound) >> 1;
      if (targetIndex <= mid) {
         int updatedLeft = updateAdd(nodes[prevNode].leftChild, leftBound, mid, targetIndex, delta);
         nodes[currNode].leftChild = updatedLeft;
      } else {
         int updatedRight = updateAdd(nodes[prevNode].rightChild, mid + 1, rightBound, targetIndex, delta);
         nodes[currNode].rightChild = updatedRight;
      }
      nodes[currNode].sum = nodes[nodes[currNode].leftChild].sum + nodes[nodes[currNode].rightChild].sum;
      return currNode;
   }

   int add(int baseVersion, int targetIndex, long long delta) {
      int newRoot = updateAdd(versionRoots[baseVersion], 1, numElements, targetIndex, delta);
      versionRoots.push_back(newRoot);
      return (int)versionRoots.size() - 1;
   }

   long long query(int node, int leftBound, int rightBound, int queryLeft, int queryRight) const {
      if (node == 0 || queryRight < leftBound || rightBound < queryLeft) {
         return 0;
      }
      if (queryLeft <= leftBound && rightBound <= queryRight) {
         return nodes[node].sum;
      }
      int mid = (leftBound + rightBound) >> 1;
      return query(nodes[node].leftChild, leftBound, mid, queryLeft, queryRight)
           + query(nodes[node].rightChild, mid + 1, rightBound, queryLeft, queryRight);
   }

   long long query(int version, int queryLeft, int queryRight) const {
      if (queryLeft > queryRight) return 0;
      return query(versionRoots[version], 1, numElements, queryLeft, queryRight);
   }

   int findKth(int leftNode, int rightNode, int leftBound, int rightBound, long long k) const {
      if (leftBound == rightBound) {
         return leftBound;
      }
      int mid = (leftBound + rightBound) >> 1;
      long long leftCount = nodes[nodes[rightNode].leftChild].sum - nodes[nodes[leftNode].leftChild].sum;
      if (k <= leftCount) {
         return findKth(nodes[leftNode].leftChild, nodes[rightNode].leftChild, leftBound, mid, k);
      }
      return findKth(nodes[leftNode].rightChild, nodes[rightNode].rightChild, mid + 1, rightBound, k - leftCount);
   }

   int findKth(int leftVersion, int rightVersion, long long k) const {
      return findKth(versionRoots[leftVersion], versionRoots[rightVersion], 1, numElements, k);
   }
};