#include <bits/stdc++.h>
using namespace std;

struct CutVertexFinder {
   int numVertices;
   int timer;
   vector<vector<int>> adj;
   vector<int> tin;
   vector<int> low;
   vector<bool> isCutVertex;
   vector<int> cutVertices;

   CutVertexFinder(int n = 0) {
      init(n);
   }

   void init(int n) {
      numVertices = n;
      timer = 0;
      adj.assign(n + 1, {});
      tin.assign(n + 1, 0);
      low.assign(n + 1, 0);
      isCutVertex.assign(n + 1, false);
      cutVertices.clear();
   }

   void addEdge(int u, int v) {
      adj[u].push_back(v);
      adj[v].push_back(u);
   }

   void dfs(int u, int parentVertex) {
      tin[u] = low[u] = ++timer;
      int treeChildren = 0;

      for (int v : adj[u]) {
         if (v == parentVertex) {
            continue;
         }
         if (tin[v] != 0) {
            low[u] = min(low[u], tin[v]);
         } else {
            ++treeChildren;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (parentVertex != -1 && low[v] >= tin[u]) {
               isCutVertex[u] = true;
            }
         }
      }

      if (parentVertex == -1 && treeChildren > 1) {
         isCutVertex[u] = true;
      }
   }

   void run() {
      timer = 0;
      tin.assign(numVertices + 1, 0);
      low.assign(numVertices + 1, 0);
      isCutVertex.assign(numVertices + 1, false);
      cutVertices.clear();

      for (int i = 1; i <= numVertices; ++i) {
         if (tin[i] == 0) {
            dfs(i, -1);
         }
      }

      for (int i = 1; i <= numVertices; ++i) {
         if (isCutVertex[i]) {
            cutVertices.push_back(i);
         }
      }
   }
};