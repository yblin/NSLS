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

#ifndef TEST_TEST_KUR_H_
#define TEST_TEST_KUR_H_

#include "test/basic_test.h"

namespace moo {

/**
 * Problem:                KUR
 * Dimension:              2
 * Variable bounds:        [-5.0, 5.0]
 * Objective function1:    f1(x) = sum(-10exp(-0.2 * sqrt(x0^2 + x1^2)))
 * Objective function2:    f2(x) = sum(|xi|^0.8 + 5.0sin(xi^3))
 * Optimal solutions:      [0,2]
 * Condition:              nonconvex
 */
class KURTest : public BasicTest {
public:
    KURTest() : BasicTest() {
        name = "KUR";
        parameter.n_objectives = 2;
        parameter.n_variables = 3;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        parameter.min_variables[0] = -5.0;
        parameter.max_variables[0] = 5.0;
        parameter.min_variables[1] = -5.0;
        parameter.max_variables[1] = 5.0;
        parameter.min_variables[2] = -5.0;
        parameter.max_variables[2] = 5.0;

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

private:
    /**
     * f1(x) = sum(-10exp(-0.2 * sqrt(x0^2 + x1^2))).
     */
    static double Objective1(const std::vector<double>& x) {
       return -10.0 * (exp(-0.2 * sqrt(x[0] * x[0] + x[1] * x[1])) +
                       exp(-0.2 * sqrt(x[0] * x[0] + x[1] * x[1])));
    }

    /**
     * f2(x) = sum(|xi|^0.8 + 5.0sin(xi^3)).
     */
    static double Objective2(const std::vector<double>& x) {
        return pow(fabs(x[0]), 0.8) + 5.0 * sin(pow(x[0], 3.0)) +
               pow(fabs(x[1]), 0.8) + 5.0 * sin(pow(x[1], 3.0)) +
               pow(fabs(x[2]), 0.8) + 5.0 * sin(pow(x[2], 3.0));
    }
};

} // namespace moo

#endif // TEST_TEST_KUR_H_
