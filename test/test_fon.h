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

#ifndef TEST_TEST_FON_H_
#define TEST_TEST_FON_H_

#include "core/math.h"
#include "test/basic_test.h"

namespace moo {

/**
 * Problem:                FON
 * Dimension:              2
 * Variable bounds:        [-4.0, 4.0]
 * Objective function1:    f1(x) = 1 - exp(-sum[(xi - 1/sqrt(3))^2])
 * Objective function2:    f2(x) = 1 - exp(-sum[(xi + 1/sqrt(3))^2])
 * Optimal solutions:      x0 = x1 = x2
 * Condition:              nonconvex
 */
class FONTest : public BasicTest {
public:
    FONTest() : BasicTest() {
        name = "FON";
        parameter.n_objectives = 2;
        parameter.n_variables = 3;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        parameter.min_variables[0] = -4.0;
        parameter.max_variables[0] = 4.0;
        parameter.min_variables[1] = -4.0;
        parameter.max_variables[1] = 4.0;
        parameter.min_variables[2] = -4.0;
        parameter.max_variables[2] = 4.0;

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

private:
    /**
     * f1(x) = 1 - exp(-sum[(xi - 1/sqrt(3))^2]).
     */
    static double Objective1(const std::vector<double>& x) {
        const double sqrt_3 = std::sqrt(3);
        double sum1 = Sqr(x[0] - 1.0 / sqrt_3);
        double sum2 = Sqr(x[1] - 1.0 / sqrt_3);
        double sum3 = Sqr(x[2] - 1.0 / sqrt_3);

        return 1.0 - std::exp(-(sum1 + sum2 + sum3));
    }

    /**
     * f2(x) = 1 - exp(-sum[(xi + 1/sqrt(3))^2]).
     */
    static double Objective2(const std::vector<double>& x) {
        const double sqrt_3 = std::sqrt(3);
        double sum1 = Sqr(x[0] + 1.0 / sqrt_3);
        double sum2 = Sqr(x[1] + 1.0 / sqrt_3);
        double sum3 = Sqr(x[2] + 1.0 / sqrt_3);

        return 1.0 - std::exp(-(sum1 + sum2 + sum3));
    }
};

} // namespace moo

#endif // TEST_TEST_FON_H_
