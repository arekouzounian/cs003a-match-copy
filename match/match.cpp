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
  double score = 0; 
  if(p1.gender == !p2.gender)
  {
    score += S(p1, p2, country);
    score += S(p1, p2, diet);
    score += S(p1, p2, drinking);
    score += S(p1, p2, language);
    score += S(p1, p2, religion);
    score += S(p1, p2, smoking);
  }
  return 0;
}

// I feel like this is pretty inefficient, but I am unsure how to optimize. 
// Perhaps use a hashmap so I'm not iterating through the data so many times?
std::tuple<Profile, Profile> getProfilePair(uint32_t maleId, uint32_t femaleId, const std::vector<Profile> &profiles)
{
  Profile male; 
  Profile female;
  for(auto profile : profiles)
  {
    if(profile.id == maleId) 
    {
      male = profile;
    }
    else if(profile.id == femaleId)
    {
      female = profile;
    }
  }
  return std::make_tuple(male, female);
}

bool sortByScore(const std::tuple<uint32_t, uint32_t, double> &p1, const std::tuple<uint32_t, uint32_t, double> &p2)
{
  return (G(p1, 2) > G(p1, 2));
}

std::map<uint32_t, uint32_t> Match::pairs(std::vector<Profile> &profiles) {
  // Suggested data structures, replace if/as necessary
  typedef std::tuple<uint32_t, uint32_t, double> Pairing;
  std::vector<uint32_t> males, females;
  std::vector<Pairing> pairings;
  std::set<uint32_t> picked;
  std::map<uint32_t, uint32_t> pairs;

  // Break into separate lists of males and females
  for(auto person : profiles)
  {
    if(person.gender==Gender::FEMALE) //female
    {
      females.push_back(person.id);
    }
    else if (person.gender==Gender::MALE) //male
    {
      
      males.push_back(person.id);
    }
  }
  // Generate list of all possible pairings
  for(auto male : males)
  {
    for (auto female : females)
    {
      auto _profiles = getProfilePair(male, female, profiles);
      Profile maleP = G(_profiles, 0);
      Profile femaleP = G(_profiles, 1);
      Pairing pair = std::make_tuple(male, female, score(maleP, femaleP));
      pairings.push_back(pair);
    }
    
  }

  // Sort pairings in descending order of score
  std::sort(pairings.begin(), pairings.end(), sortByScore);
  
  // Pick starting at the top upto required number of pairs
  
  
  // Be sure not to pick the same member twice (hint: use std::set)

  // Return pair of male/female indexes into profiles
  return pairs;
}
