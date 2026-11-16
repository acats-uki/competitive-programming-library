#include <bits/stdc++.h>
#include <ext/pbds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

struct CustomHash {
   static uint64_t splitmix64(uint64_t x) {
      x += 0x9e3779b97f4a7c15ULL;
      x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
      x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
      return x ^ (x >> 31);
   }

   size_t operator()(uint64_t x) const {
      static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
      return splitmix64(x + FIXED_RANDOM);
   }

   template <typename T1, typename T2>
   size_t operator()(const pair<T1, T2>& p) const {
      static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
      uint64_t firstHash = splitmix64(uint64_t(p.first) + FIXED_RANDOM);
      uint64_t secondHash = splitmix64(uint64_t(p.second) + FIXED_RANDOM);
      return splitmix64(firstHash ^ (secondHash >> 1));
   }
};

template <typename Key, typename Value>
using FastHashMap = gp_hash_table<Key, Value, CustomHash>;

template <typename Key>
using FastHashSet = gp_hash_table<Key, null_type, CustomHash>;

template <typename Key, typename Value>
using SafeUnorderedMap = unordered_map<Key, Value, CustomHash>;

template <typename Key>
using SafeUnorderedSet = unordered_set<Key, CustomHash>;