#include <bits/stdc++.h>
using namespace std;

struct BridgeFinder {
   struct Edge {
      int to;
      int id;
   };

   int numVertices;
   int edgeCount;
   int timer;
   vector<vector<Edge>> adj;
   vector<int> tin;
   vector<int> low;
   vector<int> bridgeIds;
   vector<pair<int, int>> bridges;

   BridgeFinder(int n = 0) {
      init(n);
   }

   void init(int n) {
      numVertices = n;
      edgeCount = 0;
      timer = 0;
      adj.assign(n + 1, {});
      tin.assign(n + 1, 0);
      low.assign(n + 1, 0);
      bridgeIds.clear();
      bridges.clear();
   }

   int addEdge(int u, int v, int id = -1) {
      if (id == -1) {
         id = ++edgeCount;
      }
      adj[u].push_back({v, id});
      adj[v].push_back({u, id});
      return id;
   }

   void dfs(int u, int parentEdgeId) {
      tin[u] = low[u] = ++timer;

      for (const auto& edge : adj[u]) {
         if (edge.id == parentEdgeId) {
            continue;
         }
         int v = edge.to;
         if (tin[v] != 0) {
            low[u] = min(low[u], tin[v]);
         } else {
            dfs(v, edge.id);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
               bridgeIds.push_back(edge.id);
               bridges.push_back({u, v});
            }
         }
      }
   }

   void run() {
      timer = 0;
      tin.assign(numVertices + 1, 0);
      low.assign(numVertices + 1, 0);
      bridgeIds.clear();
      bridges.clear();

      for (int i = 1; i <= numVertices; ++i) {
         if (tin[i] == 0) {
            dfs(i, -1);
         }
      }
   }
};