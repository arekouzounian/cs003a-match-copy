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

double score(const Profile &, const Profile &);

typedef std::tuple<uint32_t, uint32_t, double> Entry;

std::tuple<std::vector<Entry>, std::vector<Profile>> getResults(int amt)
{
    std::vector<Profile> up = profiles(amt);
    std::vector<Entry> ut;
    for (auto p : Match::pairs(up))
    {
        ut.push_back({up[p.first].id, up[p.second].id, score(up[p.first], up[p.second])});
    }

    std::sort(ut.begin(), ut.end(), [](Entry a, Entry b) {
        return std::get<0>(a) < std::get<0>(b);
    });

    return std::tuple<std::vector<Entry>, std::vector<Profile>>(ut, up);
}

//create test to check for males in first column
TEST(match, males)
{
    auto tup = getResults(100);
    std::vector<Profile> up = std::get<1>(tup);
    std::vector<Entry> ut = std::get<0>(tup);
    bool allMaleColumn = true;
    for(int i = 0; i < ut.size(); i++)
    {
        auto id = std::get<0>(ut[i]);
        for(auto profile : up)
        {
            if(id == profile.id && profile.gender == Gender::FEMALE)
                allMaleColumn = false;
        }
    }

    EXPECT_TRUE(allMaleColumn);
}

//create test to check correct sorting for scores
//should be sorted by Male ID
TEST(match, scores)
{
    auto tup = getResults(100);
    std::vector<Entry> ut = std::get<0>(tup);
    bool success = true;
    for(int i = 1; i < ut.size(); i++)
    {
        //curr male ID less than prev
        if(std::get<0>(ut[i]) < std::get<0>(ut[i-1]))
        {
            success = false;
        }
    }
    EXPECT_TRUE(success);
}

//create test to check for females in second column
TEST(match, females)
{
    auto tup = getResults(100);
    std::vector<Profile> up = std::get<1>(tup);
    std::vector<Entry> ut = std::get<0>(tup);
    bool allFemaleColumn = true;
    for(int i = 0; i < ut.size(); i++)
    {
        auto id = std::get<1>(ut[i]);
        for(auto profile : up)
        {
            if(id == profile.id && profile.gender == Gender::MALE)
                allFemaleColumn = false;
        }
    }

    EXPECT_TRUE(allFemaleColumn);
}

//check that no score is 0 or below
TEST(match, badScore)
{
    auto tup = getResults(100);
    std::vector<Entry> ut = std::get<0>(tup);
    for(int i = 0; i < ut.size(); i++)
    {
        double currScore = std::get<2>(ut[i]);
        EXPECT_GT(currScore, 0.0);
    }
}