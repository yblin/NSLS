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

#ifndef TEST_TEST_SCH_H_
#define TEST_TEST_SCH_H_

#include "core/math.h"
#include "test/basic_test.h"

namespace moo {

/**
 * Problem:                SCH
 * Dimension:              1
 * Variable bounds:        [-10^3, 10^3]
 * Objective function1:    f1(x) = x^2
 * Objective function2:    f2(x) = (x - 2)^2
 * Optimal solutions:      x = [0, 2]
 * Condition:              convex
 */
class SCHTest : public BasicTest {
public:
    SCHTest() {
        name = "SCH";
        parameter.n_objectives = 2;
        parameter.n_variables = 1;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        parameter.min_variables[0] = -1000.0;
        parameter.max_variables[0] = 1000.0;

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

private:
    /**
     * f1(x) = x0^2.
     */
    static double Objective1(const std::vector<double>& x) {
        return Sqr(x[0]);
    }

    /**
     * f2(x) = (x0 - 2)^2.
     */
    static double Objective2(const std::vector<double>& x) {
        return Sqr(x[0] - 2);
    }
};

} // namespace moo

#endif // TEST_TEST_SCH_H_
