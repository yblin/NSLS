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

#ifndef TEST_CTP_H_
#define TEST_CTP_H_

#include <vector>

#include "test/basic_test.h"

namespace moo {

/**
 * Problem:                CTP1
 * Dimension:              10
 */
class CTP1Test : public BasicTest{
public:
    CTP1Test() {
        name = "CTP1";
        parameter.n_objectives = 2;
        parameter.n_variables = 10;
        parameter.n_constraints = 2;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        for (int i = 0; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = 0.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);

        constraints.push_back(Constraint1);
        constraints.push_back(Constraint2);
    }

    static double Objective1(const std::vector<double>& x) {
        return x[0];
    }

    static double Objective2(const std::vector<double>& x) {
        double result = 0.0;
        double g = Gvalue(x);

        result = g * exp(- Objective1(x) / g);
        return result;
    }

    static double Constraint1(const std::vector<double>& x) {
        double ob1 = Objective1(x);
        double ob2 = Objective2(x);

        double result = (0.858 * exp(-0.541 * ob1) - ob2);
        return result; // result < 0 is satisfied.
    }

    static double Constraint2(const std::vector<double>& x) {
        double ob1 = Objective1(x);
        double ob2 = Objective2(x);
        double result = (0.728 * exp(-0.295 * ob1) - ob2);
        return result; // result < 0 is satisied.
    }

    static double Gvalue(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double sum = 0.0;
        for(int i = 1; i < n; ++i) {
            sum += x[i];
        }
        return 1.0 + 9.0 * (sum / (n - 1));
    }
};

} // namespace moo

#endif // TEST_CTP_H_
