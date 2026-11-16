#include <bits/stdc++.h>
using namespace std;

struct UndirectedCycleFinder {
   struct Edge {
      int to;
      int id;
   };

   int numVertices;
   int edgeCount;
   vector<vector<Edge>> adj;
   vector<bool> visited;
   vector<int> parent;
   vector<int> cycle;

   UndirectedCycleFinder(int n = 0) {
      init(n);
   }

   void init(int n) {
      numVertices = n;
      edgeCount = 0;
      adj.assign(n + 1, {});
      visited.assign(n + 1, false);
      parent.assign(n + 1, -1);
      cycle.clear();
   }

   int addEdge(int u, int v, int id = -1) {
      if (id == -1) {
         id = ++edgeCount;
      }
      adj[u].push_back({v, id});
      adj[v].push_back({u, id});
      return id;
   }

   bool dfs(int u, int parentEdgeId) {
      visited[u] = true;
      for (const auto& edge : adj[u]) {
         if (edge.id == parentEdgeId) {
            continue;
         }
         int v = edge.to;
         if (visited[v]) {
            cycle.clear();
            for (int curr = u; curr != v; curr = parent[curr]) {
               cycle.push_back(curr);
            }
            cycle.push_back(v);
            reverse(cycle.begin(), cycle.end());
            cycle.push_back(v);
            return true;
         }
         parent[v] = u;
         if (dfs(v, edge.id)) {
            return true;
         }
      }
      return false;
   }

   bool findCycle() {
      visited.assign(numVertices + 1, false);
      parent.assign(numVertices + 1, -1);
      cycle.clear();

      for (int i = 1; i <= numVertices; ++i) {
         if (!visited[i] && dfs(i, -1)) {
            return true;
         }
      }
      return false;
   }
};