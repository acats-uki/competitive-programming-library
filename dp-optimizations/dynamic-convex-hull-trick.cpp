#include <bits/stdc++.h>
using namespace std;

struct LineContainer {
   static constexpr long long INF = LLONG_MAX;

   struct Line {
      mutable long long slope;
      mutable long long intercept;
      mutable long long rightReach;

      bool operator<(const Line& other) const {
         return slope < other.slope;
      }

      bool operator<(long long queryX) const {
         return rightReach < queryX;
      }
   };

   multiset<Line, less<>> maxHull;
   multiset<Line, less<>> minHull;

   void clear() {
      maxHull.clear();
      minHull.clear();
   }

   bool empty() const {
      return maxHull.empty();
   }

   long long floorDiv(long long numerator, long long denominator) const {
      return numerator / denominator - ((numerator ^ denominator) < 0 && numerator % denominator != 0);
   }

   bool updateReach(multiset<Line, less<>>& hull, multiset<Line, less<>>::iterator currIt, multiset<Line, less<>>::iterator nextIt) {
      if (nextIt == hull.end()) {
         currIt->rightReach = INF;
         return false;
      }
      if (currIt->slope == nextIt->slope) {
         currIt->rightReach = (currIt->intercept > nextIt->intercept) ? INF : -INF;
      } else {
         currIt->rightReach = floorDiv(nextIt->intercept - currIt->intercept, currIt->slope - nextIt->slope);
      }
      return currIt->rightReach >= nextIt->rightReach;
   }

   void insertIntoHull(multiset<Line, less<>>& hull, long long slope, long long intercept) {
      auto nextIt = hull.insert({slope, intercept, 0});
      auto currIt = nextIt++;
      auto prevIt = currIt;

      while (updateReach(hull, currIt, nextIt)) {
         nextIt = hull.erase(nextIt);
      }
      if (prevIt != hull.begin() && updateReach(hull, --prevIt, currIt)) {
         updateReach(hull, prevIt, currIt = hull.erase(currIt));
      }
      while ((currIt = prevIt) != hull.begin() && (--prevIt)->rightReach >= currIt->rightReach) {
         updateReach(hull, prevIt, hull.erase(currIt));
      }
   }

   void addLine(long long slope, long long intercept) {
      insertIntoHull(maxHull, slope, intercept);
      insertIntoHull(minHull, -slope, -intercept);
   }

   long long queryMax(long long x) const {
      auto bestLine = *maxHull.lower_bound(x);
      return bestLine.slope * x + bestLine.intercept;
   }

   long long queryMin(long long x) const {
      auto bestLine = *minHull.lower_bound(x);
      return -(bestLine.slope * x + bestLine.intercept);
   }
};