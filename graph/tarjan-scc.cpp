#include <bits/stdc++.h>
using namespace std;

struct TarjanSCC {
   int numVertices;
   int timer;
   int numComponents;
   vector<vector<int>> adj;
   vector<int> tin;
   vector<int> low;
   vector<int> compId;
   vector<vector<int>> components;
   vector<int> nodeStack;
   vector<bool> inStack;

   TarjanSCC(int n = 0) {
      init(n);
   }

   void init(int n) {
      numVertices = n;
      timer = 0;
      numComponents = 0;
      adj.assign(n + 1, {});
      tin.assign(n + 1, 0);
      low.assign(n + 1, 0);
      compId.assign(n + 1, 0);
      components.assign(1, {});
      nodeStack.clear();
      inStack.assign(n + 1, false);
   }

   void addEdge(int from, int to) {
      adj[from].push_back(to);
   }

   void dfs(int u) {
      tin[u] = low[u] = ++timer;
      nodeStack.push_back(u);
      inStack[u] = true;

      for (int v : adj[u]) {
         if (tin[v] == 0) {
            dfs(v);
            low[u] = min(low[u], low[v]);
         } else if (inStack[v]) {
            low[u] = min(low[u], tin[v]);
         }
      }

      if (low[u] == tin[u]) {
         ++numComponents;
         components.emplace_back();
         while (true) {
            int curr = nodeStack.back();
            nodeStack.pop_back();
            inStack[curr] = false;
            compId[curr] = numComponents;
            components[numComponents].push_back(curr);
            if (curr == u) {
               break;
            }
         }
      }
   }

   void run() {
      timer = 0;
      numComponents = 0;
      tin.assign(numVertices + 1, 0);
      low.assign(numVertices + 1, 0);
      compId.assign(numVertices + 1, 0);
      components.assign(1, {});
      nodeStack.clear();
      inStack.assign(numVertices + 1, false);

      for (int i = 1; i <= numVertices; ++i) {
         if (tin[i] == 0) {
            dfs(i);
         }
      }
   }

   vector<vector<int>> buildCondensedGraph() const {
      vector<vector<int>> dag(numComponents + 1);
      for (int u = 1; u <= numVertices; ++u) {
         for (int v : adj[u]) {
            if (compId[u] != compId[v]) {
               dag[compId[u]].push_back(compId[v]);
            }
         }
      }
      for (int c = 1; c <= numComponents; ++c) {
         sort(dag[c].begin(), dag[c].end());
         dag[c].erase(unique(dag[c].begin(), dag[c].end()), dag[c].end());
      }
      return dag;
   }
};