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

#ifndef SOLVER_UTIL_SELECTOR_FARTHEST_CANDIDATE_H_
#define SOLVER_UTIL_SELECTOR_FARTHEST_CANDIDATE_H_

#include "core/population.h"
#include "test/basic_test.h"

namespace moo {

/// Farthest Candidate Method for Selector.
class FarthestCandidate {
public:
    /**
     * Farthest candidate method to select n populations from given population.
     */
    void operator () (const BasicTest& test, const Population& population,
                      int n, Population* selected_population) const {
        assert(selected_population);
        assert(size_t(n) <= population.size());

        if (static_cast<size_t>(n) == population.size()) {
            *selected_population = population;
            return;
        }

        std::vector<int> accepted;
        std::vector<bool> flag(population.size(), false);

        std::vector<double> distance(population.size(), INFINITY);

        for (int m = 0; m < test.parameter.n_objectives; ++m) {
            int min_index = 0, max_index = 0;
            for (size_t i = 1; i < population.size(); ++i) {
                if (population[i].objectives[m] <
                        population[min_index].objectives[m]) {
                    min_index = i;
                }

                if (population[i].objectives[m] >
                    population[max_index].objectives[m]) {
                    max_index = i;
                }
            }

            if (!flag[min_index] && accepted.size() < static_cast<size_t>(n)) {
                accepted.push_back(min_index);
                flag[min_index] = true;
            }
            if (!flag[max_index] && accepted.size() < static_cast<size_t>(n)) {
                accepted.push_back(max_index);
                flag[max_index] = true;
            }
        }

        for (size_t i = 0; i < population.size(); ++i) {
            if (!flag[i]) continue;

            for (size_t j = 0; j < population.size(); ++j) {
                if (flag[j]) continue;
                distance[j] = std::min(distance[j],
                                       IndividualUtil::ObjectiveDistance(
                                           population[i], population[j]));
            }
        }

        int tmp_n = n - accepted.size();
        while (tmp_n--) {
            double max = -1.0;
            int best = -1;
            for (size_t i = 0; i < distance.size(); ++i) {
                if (flag[i]) continue;
                if (distance[i] > max) {
                    max = distance[i];
                    best = i;
                }
            }

            assert(best != -1);

            flag[best] = true;
            accepted.push_back(best);

            // Update the distance.
            for (size_t i = 0; i < distance.size(); ++i) {
                if (flag[i]) continue;
                distance[i] = std::min(distance[i],
                                       IndividualUtil::ObjectiveDistance(
                                            population[i], population[best]));
            }
        }
        assert(accepted.size() == size_t(n));

        // For the case selected_population == population.
        selected_population->resize(n);
        for (int i = 0; i < n; ++i) {
            (*selected_population)[i] = population[accepted[i]];
        }
    }
};

} // namespace moo

#endif // SOLVER_UTIL_SELECTOR_FARTHEST_CANDIDATE_H_
