//
// Copyright 2012 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Multi-objective Optimization.
//

#ifndef SOLVER_INDIVIDUAL_H_
#define SOLVER_INDIVIDUAL_H_

#include <vector>

#include "core/objective.h"
#include "core/constants.h"

namespace moo {

/// The Individual class for MOGA.
struct Individual {
    std::vector<double> objectives;  // The objective values of Individual.
    std::vector<double> constraints; // The constraint values of Individual.
    std::vector<double> variables;   // The values for each variable.
    int rank;                        // The rank of individual in the fronts.
    double distance;                 // The distance used to evaluate the
                                     // individual.
    int life;                        // The life of individual.
};

} // namespace moo

#endif // SOLVER_INDIVIDUAL_H_
