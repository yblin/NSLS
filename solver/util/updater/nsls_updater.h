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

#ifndef SOLVER_UPDATER_NSLS_UPDATER_H_
#define SOLVER_UPDATER_NSLS_UPDATER_H_

#include <random>

#include "core/population.h"
#include "solver/util/individual_util.h"
#include "test/basic_test.h"

#include "solver/util/population_util.h"

namespace moo {

/// NSLS updater.
class NSLSUpdater {
public:
    void operator() (const BasicTest& test, Population* population) const {
        assert(population);

        unsigned int seed = time(NULL);
        std::normal_distribution<double> normal_distribution(0.5, 0.1);
        std::mt19937 mt_random(seed);

        for (size_t i = 0; i < population->size(); ++i) {
            for (int j = 0; j < test.parameter.n_variables; ++j) {
                double v_min = test.parameter.min_variables[j];
                double v_max = test.parameter.max_variables[j];

                Individual a1 = (*population)[i];
                Individual a2 = (*population)[i];
                const Individual& b = (*population)[i];

                double v = b.variables[j];

                int rnd1 = rand() % population->size();
                int rnd2 = rand() % population->size();

                double rnd3 = normal_distribution(mt_random);

                double v1 = v + rnd3 * ((*population)[rnd1].variables[j] -
                                        (*population)[rnd2].variables[j]);
                double v2 = v - rnd3 * ((*population)[rnd1].variables[j] -
                                        (*population)[rnd2].variables[j]);

                if (v1 < v_min) {
                    v1 = v_min;
                }
                if (v1 > v_max) {
                    v1 = v_max;
                }
                if (v2 < v_min) {
                    v2 = v_min;
                }
                if (v2 > v_max) {
                    v2 = v_max;
                }

                a1.variables[j] = v1;
                a2.variables[j] = v2;
                IndividualUtil::SetObjectives(test.objectives, &a1);
                IndividualUtil::SetObjectives(test.objectives, &a2);

                int t1 = IndividualUtil::Dominance(a1, b);
                int t2 = IndividualUtil::Dominance(a2, b);

                if (t1 == 1 && t2 == 1) {
                    (*population)[i] = rand() % 2 ? a1 : a2;
                } else if (t1 == 1) {
                    (*population)[i] = a1;
                } else if (t2 == 1) {
                    (*population)[i] = a2;
                } else if (t1 == 0 && t2 == -1) {
                    (*population)[i] = a1;
                } else if (t2 == 0 && t1 == -1) {
                    (*population)[i] = a2;
                } else if (t1 == 0 && t2 == 0) {
                    (*population)[i] = rand() % 2 ? a1 : a2;
                }
            }
        }
    }
};

} // namespace moo

#endif // SOLVER_UPDATER_NSLS_UPDATER_H_
