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

#ifndef SOLVER_UTIL_MUTATION_H_
#define SOLVER_UTIL_MUTATION_H_

#include "core/constants.h"
#include "core/population.h"
#include "solver/util/individual_util.h"
#include "solver/util/population_util.h"
#include "test/basic_test.h"

namespace moo {

/// Mutation for MOEA.
class Mutation {
public:
    /**
     * Polynomial Mutation of an population.
     */
    static void Polynomial(const BasicTest& test, Population* population) {
        // Probability of mutation.
        static const double MUTATION_PROBABILITY = 0.05;
        // Distribution index for mutation.
        static const double MUTATION_DISBUTION_INDEX = 20.0;

        for (size_t i = 0; i < population->size(); ++i) {
            for (int j = 0; j < test.parameter.n_variables; ++j) {
                if (static_cast<double>(rand()) / RAND_MAX >
                    MUTATION_PROBABILITY)
                    continue;

                double v = (*population)[i].variables[j];
                double v_min = test.parameter.min_variables[j];
                double v_max = test.parameter.max_variables[j];
                double delta1 = (v - v_min) / (v_max - v_min);
                double delta2 = (v_max - v) / (v_max - v_min);

                double rnd = static_cast<double>(rand()) / RAND_MAX;
                double mutation_pow = 1.0 / (MUTATION_DISBUTION_INDEX + 1.0);

                double deltaq = 0.0;
                if (rnd <= 0.5) {
                    double tmp = 1.0 - delta1;
                    double val = 2.0 * rnd + (1.0 - 2.0 * rnd) *
                                 std::pow(tmp, MUTATION_DISBUTION_INDEX + 1.0);
                    deltaq = std::pow(val, mutation_pow) - 1.0;
                } else {
                    double tmp = 1.0 - delta2;
                    double val = 2.0 * (1.0 - rnd) + 2.0 * (rnd - 0.5) *
                                 std::pow(tmp, MUTATION_DISBUTION_INDEX + 1.0);
                    deltaq = 1.0 - std::pow(val, mutation_pow);
                }

                v += deltaq * (v_max - v_min);

                if (v < v_min) {
                    v = v_min;
                }
                if (v > v_max) {
                    v = v_max;
                }

                (*population)[i].variables[j] = v;
            }
        }
        PopulationUtil::SetObjectiveValues(test, population);
    }
};

} // namespace moo

#endif // SOLVER_UTIL_MUTATION_H_
