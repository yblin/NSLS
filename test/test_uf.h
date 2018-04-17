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

#ifndef TEST_TEST_UF_H_
#define TEST_TEST_UF_H_

#include <vector>

#include "test/basic_test.h"

namespace moo {

/**
 * Problem:                UF4
 * Dimension:              30
 */
class UF4Test : public BasicTest{
public:
    UF4Test() {
        name = "UF4";
        parameter.n_objectives = 2;
        parameter.n_variables = 30;
        parameter.n_constraints = 0;

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
    }

    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum = 0.0;
        for (int j = 3; j <= n; j += 2) {
            double yj = x[j - 1] - sin(6.0 * M_PI * x[0] + M_PI * j / n);
            double hy = fabs(yj)/(1.0 + exp(2.0 * fabs(yj)));
            sum += hy;
            ++count;
        }
        return x[0] + 2.0 / count * sum;
    }

    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum = 0.0;
        for (int j = 2; j <= n; j += 2) {
            double yj = x[j - 1] - sin(6.0 * M_PI * x[0] + M_PI * j / n);
            double hy = fabs(yj)/(1.0 + exp(2.0 * fabs(yj)));
            sum += hy;
            ++count;
        }
        return 1.0 - x[0] * x[0] + 2.0 / count * sum;
    }
};

/**
 * Problem:                UF5
 * Dimension:              30
 */
class UF5Test : public BasicTest{
public:
    UF5Test() {
        name = "UF5";
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

    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double nn = 10.0;
        double sum1= (1.0 / (2.0 * nn) + 0.1) *fabs(sin(2.0 * nn * x[0]));

        double sum2 = 0.0;
        for (int j = 3; j <= n; j += 2) {
            double yj = x[j - 1] - sin(6.0 * M_PI * x[0] + M_PI * j / n);
            double hy = 2 * yj * yj - cos(4.0 * M_PI * yj) + 1.0;
            sum2 += hy;
            ++count;
        }

        return x[0] + sum1 + 2.0 / count * sum2;
    }

    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double nn = 10.0;
        double sum1= (1.0 / (2.0 * nn) + 0.1) *fabs(sin(2.0 * nn * x[0]));

        double sum2 = 0.0;
        for (int j = 2; j <= n; j += 2) {
            double yj = x[j - 1] - sin(6.0 * M_PI * x[0] + M_PI * j / n);
            double hy = 2 * yj * yj - cos(4.0 * M_PI * yj) + 1.0;
            sum2 += hy;
            ++count;
        }

        return 1.0 - x[0] + sum1 + 2.0 / count * sum2;
    }
};


/**
 * Problem:                UF6
 * Dimension:              30
 */
class UF6Test : public BasicTest{
public:
    UF6Test() {
        name = "UF6";
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

    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double nn = 10.0;
        double sum1= (1.0 / (2.0 * nn) + 0.1) * sin(2.0 * nn * x[0]);
        if(sum1 < 0.0)
            sum1 = 0.0;

        double sum2 = 0.0;
        double sum3 = 1.0;
        for (int j = 3; j <= n; j += 2) {
            double yj = x[j - 1] - sin(6.0 * M_PI * x[0] + M_PI * j / n);
            sum2 += yj * yj;
            sum3 *= cos(20.0 * yj * M_PI / sqrt(j));
            ++count;
        }

        return x[0] + sum1 + 2.0 / count * (4.0 * sum2 - 2.0 * sum3 + 2.0);
    }

    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double nn = 10.0;
        double sum1= (1.0 / (2.0 * nn) + 0.1) * sin(2.0 * nn * x[0]);
        if(sum1 < 0.0)
            sum1 = 0.0;

        double sum2 = 0.0;
        double sum3 = 1.0;
        for (int j = 2; j <= n; j += 2) {
            double yj = x[j - 1] - sin(6.0 * M_PI * x[0] + M_PI * j / n);
            sum2 += yj * yj;
            sum3 *= cos(20.0 * yj * M_PI / sqrt(j));
            ++count;
        }

        return 1.0 - x[0] + sum1 + 2.0 / count *
                                  (4.0 * sum2 - 2.0 * sum3 + 2.0);
    }
};

/**
 * Problem:                UF7
 * Dimension:              30
 */
class UF7Test : public BasicTest{
public:
    UF7Test() {
        name = "UF7";
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

    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = pow(x[0],0.2);
        double sum2 = 0.0;
        for (int j = 3; j <= n; j += 2) {
            double yj = x[j - 1] - sin(6.0 * M_PI * x[0] + M_PI * j / n);
            sum2 += yj * yj;
            ++count;
        }

        return sum1 + 2.0 / count * sum2;
    }

    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = pow(x[0],0.2);
        double sum2 = 0.0;
        for (int j = 2; j <= n; j += 2) {
            double yj = x[j - 1] - sin(6.0 * M_PI * x[0] + M_PI * j / n);
            sum2 += yj * yj;
            ++count;
        }

        return 1.0 - sum1 + 2.0 / count * sum2;
    }
};

/**
 * Problem:                UF9
 * Dimension:              30
 */
class UF9Test : public BasicTest{
public:
    UF9Test() {
        name = "UF9";
        parameter.n_objectives = 3;
        parameter.n_variables = 30;
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
        double sum2 = 0.0;
        double temp1 = 0.0;
        temp1 = (1.0 + 0.1) * (1.0 - 4.0 * pow((2.0 * x[0] - 1.0),2.0));
        if(temp1 < 0.0)
            temp1 = 0.0;

        sum1 = 0.5 * (temp1 + 2.0 * x[0]) * x[1];
        for (int j = 4; j <= n; j += 3) {
            sum2 += pow(x[j - 1] -
                    2.0 * x[1] * sin(2.0 * M_PI * x[0] + j * M_PI / n),2.0);

            ++count;
        }
        return sum1 + 2.0 / count * sum2;
    }

    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = 0.0;
        double temp1 = 0.0;
        temp1 = (1.0 + 0.1) * (1.0 - 4.0 * pow((2.0 * x[0] - 1.0),2.0));
        if(temp1 < 0.0)
            temp1 = 0.0;

        sum1 = 0.5 * (temp1 - 2.0 * x[0] + 2.0) * x[1];
        double sum2 = 0.0;
        for (int j = 5; j <= n; j += 3) {
            sum2 += pow(x[j - 1] -
                    2.0 * x[1] * sin(2.0 * M_PI * x[0] + j * M_PI / n),2.0);

            ++count;
        }
        return sum1 + 2.0 / count * sum2;
    }

    static double Objective3(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;

        double sum = 0.0;
        for (int j = 3; j <= n; j += 3) {
            sum += pow(x[j - 1] -
                    2.0 * x[1] * sin(2.0 * M_PI * x[0] + j * M_PI / n),2.0);

            ++count;
        }
        return 1.0 - x[1] + 2.0 / count * sum;
    }
};

/**
 * Problem:                UF10
 * Dimension:              30
 */
class UF10Test : public BasicTest{
public:
    UF10Test() {
        name = "UF10";
        parameter.n_objectives = 3;
        parameter.n_variables = 30;
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
        double sum2 = 0.0;
        sum1 = cos(0.5 * x[0] * M_PI) * cos(0.5 * x[1] * M_PI);
        for (int j = 4; j <= n; j += 3) {
            double yj = x[j-1] - 2.0 * x[1] *
                        sin(2.0 * M_PI * x[0] + M_PI * j / n);

            sum2 += 4.0 * yj * yj - cos(8.0 * M_PI * yj) + 1.0;
            ++count;
        }
        return sum1 + 2.0 / count * sum2;
    }

    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        int count = 0;
        double sum1 = 0.0;

        sum1 = cos(0.5 * x[0] * M_PI) * sin(0.5 * x[1] * M_PI);
        double sum2 = 0.0;
        for (int j = 5; j <= n; j += 3) {
            double yj = x[j-1] - 2.0 * x[1] *
                        sin(2.0 * M_PI * x[0] + M_PI * j / n);
            sum2 += 4.0 * yj * yj - cos(8.0 * M_PI * yj) + 1.0;
            ++count;
        }
        return sum1 + 2.0 / count * sum2;
    }

    static double Objective3(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());

        int count = 0;
        double sum1 = 0.0;
        sum1 = sin(0.5 * x[0] * M_PI);
        double sum2 = 0.0;
        for (int j = 3; j <= n; j += 3) {
            double yj = x[j-1] - 2.0 * x[1] *
                        sin(2.0 * M_PI * x[0] + M_PI * j / n);
            sum2 += 4.0 * yj * yj - cos(8.0 * M_PI * yj) + 1.0;
            ++count;
        }
        return sum1 + 2.0 / count * sum2;
    }
};

} // namespace moo

#endif // TEST_TEST_UF_H_
