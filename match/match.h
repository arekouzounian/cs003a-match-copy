/**
 * Match declarations, you shouldn't need to touch this.
 *
 * Copyright (c) 2021, Sekhar Ravinutala.
 */

#ifndef MATCH_MATCH_H_
#define MATCH_MATCH_H_

#include <cstdint>
#include <map>
#include <vector>
#include "data/data.h"

class Match {
 public:
  // A "static" function can be accessed without instantiating the class
  // Like Match::pairs() - see report.cpp for how it's called
  static std::map<uint32_t, uint32_t> pairs(std::vector<Profile> &);
};

#endif  // MATCH_MATCH_H_
