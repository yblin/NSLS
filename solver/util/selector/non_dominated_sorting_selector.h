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

#ifndef SOLVER_UTIL_SELECTOR_NON_DOMINATED_SORTING_SELECTOR_H_
#define SOLVER_UTIL_SELECTOR_NON_DOMINATED_SORTING_SELECTOR_H_

#include "core/population.h"
#include "solver/util/non_dominated_sort.h"
#include "test/basic_test.h"

namespace moo {

// Non-dominated Sorting based Selector.
template <class Selector>
class NonDominatedSortingSelector {
public:
    /**
     * Given a multi-objective optimization problem, this function select n
     * individuals as the new population from the current population.
     */
    static void Select(const BasicTest& test, const Population& population,
                       int n, Population* selected_population) {
        assert(selected_population);

        selected_population->resize(n);

        std::vector<Population> fronts;
        NonDominatedSort(population, &fronts);

        int k = 0;
        size_t cur_front = 0;

        for (cur_front = 0; cur_front < fronts.size(); ++cur_front) {
            if (k + static_cast<int>(fronts[cur_front].size()) > n) {
                break;
            }

            for (size_t j = 0; j < fronts[cur_front].size(); ++j) {
                (*selected_population)[k] = fronts[cur_front][j];
                (*selected_population)[k].rank = cur_front;
                ++k;
            }
        }

        if (k < n) {
            Population tmp;
            Selector()(test, fronts[cur_front], n - k, &tmp);
            assert(tmp.size() == static_cast<std::size_t>(n - k));

            for (size_t j = 0; j < tmp.size(); ++j) {
                (*selected_population)[k] = tmp[j];
                (*selected_population)[k].rank = cur_front;
                ++k;
            }
        }

        assert(selected_population->size() == static_cast<std::size_t>(n));
    }
};

} // namespace moo

#endif // SOLVER_UTIL_SELECTOR_NON_DOMINATED_SORTING_SELECTOR_H_

