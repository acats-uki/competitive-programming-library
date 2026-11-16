#include <bits/stdc++.h>
using namespace std;

struct ConvexHullTrick {
   struct Line {
      long long slope;
      long long intercept;

      long long eval(long long x) const {
         return slope * x + intercept;
      }
   };

   vector<Line> hull;
   int queryPtr = 0;

   void clear() {
      hull.clear();
      queryPtr = 0;
   }

   bool isRedundant(const Line& prevLine, const Line& currLine, const Line& nextLine) const {
      __int128 leftCross = (__int128)(nextLine.intercept - currLine.intercept) * (prevLine.slope - currLine.slope);
      __int128 rightCross = (__int128)(currLine.intercept - prevLine.intercept) * (currLine.slope - nextLine.slope);
      return leftCross <= rightCross;
   }

   void addLine(long long slope, long long intercept) {
      Line newLine = {slope, intercept};
      while (!hull.empty() && hull.back().slope == newLine.slope) {
         if (hull.back().intercept <= newLine.intercept) {
            return;
         }
         hull.pop_back();
      }
      while ((int)hull.size() >= 2 && isRedundant(hull[hull.size() - 2], hull.back(), newLine)) {
         hull.pop_back();
      }
      hull.push_back(newLine);
      if (queryPtr >= (int)hull.size()) {
         queryPtr = (int)hull.size() - 1;
      }
   }

   long long query(long long x) const {
      int low = 0;
      int high = (int)hull.size() - 1;
      while (low < high) {
         int mid = (low + high) >> 1;
         if (hull[mid].eval(x) >= hull[mid + 1].eval(x)) {
            low = mid + 1;
         } else {
            high = mid;
         }
      }
      return hull[low].eval(x);
   }

   long long queryMonotonic(long long x) {
      if (queryPtr >= (int)hull.size()) {
         queryPtr = (int)hull.size() - 1;
      }
      while (queryPtr + 1 < (int)hull.size() && hull[queryPtr].eval(x) >= hull[queryPtr + 1].eval(x)) {
         ++queryPtr;
      }
      return hull[queryPtr].eval(x);
   }
};