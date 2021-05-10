/**
 * Match implementation.
 *
 * Copyright (c) 2021, <your name>
 */

#include <tuple>
#include <cstdio>
#include <algorithm>
#include <set>
#include "match/match.h"

// Some helpful macros, use them if you wish
#define G(pf, i) std::get<i>(pf)
#define S(p1, p2, f) (G(p1.f, 0) == G(p2.f, 0) ? G(p1.f, 1) + G(p2.f, 1) : 0)
#define A(s, i) (s.find(i) == s.end())

double score(const Profile &p1, const Profile &p2) {
  // Calculate score for the pair
  double score = 0.0; 
  if(p1.gender == !p2.gender)
  {
    score += S(p1, p2, country);
    score += S(p1, p2, diet);
    score += S(p1, p2, drinking);
    score += S(p1, p2, language);
    score += S(p1, p2, religion);
    score += S(p1, p2, smoking);
  }
  return score;
}

std::map<uint32_t, uint32_t> Match::pairs(std::vector<Profile> &profiles) {
  // Suggested data structures, replace if/as necessary
  typedef std::tuple<uint32_t, uint32_t, double> Pairing;
  std::vector<uint32_t> males, females;
  std::vector<Pairing> pairings;
  std::set<uint32_t> picked;
  std::vector<uint32_t> pickedIndices;
  std::map<uint32_t, uint32_t> pairs;

  // Break into separate lists of males and females
  for(int i = 0; i < profiles.size(); ++i)
  {
    (profiles[i].gender == MALE ? males : females).push_back(i);
  }
  // Generate list of all possible pairings
  for(auto male : males)
  {
    for (auto female : females)
    {
      pairings.push_back(Pairing{male, female, score(profiles[male], profiles[female])});
      //pairs[male] = female;
    }
  }

  // Sort pairings in descending order of score
  //std::sort(pairings.begin(), pairings.end(), sortByScore);
  std::sort(pairings.begin(), pairings.end(), [](Pairing a, Pairing b)
  {
    return std::get<2>(a) > std::get<2>(b);
  });

  // Pick starting at the top upto required number of pairs
  // Be sure not to pick the same member twice (hint: use std::set)
  for(auto i = 0; i < pairings.size() && (picked.size() < (profiles.size())/2); ++i)
  {
    auto res = picked.insert(std::get<0>(pairings[i]));
    if(res.second) //successful insertion
    {
      pairs[std::get<0>(pairings[i])] = std::get<1>(pairings[i]);
      //printf("%lf\n\n", std::get<2>(pairings[i]));
    }
  }

  // Return pair of male/female indexes into profiles
  return pairs;
}
