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

#ifndef TEST_TEST_ZDT_H_
#define TEST_TEST_ZDT_H_

#include <cmath>

#include "codelibrary/base/constants.h"

#include "test/basic_test.h"

namespace moo {

/**
 * Problem:                ZDT1
 * Dimension:              30
 * Variable bounds:        [0, 1]
 * Objective function1:    f1(x) = x0
 * Objective function2:    f2(x) = g(x) * [1 - sqrt(x0 / g(x))];
 *                         g(x) = 1 + 9 * [Sum(xi, i = [1, n)) / (n - 1)].
 * Optimal solutions:      x0 = [0, 1], xi = 0, i = 1, ..., n - 1
 * Condition:              convex
 */
class ZDT1Test : public BasicTest {
public:
    ZDT1Test() {
        name = "ZDT1";
        parameter.n_objectives = 2;
        parameter.n_variables = 30;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        for (int i = 0; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = 0.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

    /**
     * f1(x) = x0.
     */
    static double Objective1(const std::vector<double>& x) {
        return x[0];
    }

    /**
     * f2(x) = g(x) * [1 - sqrt(x0 / g(x))];
     * g(x) = 1 + 9 * [Sum(xi, i = [1, n)) / (n - 1)].
     */
    static double Objective2(const std::vector<double>& x) {
        double sum = 0.0;
        for (size_t i = 1; i < x.size(); ++i) {
            sum += x[i];
        }
        double g = 1.0 + 9.0 * sum / (x.size() - 1);
        return g * (1.0 - sqrt(x[0] / g));
    }
};

/**
 * Problem:                ZDT2
 * Dimension:              30
 * Variable bounds:        [0, 1]
 * Objective function1:    f1(x) = x0
 * Objective function2:    f2(x) = g(x) * [1 - (f1(x) / g(x))^2];
 *                         g(x) = 1 + 9 * [Sum(xi, i = [1, n)) / (n - 1)]
 * Optimal solutions:      x0 = [0, 1], xi = 0, i = 1, ..., n - 1
 * Condition:              nonconvex
 */
class ZDT2Test : public BasicTest{
public:
    ZDT2Test() {
        name = "ZDT2";
        parameter.n_objectives = 2;
        parameter.n_variables = 30;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        for (int i = 0; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = 0.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

    /**
     * f1(x) = x0.
     */
    static double Objective1(const std::vector<double>& x) {
        return x[0];
    }

    /**
     * f2(x) = g(x) * [1 - sqrt(x0 / g(x))];
     * g(x) = 1 + 9 * [Sum(xi, i = [1, n)) / (n - 1)].
     */
    static double Objective2(const std::vector<double>& x) {
        double sum = 0.0;
        for (size_t i = 1; i < x.size(); ++i) {
            sum += x[i];
        }
        double g = 1.0 + 9.0 * sum / (x.size() - 1);
        return g * (1.0 - (x[0] / g) * (x[0] / g));
    }
};

/**
 * Problem:                ZDT3
 * Dimension:              30
 * Variable bounds:        [0, 1]
 * Objective function1:    f1(x) = x0
 * Objective function2:    f2(x) = g(x) * [1 - sqrt(f1(x) / g(x)) -
 *                                         x0 / g(x) * sin(10PI * x0)];
 *                         g(x) = 1 + 9 * [Sum(xi, i = [1, n)) / (n - 1)]
 * Optimal solutions:      x0 = [0, 1], xi = 0, i = 1, ..., n - 1
 * Condition:              convex, disconnected
 */
class ZDT3Test : public BasicTest{
public:
    ZDT3Test() {
        name = "ZDT3";
        parameter.n_objectives = 2;
        parameter.n_variables = 30;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        for (int i = 0; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = 0.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

    /**
     * f1(x) = x0.
     */
    static double Objective1(const std::vector<double>& x) {
        return x[0];
    }

    /**
     * f2(x) = g(x) * [1 - sqrt(x0 / g(x))];
     * g(x) = 1 + 9 * [Sum(xi, i = [1, n)) / (n - 1)].
     */
    static double Objective2(const std::vector<double>& x) {
        double sum = 0.0;
        for (size_t i = 1; i < x.size(); ++i) {
            sum += x[i];
        }
        double g = 1.0 + 9.0 * sum / (x.size() - 1);
        return g * (1.0 - std::sqrt(x[0] / g) -
               x[0] / g * std::sin(10.0 * cl::PI * x[0]));
    }
};

/**
 * Problem:                ZDT4
 * Dimension:              10
 * Variable bounds:        x0 = [0, 1], xi = [-5, 5], i = 1, ..., n
 * Objective function1:    f1(x) = x0
 * Objective function2:    f2(x) = g(x) * [1 - sqrt(x0 / g(x))];
 *                         g(x) = 1 + 10 * (n - 1) +
 *                                Sum[xi * xi - 10cos(4PI * xi) | i = [1, n)]
 * Optimal solutions:      x0 = [0, 1], xi = 0, i = 1, ..., n - 1
 * Condition:              nonconvex
 */
class ZDT4Test : public BasicTest{
public:
    ZDT4Test() {
        name = "ZDT4";
        parameter.n_objectives = 2;
        parameter.n_variables = 10;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        parameter.min_variables[0] = 0.0;
        parameter.max_variables[0] = 1.0;
        for (int i = 1; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = -5.0;
            parameter.max_variables[i] = 5.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

    /**
     * f1(x) = x0.
     */
    static double Objective1(const std::vector<double>& x) {
        return x[0];
    }

    /**
     * f2(x) = g(x) * [1 - sqrt(x0 / g(x))];
     * g(x) = 1 + 10 * (n - 1) + Sum[xi * xi - 10cos(4PI * xi) | i = [1, n)].
     */
    static double Objective2(const std::vector<double>& x) {
        double g = 1.0 + 10.0 * (x.size() - 1);
        for (size_t i = 1; i < x.size(); ++i) {
            g += x[i] * x[i] - 10.0 * std::cos(4.0 * cl::PI * x[i]);
        }
        return g * (1.0 - std::sqrt(x[0] / g));
    }
};


/**
 * Problem:                ZDT6
 * Dimension:              10
 * Variable bounds:        [0, 1]
 * Objective function1:    f1(x) = 1 - e^(-4 * x0) * sin(6PI * x0)^6
 * Objective function2:    f2(x) = g(x) * [1 - (f1(x) / g(x))^2];
 *                         g(x) = 1 + 9 * [Sum(xi, i = [1, n)) / (n - 1)]^0.25
 * Optimal solutions:      x0 = [0, 1], xi = 0, i = 1, ..., n - 1
 * Condition:              nonconvex, nonuniformly spaced
 */
class ZDT6Test : public BasicTest{
public:
    ZDT6Test() {
        name = "ZDT6";
        parameter.n_objectives = 2;
        parameter.n_variables = 10;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        for (int i = 0; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = 0.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

    /**
     * f1(x) = 1 - e^(-4 * x0) * sin(6PI * x0)^6.
     */
    static double Objective1(const std::vector<double>& x) {
        return 1.0 - std::exp(-4.0 * x[0]) *
                     std::pow(std::sin(6.0 * cl::PI * x[0]), 6.0);
    }

    /**
     * f2(x) = g(x) * [1 - (f1(x) / g(x))^2];
     * g(x) = 1 + 9 * [Sum(xi, i = [1, n)) / (n - 1)]^0.25.
     */
    static double Objective2(const std::vector<double>& x) {
        double sum = 0.0;
        for (size_t i = 1; i < x.size(); ++i) {
            sum += x[i];
        }
        double g = 1.0 + 9.0 * pow(sum / (x.size() - 1), 0.25);
        double f1 = Objective1(x);
        return g * (1.0 - (f1 / g) * (f1 / g));
    }
};

} // namespace moo

#endif // TEST_TEST_ZDT_H_
