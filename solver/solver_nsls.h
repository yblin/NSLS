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

#ifndef SOLVER_SOLVER_NSLS_H_
#define SOLVER_SOLVER_NSLS_H_

#include <random>

#include "solver/basic_solver.h"
#include "solver/util/initializer.h"
#include "solver/util/selector.h"
#include "solver/util/updater.h"

namespace moo {

/// NSLS MOO Solver.
/**
 * Reference:
 *   Chen B L, Zeng W H, Lin Y B, Zhang D F. A new local serach based
 *   multiobjectives optimization algorithm. 2014.
 */
template <class Selector = FarthestCandidate, class Updater = NSLSUpdater>
class SolverNSLS : public BasicSolver {
public:
    SolverNSLS() : BasicSolver() {}

    virtual ~SolverNSLS() {}

    /**
     * Initialize the solver.
     */
    void Initialize(const BasicTest& test, int size_population,
                    Population* population) {
        assert(size_population > 0);

        test_ = test;

        size_population_ = (size_population / 4 +
                           (size_population % 4 != 0)) * 4;

        Initializer::Random(test_, size_population_, population);

        n_generation_ = 0;
    }

    /**
     * Single step running the solver.
     */
    void SingleStep(Population* population) {
        if (population->empty()) {
            return;
        }

        Population new_population = *population;
        Updater()(test_, &new_population);

        Population union_population = *population;
        union_population.insert(union_population.end(), new_population.begin(),
                                new_population.end());

        NonDominatedSortingSelector<Selector>::
                Select(test_, union_population, size_population_, population);

        ++n_generation_;
    }
};

} // namespace moo

#endif // SOLVER_SOLVER_NSLS_H_
