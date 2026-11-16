#include <bits/stdc++.h>
using namespace std;

struct DirectedCycleFinder {
   int numVertices;
   vector<vector<int>> adj;
   vector<int> state;
   vector<int> parent;
   vector<int> cycle;

   DirectedCycleFinder(int n = 0) {
      init(n);
   }

   void init(int n) {
      numVertices = n;
      adj.assign(n + 1, {});
      state.assign(n + 1, 0);
      parent.assign(n + 1, -1);
      cycle.clear();
   }

   void addEdge(int from, int to) {
      adj[from].push_back(to);
   }

   bool dfs(int u) {
      state[u] = 1;
      for (int v : adj[u]) {
         if (state[v] == 1) {
            cycle.clear();
            for (int curr = u; curr != v; curr = parent[curr]) {
               cycle.push_back(curr);
            }
            cycle.push_back(v);
            reverse(cycle.begin(), cycle.end());
            cycle.push_back(v);
            return true;
         }
         if (state[v] == 0) {
            parent[v] = u;
            if (dfs(v)) {
               return true;
            }
         }
      }
      state[u] = 2;
      return false;
   }

   bool findCycle() {
      state.assign(numVertices + 1, 0);
      parent.assign(numVertices + 1, -1);
      cycle.clear();

      for (int i = 1; i <= numVertices; ++i) {
         if (state[i] == 0 && dfs(i)) {
            return true;
         }
      }
      return false;
   }
};