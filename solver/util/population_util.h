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

#ifndef SOLVER_UTIL_POPULATION_UTIL_H_
#define SOLVER_UTIL_POPULATION_UTIL_H_

#include <cfloat>

#include "codelibrary/util/common/sequence.h"

#include "test/basic_test.h"
#include "solver/util/individual_util.h"
#include "core/population.h"

namespace moo {

/// Util for population.
class PopulationUtil {
public:
    /**
     * Set the objectives' values for population.
     */
    static void SetObjectiveValues(const BasicTest& test,
                                   Population* population) {
        assert(population);

        for (size_t i = 0; i < population->size(); ++i) {
            IndividualUtil::SetObjectives(test.objectives, &(*population)[i]);
        }
    }

    /**
     * Set the constraints' values for population.
     */
    static void SetConstraintValues(const BasicTest& test,
                                    Population* population) {
        assert(population);

        for (size_t i = 0; i < population->size(); ++i) {
            for (int j = 0; j < test.parameter.n_objectives; ++j) {
                (*population)[i].objectives[j] =
                        (test.constraints[j])((*population)[i].variables);
            }
        }
    }

    /**
     * Opposite the population.
     */
    static void Opposite(const BasicTest& test, Population* population) {
        assert(population);

        for (size_t i = 0; i < population->size(); ++i) {
            for (int j = 0; j < test.parameter.n_variables; ++j) {
                double max = test.parameter.max_variables[j];
                double min = test.parameter.min_variables[j];
                (*population)[i].variables[j] =
                        min + max - (*population)[i].variables[j];
            }
        }
        PopulationUtil::SetObjectiveValues(test, population);
    }

    /**
     * Set the crowding distance for each individual in population.
     */
    static void SetCrowdingDistance(const BasicTest& test,
                                    Population* population) {
        for (size_t i = 0; i < population->size(); ++i) {
            (*population)[i].distance = 0.0;
        }

        if (population->size() > 2) {
            for (int m = 0; m < test.parameter.n_objectives; ++m) {
                // Sorting population by m-th objective value.
                std::vector<double> objectives(population->size());
                for (size_t i = 0; i < population->size(); ++i) {
                    objectives[i] = (*population)[i].objectives[m];
                }

                cl::Sequence<double> seq(objectives);

                for (size_t i = 1; i < population->size() - 1; ++i) {
                    double delt = objectives[seq[i + 1]] -
                                  objectives[seq[i - 1]];
                    (*population)[seq[i]].distance += delt;
                }
            }
        }

        // Set the distance of boundary individualto INFINITY.
        for (int m = 0; m < test.parameter.n_objectives; ++m) {
            int min_index = 0;
            for (size_t i = 1; i < population->size(); ++i) {
                if ((*population)[i].objectives[m] <
                    (*population)[min_index].objectives[m]) {
                    min_index = i;
                }
            }
            (*population)[min_index].distance = INFINITY;
        }
    }
};

} // namespace moo

#endif // SOLVER_UTIL_POPULATION_UTIL_H_
