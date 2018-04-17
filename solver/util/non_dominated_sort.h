//
// Copyright 2013 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Multi-objective Optimization.
//

#ifndef SOLVER_UTIL_NON_DOMINATED_SORT_H_
#define SOLVER_UTIL_NON_DOMINATED_SORT_H_

#include <queue>

#include "codelibrary/util/list/adjacency_list.h"

#include "core/population.h"
#include "solver/util/individual_util.h"

namespace moo {

/**
 * Perfrom non-dominated sort for given population.
 */
static void NonDominatedSort(const Population& population,
                             std::vector<Population>* fronts) {
    // The indegrees of every individuals in the adjacency list.
    std::vector<int> indegrees(population.size(), 0);

    cl::AdjacencyList list(population.size());

    for (size_t i = 0; i < population.size(); ++i) {
        for (size_t j = i + 1; j < population.size(); ++j) {
            if (i == j) continue;
            int dominance = IndividualUtil::Dominance(population[i],
                                                      population[j]);
            if (dominance == 1) {
                list.InsertOneWayEdge(i, j);
                ++indegrees[j];
            } else if (dominance == -1) {
                list.InsertOneWayEdge(j, i);
                ++indegrees[i];
            }
        }
    }

    // Topological sorting to get every non-dominated fronts.
    std::vector<int> rank(population.size(), 0); // The rank of individuals.

    std::queue<int> queue;
    for (size_t i = 0; i < indegrees.size(); ++i) {
        if (indegrees[i] == 0) {
            queue.push(i);
        }
    }

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();

        for (const cl::AdjacencyList::Edge& e : list.edge_list(node)) {
            --indegrees[e.target()];
            if (indegrees[e.target()] == 0) {
                queue.push(e.target());
                rank[e.target()] = rank[e.source()] + 1;
            }
        }
    }

    int max_rank = 0;
    for (size_t i = 0; i < population.size(); ++i) {
        max_rank = std::max(rank[i], max_rank);
    }

    fronts->resize(max_rank + 1);
    for (size_t i = 0; i < population.size(); ++i) {
        fronts->at(rank[i]).push_back(population[i]);
    }
}

} // namespace moo

#endif // SOLVER_UTIL_NON_DOMINATED_SORTING_H_
