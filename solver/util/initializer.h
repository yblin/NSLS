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

#ifndef SOLVER_UTIL_INITIALIZER_H_
#define SOLVER_UTIL_INITIALIZER_H_

#include <ctime>
#include <random>

#include "core/population.h"
#include "solver/util/population_util.h"
#include "test/basic_test.h"

namespace moo {

/// Population Initializer.
class Initializer {
public:
    /**
     * Random initialize the population.
     */
    static void Random(const BasicTest& test, int size_population,
                       Population* population) {
        assert(population);

        unsigned int seed = time(NULL);

        srand(seed);
        std::mt19937 mt_random(seed);
        std::uniform_real_distribution<double> distribution(0, 1);

        population->resize(size_population);

        for (int i = 0; i < size_population; ++i) {
            (*population)[i].distance = 0.0;
            (*population)[i].rank = 0;
            (*population)[i].life = 0;

            (*population)[i].variables.resize(test.parameter.n_variables);
            for (int j = 0; j < test.parameter.n_variables; ++j) {
                double t = distribution(mt_random);
                (*population)[i].variables[j] =
                        t * (test.parameter.max_variables[j] -
                             test.parameter.min_variables[j]) +
                        test.parameter.min_variables[j];
            }

            (*population)[i].objectives.resize(test.parameter.n_objectives);
            (*population)[i].constraints.resize(test.parameter.n_constraints);
        }
        PopulationUtil::SetObjectiveValues(test, population);
    }
};

} // namespace moo

#endif // SOLVER_UTIL_CROSSOVER_H_
