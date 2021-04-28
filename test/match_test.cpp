/**
 * Unit tests.
 *
 * Copyright (c) 2021, Arek Ouzounian.
*/

// Write your unit tests here
// Be sure to test at least some of the key requirements in README
// Use the Orvile unit tests as guide
#include <cstdio>
#include <gtest/gtest.h>
#include "match/match.h"
#include "data/data.h"



TEST(match, score)
{
    auto perfiles = profiles(2);
    auto one = std::get<1>(perfiles[0].country);
    auto two = std::get<1>(perfiles[0].country);
    printf("Person 1 country: %d, %lf\n", std::get<0>(perfiles[0].country), one);
    printf("Person 2 country: %d, %lf\n", std::get<0>(perfiles[1].country), two);
    printf("%lf", one + two);
    //printf("Country score: %lf", score(perfiles[0], perfiles[1]));
}