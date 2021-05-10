/**
 * Generate report for an integration test.
 *
 * Copyright (c) 2021, <your name>.
 */

#include <algorithm>
#include <tuple>
#include <vector>
#include <cstdio>
#include "data/data.h"
#include "match/match.h"

// Refers to what you implement in match
double score(const Profile &, const Profile &);

int main() {
  // Tuple is like an ad-hoc struct, holding disparate entities
  // Convenient when returning multiple values from function
  typedef std::tuple<uint32_t, uint32_t, double> Entry;

  // Vector is a contiguous list of entities
  // Just like array, but of variable length
  std::vector<Profile> up = profiles(100);

  // Easiest is to return indeces rather than IDs
  std::vector<Entry> ut;
  for (auto p : Match::pairs(up)) {
    ut.push_back({
      up[p.first].id, up[p.second].id, score(up[p.first], up[p.second])
    });
  }

  // Sort by male ID
  std::sort(ut.begin(), ut.end(), [](Entry a, Entry b)
  {
    return std::get<0>(a) < std::get<0>(b);
  });

  // Print results
  for(auto p : ut)
  {
    printf("%-10d%-10d%-.1lf\n", 
      std::get<0>(p), std::get<1>(p), std::get<2>(p));
  }
}
