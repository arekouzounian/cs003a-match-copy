/**
 * Match implementation.
 *
 * Copyright (c) 2021, <your name>
 */

#include <tuple>
#include <algorithm>
#include <set>
#include "match/match.h"

// Some helpful macros, use them if you wish
#define G(pf, i) std::get<i>(pf)
#define S(p1, p2, f) (G(p1.f, 0) == G(p2.f, 0) ? G(p1.f, 1) + G(p2.f, 1) : 0)
#define A(s, i) (s.find(i) == s.end())

double score(const Profile &p1, const Profile &p2) {
  // Calculate score for the pair
  return 0;
}

std::map<uint32_t, uint32_t> Match::pairs(std::vector<Profile> &profiles) {
  // Suggested data structures, replace if/as necessary
  typedef std::tuple<uint32_t, uint32_t, double> Pairing;
  std::vector<uint32_t> males, females;
  std::vector<Pairing> pairings;
  std::set<uint32_t> picked;
  std::map<uint32_t, uint32_t> pairs;

  // Break into separate lists of males and females

  // Generate list of all possible pairings

  // Sor pairings in descending order of score

  // Pick starting at the top upto required number of pairs
  // Be sure not to pick the same member twice (hint: use std::set)

  // Return pair of male/female indexes into profiles
  return pairs;
}
