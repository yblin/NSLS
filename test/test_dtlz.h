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

#ifndef TEST_DTLZ_H
#define TEST_DTLZ_H

#include <vector>

#include "test/basic_test.h"

namespace moo {

/**
 * Problem:                DTLZ1
 * Dimension:              7
 */
class DTLZ1_3DTest: public BasicTest{
    static const int K = 5;
public:
    DTLZ1_3DTest() {
        name = "DTLZ1";
        parameter.n_objectives = 3;
        parameter.n_variables = K + parameter.n_objectives - 1;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        for (int i = 0; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = 0.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
        objectives.push_back(Objective3);
    }

    static double Objective1(const std::vector<double>& x) {
        //int n = static_cast<int>(x.size());
        double result = 0.0;
        double gx = GX(x);

        result = 0.5 * x[0] * x[1] * (1.0 + gx);
        return result;
    }

    static double Objective2(const std::vector<double>& x) {
        //int n = static_cast<int>(x.size());
        double result = 0.0;
        double gx = GX(x);

        result = 0.5 * x[0] * (1.0 - x[1]) * (1.0 + gx);
        return result;
    }

    static double Objective3(const std::vector<double>& x) {
        //int n = static_cast<int>(x.size());
        double result = 0.0;

        double gx = GX(x);

        result = 0.5 * (1.0 - x[0]) * (1.0 + gx);
        return result;
    }
    private:
    static double GX(const std::vector<double>& x) {
        double gx_2 = 0.0;
        int n = static_cast<int>(x.size());
        for (int i = n - K; i < n; ++i) {
            gx_2 += (x[i] - 0.5) * (x[i] - 0.5) -
                    cos(20.0 * M_PI * (x[i] - 0.5));
        }
        double gx = 100.0 * (K + gx_2);
        return gx;
    }
};

/**
 * Problem:                DTLZ2
 * Dimension:              10
 */

class DTLZ2_3DTest : public BasicTest{
    static const int K = 10;
public:
    DTLZ2_3DTest() {
        name = "DTLZ2";
        parameter.n_objectives = 3;
        parameter.n_variables = K + parameter.n_objectives - 1;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        for (int i = 0; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = 0.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
        objectives.push_back(Objective3);
    }

    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double result = 0.0;
        double gx = 0.0;
        for(int i = n - K; i < n; ++i){
            gx += (x[i] - 0.5) * (x[i] - 0.5);
        }

        result = (1.0 + gx) * cos(x[0] * M_PI / 2.0) * cos(x[1] * M_PI / 2.0);
        return result;
    }

    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double result = 0.0;
        double gx = 0.0;
        for(int i = n - K; i < n; ++i){
            gx += (x[i] - 0.5) * (x[i] - 0.5);
        }

        result = (1.0 + gx) * cos(x[0] * M_PI / 2.0) * sin(x[1] * M_PI / 2.0);
        return result;
    }

    static double Objective3(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double result = 0.0;
        double gx = 0.0;
        for(int i = n - K; i < n; ++i){
            gx += (x[i] - 0.5) * (x[i] - 0.5);
        }

        result = (1.0 + gx) * sin(x[0] * M_PI / 2.0);
        return result;
    }
};

/**
 * Problem:                DTLZ3
 * Dimension:              10
 */
class DTLZ3_3DTest : public BasicTest{
    static const int K = 10;
public:
    DTLZ3_3DTest() {
        name = "DTLZ3";
        parameter.n_objectives = 3;
        parameter.n_variables = K + parameter.n_objectives - 1;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        for (int i = 0; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = 0.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
        objectives.push_back(Objective3);
    }

    static double Objective1(const std::vector<double>& x) {
        double result = 0.0;
        double gx = GX(x);

        result = (1.0 + gx) * cos(x[0] * M_PI * 0.5) * cos(x[1] * M_PI * 0.5);
        return result;
    }

    static double Objective2(const std::vector<double>& x) {
        double result = 0.0;
        double gx = GX(x);

        result = (1.0 + gx) * cos(x[0] * M_PI * 0.5) * sin(x[1] * M_PI * 0.5);
        return result;
    }

    static double Objective3(const std::vector<double>& x) {
        double result = 0.0;
        double gx = GX(x);

        result = (1.0 + gx) * sin(x[0] * M_PI * 0.5);
        return result;
    }

private:
    static double GX(const std::vector<double>& x) {
        double gx_2 = 0.0;
        int n = static_cast<int>(x.size());
        for (int i = n - K; i < n; ++i) {
            gx_2 += (x[i] - 0.5) * (x[i] - 0.5) -
                    cos(20.0 * M_PI * (x[i] - 0.5));
        }
        double gx = 100.0 * (K + gx_2);
        return gx;
    }
};

/**
 * Problem:                DTLZ4
 * Dimension:              10
 */
class DTLZ4_3DTest : public BasicTest{
public:
    DTLZ4_3DTest() {
        name = "DTLZ4";
        parameter.n_objectives = 3;
        parameter.n_variables = 3 + 10 - 1;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        for (int i = 0; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = 0.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
        objectives.push_back(Objective3);
    }

    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double result = 0.0;
        double gx = 0.0;
        for(int i = 3; i < n; ++i){
            gx += (x[i] - 0.5) * (x[i] - 0.5);
        }

        result = (1.0 + gx) * cos(pow(x[0],100) * M_PI / 2.0) *
                 cos(pow(x[1],100) * M_PI / 2.0);
        return result;
    }

    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double result = 0.0;
        double gx = 0.0;
        for(int i = 3; i < n; ++i){
            gx += (x[i] - 0.5) * (x[i] - 0.5);
        }

        result = (1.0 + gx) * cos(pow(x[0],100) * M_PI / 2.0) *
                 sin(pow(x[1],100) * M_PI / 2.0);
        return result;
    }

    static double Objective3(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double result = 0.0;
        double gx = 0.0;
        for(int i = 3; i < n; ++i){
            gx += (x[i] - 0.5) * (x[i] - 0.5);
        }

        result = (1.0 + gx) * sin(pow(x[0],100) * M_PI / 2.0);
        return result;
    }
};

/**
 * Problem:                DTLZ5
 * Dimension:              7
 */
class DTLZ5_3DTest : public BasicTest{
    static const int K = 10;
public:
    DTLZ5_3DTest() {
        name = "DTLZ5";
        parameter.n_objectives = 3;
        parameter.n_variables = K + parameter.n_objectives - 1;
        parameter.n_constraints = 0;

        parameter.min_variables.resize(parameter.n_variables);
        parameter.max_variables.resize(parameter.n_variables);
        for (int i = 0; i < parameter.n_variables; ++i) {
            parameter.min_variables[i] = 0.0;
            parameter.max_variables[i] = 1.0;
        }

        objectives.push_back(Objective1);
        objectives.push_back(Objective2);
        objectives.push_back(Objective3);
    }

    static double Objective1(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double result = 0.0;
        double gx = 0.0;
        for(int i = n - K; i < n; ++i){
            gx += (x[i] - 0.5) * (x[i] - 0.5);
        }
        double seta0 = M_PI / (4.0 * (1.0 + gx)) * (1.0 + 2.0 * gx * x[0]);
        double seta1 = M_PI / (4.0 * (1.0 + gx)) * (1.0 + 2.0 * gx * x[1]);

        result = (1.0 + gx) * cos(seta0 * M_PI / 2.0) *
                  cos(seta1 * M_PI / 2.0);
        return result;
    }

    static double Objective2(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double result = 0.0;
        double gx = 0.0;
        for(int i = n - K; i < n; ++i){
            gx += (x[i] - 0.5) * (x[i] - 0.5);
        }
        double seta0 = M_PI / (4.0 * (1.0 + gx)) * (1.0 + 2.0 * gx * x[0]);
        double seta1 = M_PI / (4.0 * (1.0 + gx)) * (1.0 + 2.0 * gx * x[1]);

        result = (1.0 + gx) * cos(seta0 * M_PI / 2.0) *
                  sin(seta1 * M_PI / 2.0);
        return result;
    }

    static double Objective3(const std::vector<double>& x) {
        int n = static_cast<int>(x.size());
        double result = 0.0;
        double gx = 0.0;
        for(int i = n - K; i < n; ++i){
            gx += (x[i] - 0.5) * (x[i] - 0.5);
        }

        double seta0 = M_PI / (4.0 * (1.0 + gx)) * (1.0 + 2.0 * gx * x[0]);
        result = (1.0 + gx) * sin(seta0 * M_PI / 2.0);
        return result;
    }
};

} // namespace moo


#endif // TEST_DTLZ_H
