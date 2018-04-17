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

#ifndef TEST_TEST_LZ_H_
#define TEST_TEST_LZ_H_

#include <vector>

#include "codelibrary/util/array/array_2d.h"
#include "test/basic_test.h"

namespace moo {

template <typename T>
inline const T Sqr(const T& value) {
    return value * value;
}

/**
 * Problem:                LZ1
 * Dimension:              30
 * Variable bounds:        [0, 1]
 * Objective function1:    f1(x) = x0 + 2 / |J1| * Sum[(xj - g(j))^2]
 * Objective function2:    f2(x) = 1 - sqrt(x1) + 2 / |J2| * Sum[(xj - g(j))^2]
 *                         g(j) = x0^[0.5 * (1.0 + 3 * (j - 2)/(n - 2))]
 */
class LZ1Test : public BasicTest{
public:
    LZ1Test() {
        name = "LZ1";
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
     * f1(x) = x0 + 2 / |J1| * Sum[(xj - g(j))^2].
     * g(j) = x0^[0.5 * (1.0 + 3 * (j - 2)/(n - 2))].
     */
    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum = 0.0;
        for (int j = 3; j <= n; j += 2) {
            sum += Sqr(x[j - 1] -
                       pow(x[0], 0.5 * (1.0 + 3.0 * (j - 2) / (n - 2))));
            ++count;
        }
        return x[0] + 2.0 / count * sum;
    }

    /**
     * f2(x) = 1 - sqrt(x1) + 2 / |J2| * Sum[(xj - g(j))^2].
     * g(j) = x0^[0.5 * (1.0 + 3 * (j - 2)/(n - 2))].
     */
    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double sum = 0.0;
        int count = 0;
        for (int j = 2; j <= n; j += 2) {
            sum += Sqr(x[j - 1] -
                       pow(x[0], 0.5 * (1.0 + 3.0 * (j - 2) / (n - 2))));
            ++count;
        }
        return 1.0 - sqrt(x[0]) + 2.0 / count * sum;
    }
};

/**
 * Problem:                LZ2
 * Dimension:              30
 * Variable bounds:        x0 ~ [0, 1]; x1 - xn-1 ~ [-1,1]
 * Objective function1:    f1(x) = x0 + 2 / |J1| * Sum((xj - g(j))^2)
 * Objective function2:    f2(x) = 1 - sqrt(x0) + 2/|J2| * Sum(xj - g(j)^2)
 *                         g(j) = sin(6 * PI * x0 + j * PI / n)
 */
class LZ2Test : public BasicTest{
public:
    LZ2Test() {
        name = "LZ2";
        parameter.n_objectives = 2;
        parameter.n_variables = 30;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        parameter.min_variables[0] = 0.0;
        parameter.max_variables[0] = 1.0;
        for (int i = 1; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = -1.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

    /**
     * f1(x) = x0 + 2 / |J1| * Sum((xj - g(j))^2).
     * g(j) = sin(6 * PI * x0 + j * PI / n).
     */
    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum = 0.0;
        for (int j = 3; j <= n; j += 2) {
            sum += Sqr(x[j - 1] - sin(6.0 * cl::PI * x[0] +  cl::PI * j / n));
            ++count;
        }
        return x[0] + 2.0 / count * sum;
    }

    /**
     * f2(x) = 1 - sqrt(x0) + 2/|J2| * Sum(xj - g(j)^2).
     * g(j) = sin(6 * PI * x0 + j * PI / n).
     */
    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double sum = 0.0;
        int count = 0;
        for (int j = 2; j <= n; j += 2) {
            sum += Sqr(x[j - 1] - sin(6.0 * cl::PI * x[0] + cl::PI * j / n));
            ++count;
        }
        return 1.0 - sqrt(x[0]) + 2.0 / count * sum;
    }
};

/**
 * Problem:                LZ3
 * Dimension:              30
 * Variable bounds:        x0 ~ [0, 1]; x1 - xn-1 ~ [-1,1]
 * Objective function1:    f1(x) = x0 + 2 / |J1| * Sum[(xj - g1(j))^2]
 * Objective function2:    f2(x) = 1 - sqrt(x0) + 2/|J2| * Sum[xj - g2(j)^2]
 *                         g1(j) = cos(6 * PI * x0 + j * PI / n)
 *                         g2(j) = sin(6 * PI * x0 + j * PI / n)
 */
class LZ3Test : public BasicTest{
public:
    LZ3Test() {
        name = "LZ3";
        parameter.n_objectives = 2;
        parameter.n_variables = 30;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        parameter.min_variables[0] = 0.0;
        parameter.max_variables[0] = 1.0;
        for (int i = 1; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = -1.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

    /**
     * f1(x) = x0 + 2 / |J1| * Sum[(xj - g1(j))^2].
     * g1(j) = cos(6 * PI * x0 + j * PI / n).
     */
    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum = 0.0;
        for (int j = 3; j <= n; j += 2) {
            sum += Sqr(x[j - 1] -
                       0.8 * x[0] * cos(6.0 * cl::PI * x[0] + cl::PI * j / n));
            ++count;
        }
        return x[0] + 2.0 / count * sum;
    }

    /**
     * f2(x) = 1 - sqrt(x0) + 2/|J2| * Sum[xj - g2(j)^2].
     * g2(j) = sin(6 * PI * x0 + j * PI / n).
     */
    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double sum = 0.0;
        int count = 0;
        for (int j = 2; j <= n; j += 2) {
            sum += Sqr(x[j - 1] -
                        0.8 * x[0] * sin(6.0 * cl::PI * x[0] + cl::PI * j / n));
            ++count;
        }
        return 1.0 - sqrt(x[0]) + 2.0 / count * sum;
    }
};

/**
 * Problem:                LZ4
 * Dimension:              30
 * Variable bounds:        x0 ~ [0, 1]; x1 - xn-1 ~ [-1,1]
 * Objective function1:    f1(x) = x1 + 2 / |J1| * Sum[(xj - g1(j))^2]
 * Objective function2:    f2(x) = 1 - sqrt(x1) + 2/|J2| * Sum[xj - g2(j)^2]
 *                         g1(j) = 0.8 * x0 * cos((6 * PI * x0 + PI * j / n)/3)
 *                         g2(j) = 0.8 * x0 * sin(6 * PI * x0 + M_PI * j / n).
 */
class LZ4Test : public BasicTest{
public:
    LZ4Test() {
        name = "LZ4";
        parameter.n_objectives = 2;
        parameter.n_variables = 30;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        parameter.min_variables[0] = 0.0;
        parameter.max_variables[0] = 1.0;
        for (int i = 1; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = -1.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

    /**
     *  f1(x) = x1 + 2 / |J1| * Sum((xj - g(j))^2).
     *  g1(j) = 0.8 * x[0] * cos((6.0 * M_PI * x[0) + M_PI * j / n)/ 3.0).
     */
    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum = 0.0;
        for (int j = 3; j <= n; j += 2) {
            sum += Sqr(x[j - 1] - 0.8 * x[0] *
                       std::cos((6.0 * cl::PI * x[0] + cl::PI * j / n) / 3.0));

            ++count;
        }
        return x[0] + 2.0 / count * sum;
    }

    /**
     * f2(x) = 1 - sqrt(x1) + 2/|J2| * Sum(xj - g2(j)^2.
     * g2(j) = 0.8 * x[0] * sin(6.0* pi * x[0) + M_PI * j / n).
     */
    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double sum = 0.0;
        int count = 0;
        for (int j = 2; j <= n; j += 2) {
            sum += Sqr(x[j - 1] - 0.8 * x[0] * std::sin(6.0 * cl::PI * x[0] +
                                                        cl::PI * j / n));
            ++count;
        }
        return 1.0 - std::sqrt(x[0]) + 2.0 / count * sum;
    }
};

/**
 * Problem:                LZ5
 * Dimension:              30
 * Variable bounds:        x0 ~ [0, 1]; x1 - xn-1 ~ [-1,1]
 * Objective function1:    f1(x) = x1 + 2 / |J1| * Sum((xj - g1(j))^2)
 * Objective function2:    f2(x) = 1 - sqrt(x1) + 2/|J2| * Sum(xj - g(j)^2
 *                         g1(j) = [0.3 * x0 * x0 *
 *                                  cos(24PI * x0 + 4j * PI / n) + 0.6 * x0] *
 *                                 cos(6.0 * PI * x0 + PI * j / n)
 *                         g2(j) = [0.3 * x0 * x0 *
 *                                  cos(24PI * x0 + 4j * PI / n) + 0.6 * x0] *
 *                                 sin(6.0 * PI * x0 + PI * j / n)
 */
class LZ5Test : public BasicTest{
public:
    LZ5Test() {
        name = "LZ5";
        parameter.n_objectives = 2;
        parameter.n_variables = 30;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        parameter.min_variables[0] = 0.0;
        parameter.max_variables[0] = 1.0;
        for (int i = 1; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = -1.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

    /**
     * f1(x) = x1 + 2 / |J1| * Sum((xj - g1(j))^2).
     * g1(j) = [0.3 * x0 * x0 * cos(24PI * x0 + 4j * PI / n) + 0.6 * x0] *
     *         cos(6.0 * PI * x0 + PI * j / n).
     */
    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum = 0.0;
        for (int j = 3; j <= n; j += 2) {
            sum += Sqr(x[j - 1] -
                       (0.3 * x[0] * x[0] * std::cos(24.0 * cl::PI * x[0] +
                                                     4.0 * j * cl::PI / n) +
                        0.6 * x[0]) *
                       std::cos(6.0 * cl::PI * x[0] + cl::PI * j / n));
            ++count;
        }

        return x[0] + 2.0 / count * sum;
    }

    /**
     * f2(x) = 1 - sqrt(x1) + 2/|J2| * Sum(xj - g(j)^2.
     * g2(j) = [0.3 * x0 * x0 * cos(24PI * x0 + 4j * PI / n) + 0.6 * x0] *
     *         sin(6.0 * PI * x0 + PI * j / n).
     */
    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double sum = 0.0;
        int count = 0;
        for (int j = 2; j <= n; j += 2) {
            sum += Sqr(x[j - 1] -
                       (0.3 * x[0] * x[0] * std::cos(24.0 * cl::PI * x[0] +
                                                     4.0 * j * cl::PI / n) +
                        0.6 * x[0]) *
                       std::sin(6.0 * cl::PI * x[0] + cl::PI * j / n));
            ++count;
        }
        return 1.0 - sqrt(x[0]) + 2.0 / count * sum;
    }
};

/**
 * Problem:                LZ6
 * Dimension:              30
 * Variable bounds:        x0 - x1 ~ [0, 1]; x2 - xn-1 ~ [-2,2]
 */
class LZ6Test : public BasicTest{
public:
    LZ6Test() {
        name = "LZ6";
        parameter.n_objectives = 3;
        parameter.n_variables = 10;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        parameter.min_variables[0] = 0.0;
        parameter.max_variables[0] = 1.0;
        parameter.min_variables[1] = 0.0;
        parameter.max_variables[1] = 1.0;
        for (int i = 2; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = -2.0;
            parameter.max_variables[i] = 2.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
        objectives.push_back(Objective3);
    }

    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = 0.0;
        sum1 = std::cos(0.5 * x[0] * cl::PI) * std::cos(0.5 * x[1] * cl::PI);
        double sum2 = 0.0;
        for (int j = 4; j <= n; j += 3) {
            sum2 += Sqr(x[j - 1] - 2.0 * x[1] *
                        std::sin(2.0 * cl::PI * x[0] + j * cl::PI / n));
            ++count;
        }
        return sum1 + 2.0 / count * sum2;
    }

    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = 0.0;
        sum1 = std::cos(0.5 * x[0] * cl::PI) * std::sin(0.5 * x[1] * cl::PI);
        double sum2 = 0.0;
        for (int j = 5; j <= n; j += 3) {
            sum2 += Sqr(x[j - 1] - 2.0 * x[1] *
                        std::sin(2.0 * cl::PI * x[0] + j * cl::PI / n));
            ++count;
        }
        return sum1 + 2.0 / count * sum2;
    }

    static double Objective3(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = 0.0;
        sum1 = std::sin(0.5 * x[0] * cl::PI);
        double sum2 = 0.0;
        for (int j = 3; j <= n; j += 3) {
            sum2 += Sqr(x[j - 1] - 2.0 * x[1] *
                        std::sin(2.0 * cl::PI * x[0] + j * cl::PI / n));
            ++count;
        }
        return sum1 + 2.0 / count * sum2;
    }
};

/**
 * Problem:                LZ7
 * Dimension:              10
 * Variable bounds:        x ~ [0, 1]
 * Objective function1:    f1(x) = x1 + 2 / |J1| * sum
 * Objective function2:    f2(x) = 1 - sqrt(x1) + 2/|J2| * sum
 *                         yj = x[j - 1] -
 *                              pow(x[0], 0.5 * (1.0 + 3.0 * (j - 2)/(n - 2)))
 *                         sum += (4.0 * yj * yj - cos(8.0 * yj * PI + 1.0))
 */
class LZ7Test : public BasicTest{
public:
    LZ7Test() {
        name = "LZ7";
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
     * f1(x) = x1 + 2 / |J1| * Sum.
     * yj = x[j - 1] - pow(x[0], 0.5 * (1.0 + 3.0 * (j - 2) / (n - 2)));
     * sum += (4.0 * yj * yj - cos(8.0 * yj * M_PI + 1.0)).
     */
    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum = 0.0;
        for (int j = 3; j <= n; j += 2) {
            double yj = x[j - 1] -
                        std::pow(x[0], 0.5 * (1.0 + 3.0 * (j - 2) / (n - 2)));
            sum += (4.0 * yj * yj - std::cos(8.0 * yj * cl::PI) + 1.0);
            ++count;
        }
        return x[0] + 2.0 / count * sum;
    }

    /**
     * f2(x) = 1.0 - sqrt(x[0]) + 2.0 / count * sum;
     * yj = x[j - 1] - pow(x[0],0.5 * (1.0 + 3.0 * (j - 2)/(n - 2)));
     * sum += (4.0 * yj * yj - cos(8.0 * yj * PI + 1.0));
     */
    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double sum = 0.0;
        int count = 0;
        double yj = 0.0;
        for (int j = 2; j <= n; j += 2) {
            yj = x[j - 1] - std::pow(x[0],
                                     0.5 * (1.0 + 3.0 * (j - 2) / (n - 2)));
            sum += (4.0 * yj * yj - std::cos(8.0 * yj * cl::PI) + 1.0);
            ++count;
        }
        return 1.0 - std::sqrt(x[0]) + 2.0 / count * sum;
    }
};

/**
 * Problem:                LZ8
 * Dimension:              10
 * Variable bounds:        x ~ [0, 1]
 * Objective function1:    f1(x) =  x1 + 2 / |J1| * (4.0 * sum1 - 2 * sum2 + 2)
 * Objective function2:    f2(x) =  1 - sqrt(x1) +
 *                                  2/|J2| * (4.0 * sum1 - 2 * sum2 + 2)
 *                         yj = x[j - 1] -
 *                              pow(x[0], 0.5 * (1.0 + 3.0 * (j - 2))/(n - 2))
 *                         sum1 += yj^2
 *                         sum2 *= cos(20 * yj * PI / sqrt(j)
 */
class LZ8Test : public BasicTest{
public:
    LZ8Test() {
        name = "LZ8";
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
     * f1(x) =  x1 + 2 / |J1| * (4.0 * sum1 - 2 * sum2 + 2).
     * yj = x[j - 1] - pow(x[0], 0.5 * (1.0 + 3.0 * (j - 2))/(n - 2));
     * sum1 += yj^2;
     * sum2 *= cos(20 * yj * PI / sqrt(j).
     */
    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = 0.0;
        double sum2 = 1.0;
        for (int j = 3; j <= n; j += 2) {
            double yj = x[j - 1] -
                        std::pow(x[0], 0.5 * (1.0 + 3.0 * (j - 2) / (n - 2)));
            sum1 += yj * yj;
            sum2 *= std::cos(20.0 * yj * cl::PI / std::sqrt(j));
            ++count;
        }
        return x[0] + 2.0 / count * (4.0 * sum1 - 2.0 * sum2 + 2.0);
    }

    /**
     * f2(x) =  1 - sqrt(x1) + 2/|J2| * (4.0 * sum1 - 2 * sum2 + 2).
     * yj = x[j - 1] - pow(x[0], 0.5 * (1.0 + 3.0 * (j - 2))/(n - 2));
     * sum1 += yj^2;
     * sum2 *= cos(20 * yj * PI / sqrt(j).
     */
    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double sum1 = 0.0;
        double sum2 = 1.0;
        int count = 0;
        for (int j = 2; j <= n; j += 2) {
            double yj = x[j - 1] -
                        std::pow(x[0],0.5 * (1.0 + 3.0 * (j - 2) / (n - 2)));
            sum1 += yj * yj;
            sum2 *= std::cos(20.0 * yj * cl::PI / std::sqrt(j));
            ++count;
        }

        return 1.0 - std::sqrt(x[0]) + 2.0 / count *
               (4.0 * sum1 - 2.0 * sum2 + 2.0);
    }
};

/**
 * Problem:                LZ9
 * Dimension:              30
 * Variable bounds:        x0 ~ [0, 1]; x1-xn ~ [-1, 1]
 * Objective function1:    f1(x) = x1 + 2 / |J1| * (4*sum1 - 2*sum2 + 2).
 * Objective function2:    f2(x) = 1 - sqrt(x1) + 2/|J2| * (4sum1 - 2sum2 + 2).
 *                         yj = x[j - 1] -
 *                              pow(x[0], 0.5*(1.0 + 3.0 * (j - 2)) / (n - 2));
 *                         sum1 += pow(yj, 2.0);
 *                         sum2 *= cos(20.0 * yj * M_PI / sqrt(j);
 * Optimal solutions:      x1 = [0, 1], xi = 0, i = 1, ..., n - 1
 * Condition:              convex
 */
class LZ9Test : public BasicTest{
public:
    LZ9Test() {
        name = "LZ9";
        parameter.n_objectives = 2;
        parameter.n_variables = 30;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        parameter.min_variables[0] = 0.0;
        parameter.max_variables[0] = 1.0;
        for (int i = 1; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = -1.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
    }

    /**
     *   f1(x) =  x[0] + 2.0 / count * sum.
     *   sum += pow(x[j - 1] - sin(6.0 * M_PI * x[0] + M_PI * j / n),2.0);
     */
    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());

        int count = 0;
        double sum = 0.0;
        for (int j = 3; j <= n; j += 2) {
            sum += Sqr(x[j - 1] - std::sin(6.0 * cl::PI * x[0] +
                                           cl::PI * j / n));
            ++count;
        }
        return x[0] + 2.0 / count * sum;
    }

    /**
     * f2(x) =  1.0 - x[0] * x[0] + 2.0 / count * sum.
     * sum += pow(x[j - 1] - sin(6.0 * M_PI * x[0] + M_PI * j / n),2.0);
     */
    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double sum = 0.0;
        int count = 0;
        for (int j = 2; j <= n; j += 2) {
            sum += Sqr(x[j - 1] - std::sin(6.0 * cl::PI * x[0] +
                                           cl::PI * j / n));
            ++count;
        }

        return 1.0 - x[0] * x[0] + 2.0 / count * sum;
    }
};

} // namespace moo

#endif // TEST_TEST_LZ_H_
