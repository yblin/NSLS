//
// Copyright 2013 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Multi-objective Optimization.
//

#ifndef CORE_PARAMETER_H_
#define CORE_PARAMETER_H_

#include <vector>

namespace moo {

/// Parameter for MOO solver.
struct Parameter {
    int n_variables;  // The number of variables.
    int n_objectives; // The number of objectives.
    int n_constraints;// The number of constraints.

    std::vector<double> min_variables; // The min value of variables.
    std::vector<double> max_variables; // The max value of variables.
};

} // namespace moo

#endif // CORE_PARAMETER_H_
