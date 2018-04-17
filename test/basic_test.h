//
// Copyright 2013 Yangbin Lin and Bili Chen. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// To use this code, please cite the follow paper:
//
// Chen B, Zeng W, Lin Y, et al. A New Local Search-Based Multiobjective
// Optimization Algorithm[J]. IEEE Transactions on Evolutionary Computation,
// 2014, 19(1):1-1.
//


#ifndef TEST_BASIC_TEST_H_
#define TEST_BASIC_TEST_H_

#include <string>

#include "core/objective.h"
#include "core/parameter.h"
#include "core/constants.h"

namespace moo {

/// Basic Test.
struct BasicTest {
    std::string name;                  // The name of Test.
    Parameter parameter;               // The parameter of Test.
    std::vector<Objective> objectives; // The objectives of Test.
    std::vector<Constraint> constraints; // The constraints of Test.
};

} // namespace moo

#endif // TEST_BASIC_TEST_H_
