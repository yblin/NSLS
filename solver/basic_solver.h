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

#ifndef SOLVER_BASIC_SOLVER_H_
#define SOLVER_BASIC_SOLVER_H_

#include "core/population.h"
#include "test/basic_test.h"

namespace moo {

/// Basic MOO Solver.
class BasicSolver {
public:
    BasicSolver() {}

    virtual ~BasicSolver() {}

    /**
     * Initialize the solver.
     */
    virtual void Initialize(const BasicTest& test, int size_population,
                            Population* population) = 0;

    /**
     * Single step running the solver.
     */
    virtual void SingleStep(Population* population) = 0;

    int size_population() const { return size_population_; }
    int n_generation()    const { return n_generation_;    }

protected:
    int size_population_; // The size of population.
    BasicTest test_;      // The test.
    int n_generation_;    // The number of generation.
};

} // namespace moo

#endif // SOLVER_SOLVER_H_
