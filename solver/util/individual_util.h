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

#ifndef SOLVER_UTIL_INDIVIDUAL_UTIL_H_
#define SOLVER_UTIL_INDIVIDUAL_UTIL_H_

#include <cmath>

#include "core/individual.h"
#include "core/objective.h"

namespace moo {

/// Util for individual.
class IndividualUtil {
public:
    /**
     * Set the objectives of individual.
     */
    static void SetObjectives(const std::vector<Objective>& objectives,
                               Individual* individual) {
        assert(individual->objectives.size() == objectives.size());

        for (size_t i = 0; i < objectives.size(); ++i) {
            individual->objectives[i] = (objectives[i])(individual->variables);
        }
    }

    /**
     * Set the constraints of individual.
     */
    static void SetConstraints(const std::vector<Constraint>& constraints,
                               Individual* individual) {
        assert(individual->constraints.size() == constraints.size());

        for (size_t i = 0; i < constraints.size(); ++i) {
            individual->constraints[i] =
                    (constraints[i])(individual->variables);
        }
    }

    /**
     * Get the dominance between two individuals.
     * @return 0, if both a and b are non-dominated
     *         1, if a dominates b
     *        -1, if b dominates a.
     */
    static int Dominance(const Individual& a, const Individual& b) {
        bool flag1 = false, flag2 = false;

        for (size_t i = 0; i < a.objectives.size(); ++i) {
            if (a.objectives[i] < b.objectives[i]) {
                flag1 = true;
            } else if (a.objectives[i] > b.objectives[i]) {
                flag2 = true;
            }
        }

        if (flag1 && !flag2) {
            return 1;
        } else if (!flag1 && flag2) {
            return -1;
        } else {
            return 0;
        }
    }

    /**
     * Compare two individuals by distance.
     */
    static bool CompareByDistance(const Individual& a, const Individual& b) {
        return a.distance > b.distance;
    }

    /**
     * Compare two individuals by rank, objectives and distance.
     */
    static bool Compare(const Individual& a, const Individual& b) {
        if (a.rank != b.rank) {
            return a.rank < b.rank;
        }

        int dominance = Dominance(a, b);
        if (dominance != 0) {
            return dominance > 0;
        } else {
            if (a.distance > b.distance) {
                return true;
            } else if (a.distance < b.distance) {
                return false;
            }
            return true;
        }
    }

    /**
     * The objective distance between two individuals.
     */
    static double ObjectiveDistance(const Individual& a, const Individual& b) {
        double dis = 0.0;
        for (size_t i = 0; i < a.objectives.size(); ++i) {
            dis += (a.objectives[i] - b.objectives[i]) *
                   (a.objectives[i] - b.objectives[i]);
        }
        return std::sqrt(dis);
    }
};

} // namespace moo

#endif // SOLVER_UTIL_INDIVIDUAL_UTIL_H_
