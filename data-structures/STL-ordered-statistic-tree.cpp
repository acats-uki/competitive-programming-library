#include <bits/stdc++.h>
#include <ext/pbds/assoc_container.hpp>
#include <ext/pbds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T, typename Compare = less<T>>
using OrderedSet = tree<
   T,
   null_type,
   Compare,
   rb_tree_tag,
   tree_order_statistics_node_update
>;

template <typename T>
struct OrderedMultiset {
   OrderedSet<pair<T, int>> elements;
   int nextId = 0;

   void insert(const T& value) {
      elements.insert({value, nextId++});
   }

   bool eraseOne(const T& value) {
      auto it = elements.lower_bound({value, 0});
      if (it != elements.end() && it->first == value) {
         elements.erase(it);
         return true;
      }
      return false;
   }

   int countLess(const T& value) const {
      return (int)elements.order_of_key({value, 0});
   }

   T kthElement(int k) const {
      return elements.find_by_order(k)->first;
   }

   int size() const {
      return (int)elements.size();
   }
};