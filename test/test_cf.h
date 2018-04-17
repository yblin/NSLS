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

#ifndef TEST_CF_H_
#define TEST_CF_H_

#include <vector>
#include "test/basic_test.h"

namespace moo {
/**
 * Problem:                CF1
 * Dimension:              10
 * Variable bounds:        [0, 1]
 * Objective function1:    f1(x) = x0 + 2 / |J1| * Sum[(xj - g(j))^2]
 * Objective function2:    f2(x) = 1 - sqrt(x1) + 2 / |J2| * Sum[(xj - g(j))^2]
 *                         g(j) = x0^[0.5 * (1.0 + 3 * (j - 2)/(n - 2))]
 */
class CF1Test : public BasicTest{
public:
    CF1Test() {
        name = "CF1";
        parameter.n_objectives = 2;
        parameter.n_variables = 10;
        parameter.n_constraints = 1;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        for (int i = 0; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = 0.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);

        constraints.push_back(Constraint1);
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
     * f2(x) = 1 -x1 + 2 / |J2| * Sum[(xj - g(j))^2].
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
        return 1.0 - x[0] + 2.0 / count * sum;
    }

    static double Constraint1(const std::vector<double>& x) {
        double a = 1.0;
        int N = 10;
        double f1 = Objective1(x);
        double f2 = Objective2(x);
        double temp = sin(N * M_PI * (f1 - f2 + 1.0));
        double result = f1 + f2 - a * std::abs(temp) - 1.0;
        return result;// result >=0  is satisfied.
    }
};

/**
 * Problem:                CF2
 * Dimension:              10
 * Variable bounds:        [0, 1]
 * Objective function1:    f1(x) = x0 + 2 / |J1| * Sum[(xj - g(j))^2]
 * Objective function2:    f2(x) = 1 - sqrt(x1) + 2 / |J2| * Sum[(xj - g(j))^2]
 *                         g(j) = x0^[0.5 * (1.0 + 3 * (j - 2)/(n - 2))]
 */
class CF2Test : public BasicTest{
public:
    CF2Test() {
        name = "CF2";
        parameter.n_objectives = 2;
        parameter.n_variables = 10;
        parameter.n_constraints = 1;

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

        constraints.push_back(Constraint1);
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
            sum += Sqr(x[j - 1] - sin(6.0 * M_PI * x[0] +  M_PI * j / n));
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
            sum += Sqr(x[j - 1] - cos(6.0 * M_PI * x[0] + M_PI * j / n));
            ++count;
        }
        return 1.0 - sqrt(x[0]) + 2.0 / count * sum;
    }

    static double Constraint1(const std::vector<double>& x) {
        double a = 1.0;
        int N = 2;
        double f1= Objective1(x);
        double f2 = Objective2(x);
        double temp = a * sin(N * M_PI * (sqrt(f1) - f2 + 1.0));
        double t = f2 + sqrt(f1) - temp - 1.0;
        double result = t / (1.0 + exp(4.0 * std::abs(t)));
        return result; // result >=0  is satisfied.
    }
};

/**
 * Problem:                CF3
 * Dimension:              10
 */
class CF3Test : public BasicTest{
public:
    CF3Test() {
        name = "CF3";
        parameter.n_objectives = 2;
        parameter.n_variables = 10;
        parameter.n_constraints = 1;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);

        parameter.min_variables[0] = 0.0;
        parameter.max_variables[0] = 1.0;

        for (int i = 1; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = -2.0;
            parameter.max_variables[i] = 2.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);

        constraints.push_back(Constraint1);
    }


    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = 0.0;
        double sum2 = 1.0;
        for (int j = 3; j <= n; j += 2) {
            double yj = x[j] - sin(6.0 * M_PI * x[0] + j * M_PI / n);
            sum1 += yj * yj;
            sum2 *= cos(20.0 * yj * M_PI / std::sqrt((double)j));
            ++count;
        }
        return x[0] + 2.0 / count * (4.0 * sum1 - 2.0 * sum2 + 2.0);
    }


    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = 0.0;
        double sum2 = 1.0;
        for (int j = 2; j <= n; j += 2) {
            double yj = x[j] - sin(6.0 * M_PI * x[0] + j * M_PI / n);
            sum1 += yj * yj;
            sum2 *= cos(20.0 * yj * M_PI / std::sqrt((double)j));
            ++count;
        }
        return 1.0 - x[0] * x[0] + 2.0 / count * (4.0 * sum1 - 2.0 * sum2 + 2.0);
    }

    static double Constraint1(const std::vector<double>& x) {
        double a = 1.0;
        int N = 2;
        double f1 = Objective1(x);
        double f2 = Objective2(x);
        double temp = sin(N * M_PI * (f1 * f1 - f2 + 1.0));
        double result = f2 + f1 * f1 - a * temp - 1.0;
        return result;// result >= 0  is satisfied.
    }
};

/**
 * Problem:                CF4
 * Dimension:              10
 */
class CF4Test : public BasicTest{
public:
    CF4Test() {
        name = "CF4";
        parameter.n_objectives = 2;
        parameter.n_variables = 10;
        parameter.n_constraints = 1;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);

        parameter.min_variables[0] = 0.0;
        parameter.max_variables[0] = 1.0;

        for (int i = 1; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = -2.0;
            parameter.max_variables[i] = 2.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);

        constraints.push_back(Constraint1);
    }


    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = 0.0;
        for (int j = 3; j <= n; j += 2) {
            double temp = M_PI * j / ((double)n);
            double yj = x[j] - sin(6.0 * M_PI * x[0] + temp);
            sum1 += yj * yj;
            ++count;
        }
        return x[0] + sum1;
    }

    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = 0.0;
        for (int j = 2; j <= n; j += 2) {
            double temp = M_PI * j /((double)n);
            double yj = x[j] - sin(6.0 * M_PI * x[0] + temp);
            if(j == 2) {
                double sherd = 3.0 / 2.0 * (1.0 - std::sqrt(2.0)/2.0);
                if(yj < sherd)
                    sum1 += std::abs(yj);
                else
                    sum1 += (0.125 + (yj - 1.0) * (yj - 1.0));
            }
            else {
                sum1 += yj * yj;
            }
            ++count;
        }
        return 1.0 - x[0] + sum1;
    }

    static double Constraint1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double t = x[1] - sin(6.0 * M_PI * x[0] + 2.0 * M_PI / n)
                   - 0.5 * x[0]
                   + 0.25;

        double result = t / (1.0 + exp(4.0 * std::abs(t)));
        return result; // result >= 0  is satisfied.
    }
};

/**
 * Problem:                CF5
 * Dimension:              10
 */
class CF5Test : public BasicTest{
public:
    CF5Test() {
        name = "CF5";
        parameter.n_objectives = 2;
        parameter.n_variables = 10;
        parameter.n_constraints = 1;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);

        parameter.min_variables[0] = 0.0;
        parameter.max_variables[0] = 1.0;

        for (int i = 1; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = -2.0;
            parameter.max_variables[i] = 2.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);

        constraints.push_back(Constraint1);
    }


    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = 0.0;
        for (int j = 3; j <= n; j += 2) {
            double yj = x[j] - 0.8 * x[0] * cos(6.0 * M_PI * x[0] +
                        j * M_PI / n);
            double threshold = 3.0 / 2.0 * (1.0 - sqrt(2.0) / 2.0);
            if(j == 2) {
                if(yj < threshold)
                    yj = std::abs(yj);
                else
                    yj = 0.125 + (yj + (yj - 1.0) * (yj - 1.0));
            }
            else {
                yj = 2.0 * yj * yj - cos(4.0 * M_PI * yj) + 1.0;
            }
            sum1 += yj;
            ++count;
        }
        return x[0] + sum1;
    }

    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = 0.0;
        for (int j = 2; j <= n; j += 2) {
            double yj = x[j] - 0.8 * x[0] * sin(6.0 * M_PI * x[0] +
                        j * M_PI / n);
            double threshold = 3.0 / 2.0 * (1.0 - sqrt(2.0) / 2.0);
            if(j == 2) {
                if(yj < threshold)
                    yj = std::abs(yj);
                else
                    yj = 0.125 + (yj + (yj - 1.0) * (yj - 1.0));
            }
            else {
                yj = 2.0 * yj * yj - cos(4.0 * M_PI * yj) + 1.0;
            }
            sum1 += yj;
            ++count;
        }
        return 1.0 - x[0] + sum1;
    }

    static double Constraint1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double result = x[1] - 0.8 * x[0] * sin(6.0 * M_PI * x[0] + 2.0 * M_PI / n) -
                        0.5 * x[0] + 0.25;
        return result; // result >= 0  is satisfied.
    }
};

}

#endif // TEST_CF_H_
