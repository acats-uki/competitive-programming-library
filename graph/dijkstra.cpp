#include <bits/stdc++.h>
using namespace std;

struct Dijkstra {
   static constexpr long long INF = 4e18;

   struct Edge {
      int to;
      long long weight;
   };

   int numVertices;
   vector<vector<Edge>> adj;
   vector<long long> minDist;
   vector<int> parent;

   Dijkstra(int n = 0) {
      init(n);
   }

   void init(int n) {
      numVertices = n;
      adj.assign(n + 1, {});
      minDist.assign(n + 1, INF);
      parent.assign(n + 1, -1);
   }

   void addDirectedEdge(int from, int to, long long weight) {
      adj[from].push_back({to, weight});
   }

   void addUndirectedEdge(int u, int v, long long weight) {
      adj[u].push_back({v, weight});
      adj[v].push_back({u, weight});
   }

   void run(const vector<int>& sources) {
      minDist.assign(numVertices + 1, INF);
      parent.assign(numVertices + 1, -1);

      using State = pair<long long, int>;
      priority_queue<State, vector<State>, greater<State>> pq;

      for (int src : sources) {
         minDist[src] = 0;
         pq.push({0, src});
      }

      while (!pq.empty()) {
         auto [currDist, u] = pq.top();
         pq.pop();

         if (currDist > minDist[u]) {
            continue;
         }

         for (const auto& edge : adj[u]) {
            long long nextDist = currDist + edge.weight;
            if (nextDist < minDist[edge.to]) {
               minDist[edge.to] = nextDist;
               parent[edge.to] = u;
               pq.push({nextDist, edge.to});
            }
         }
      }
   }

   void run(int startNode) {
      run(vector<int>{startNode});
   }

   vector<int> getPath(int targetNode) const {
      if (targetNode < 1 || targetNode > numVertices || minDist[targetNode] == INF) {
         return {};
      }
      vector<int> path;
      for (int curr = targetNode; curr != -1; curr = parent[curr]) {
         path.push_back(curr);
      }
      reverse(path.begin(), path.end());
      return path;
   }
};