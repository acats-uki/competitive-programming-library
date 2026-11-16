#include <bits/stdc++.h>
using namespace std;

struct FloydWarshall {
   static constexpr long long INF = 4e18;

   int numVertices;
   vector<vector<long long>> dist;
   vector<vector<int>> nextNode;

   FloydWarshall(int n = 0) {
      init(n);
   }

   void init(int n) {
      numVertices = n;
      dist.assign(n + 1, vector<long long>(n + 1, INF));
      nextNode.assign(n + 1, vector<int>(n + 1, -1));
      for (int i = 1; i <= n; ++i) {
         dist[i][i] = 0;
         nextNode[i][i] = i;
      }
   }

   void addDirectedEdge(int from, int to, long long weight) {
      if (weight < dist[from][to]) {
         dist[from][to] = weight;
         nextNode[from][to] = to;
      }
   }

   void addUndirectedEdge(int u, int v, long long weight) {
      addDirectedEdge(u, v, weight);
      addDirectedEdge(v, u, weight);
   }

   void run() {
      for (int k = 1; k <= numVertices; ++k) {
         for (int i = 1; i <= numVertices; ++i) {
            if (dist[i][k] == INF) continue;
            for (int j = 1; j <= numVertices; ++j) {
               if (dist[k][j] == INF) continue;
               if (dist[i][k] + dist[k][j] < dist[i][j]) {
                  dist[i][j] = dist[i][k] + dist[k][j];
                  nextNode[i][j] = nextNode[i][k];
               }
            }
         }
      }
   }

   bool hasNegativeCycle() const {
      for (int i = 1; i <= numVertices; ++i) {
         if (dist[i][i] < 0) {
            return true;
         }
      }
      return false;
   }

   vector<int> getPath(int startNode, int targetNode) const {
      if (nextNode[startNode][targetNode] == -1) {
         return {};
      }
      vector<int> path = {startNode};
      int curr = startNode;
      while (curr != targetNode) {
         curr = nextNode[curr][targetNode];
         path.push_back(curr);
         if ((int)path.size() > numVertices) {
            return {};
         }
      }
      return path;
   }
};