#include <bits/stdc++.h>
using namespace std;

struct DSU {
   int numElements;
   int numComponents;
   vector<int> parent;
   vector<int> compSize;

   DSU(int n = 0) {
      init(n);
   }

   void init(int n) {
      numElements = n;
      numComponents = n;
      parent.resize(n + 1);
      compSize.assign(n + 1, 1);
      iota(parent.begin(), parent.end(), 0);
   }

   int findRoot(int node) {
      if (parent[node] == node) {
         return node;
      }
      return parent[node] = findRoot(parent[node]);
   }

   bool isSameSet(int nodeA, int nodeB) {
      return findRoot(nodeA) == findRoot(nodeB);
   }

   bool unite(int nodeA, int nodeB) {
      int rootA = findRoot(nodeA);
      int rootB = findRoot(nodeB);
      if (rootA == rootB) {
         return false;
      }
      if (compSize[rootA] < compSize[rootB]) {
         swap(rootA, rootB);
      }
      parent[rootB] = rootA;
      compSize[rootA] += compSize[rootB];
      --numComponents;
      return true;
   }

   int getComponentSize(int node) {
      return compSize[findRoot(node)];
   }
};