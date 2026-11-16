#include <bits/stdc++.h>
using namespace std;

struct LiChaoTree {
   static constexpr long long INF = 4e18;

   struct Line {
      long long slope;
      long long intercept;

      long long eval(long long x) const {
         return slope * x + intercept;
      }
   };

   struct Node {
      int leftChild;
      int rightChild;
      Line line;
   };

   long long minCoord;
   long long maxCoord;
   int root;
   vector<Node> nodes;

   LiChaoTree(long long minX = -1000000000LL, long long maxX = 1000000000LL) {
      init(minX, maxX);
   }

   void init(long long minX, long long maxX) {
      minCoord = minX;
      maxCoord = maxX;
      root = 0;
      nodes.clear();
      nodes.push_back({0, 0, {0, INF}});
   }

   int createNode(Line line) {
      nodes.push_back({0, 0, line});
      return (int)nodes.size() - 1;
   }

   int addLine(int node, long long leftBound, long long rightBound, Line newLine) {
      if (node == 0) {
         return createNode(newLine);
      }
      long long mid = leftBound + ((rightBound - leftBound) >> 1);
      bool leftBetter = newLine.eval(leftBound) < nodes[node].line.eval(leftBound);
      bool midBetter = newLine.eval(mid) < nodes[node].line.eval(mid);

      if (midBetter) {
         swap(nodes[node].line, newLine);
      }
      if (leftBound == rightBound) {
         return node;
      }
      if (newLine.eval(leftBound) >= nodes[node].line.eval(leftBound) &&
          newLine.eval(rightBound) >= nodes[node].line.eval(rightBound)) {
         return node;
      }

      if (leftBetter != midBetter) {
         int updatedLeft = addLine(nodes[node].leftChild, leftBound, mid, newLine);
         nodes[node].leftChild = updatedLeft;
      } else {
         int updatedRight = addLine(nodes[node].rightChild, mid + 1, rightBound, newLine);
         nodes[node].rightChild = updatedRight;
      }
      return node;
   }

   void addLine(long long slope, long long intercept) {
      root = addLine(root, minCoord, maxCoord, {slope, intercept});
   }

   int addSegment(int node, long long leftBound, long long rightBound, long long segLeft, long long segRight, Line newLine) {
      if (segRight < leftBound || rightBound < segLeft) {
         return node;
      }
      if (segLeft <= leftBound && rightBound <= segRight) {
         return addLine(node, leftBound, rightBound, newLine);
      }
      if (node == 0) {
         node = createNode({0, INF});
      }
      long long mid = leftBound + ((rightBound - leftBound) >> 1);
      int updatedLeft = addSegment(nodes[node].leftChild, leftBound, mid, segLeft, segRight, newLine);
      int updatedRight = addSegment(nodes[node].rightChild, mid + 1, rightBound, segLeft, segRight, newLine);
      nodes[node].leftChild = updatedLeft;
      nodes[node].rightChild = updatedRight;
      return node;
   }

   void addSegment(long long segLeft, long long segRight, long long slope, long long intercept) {
      if (segLeft > segRight) return;
      root = addSegment(root, minCoord, maxCoord, segLeft, segRight, {slope, intercept});
   }

   long long query(int node, long long leftBound, long long rightBound, long long x) const {
      if (node == 0) {
         return INF;
      }
      long long bestVal = nodes[node].line.eval(x);
      if (leftBound == rightBound) {
         return bestVal;
      }
      long long mid = leftBound + ((rightBound - leftBound) >> 1);
      if (x <= mid) {
         return min(bestVal, query(nodes[node].leftChild, leftBound, mid, x));
      }
      return min(bestVal, query(nodes[node].rightChild, mid + 1, rightBound, x));
   }

   long long query(long long x) const {
      if (x < minCoord || x > maxCoord) return INF;
      return query(root, minCoord, maxCoord, x);
   }
};