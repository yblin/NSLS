//
// Copyright 2013 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Multi-objective Optimization.
//

#ifndef CORE_OBJECTIVES_H_
#define CORE_OBJECTIVES_H_

#include <vector>

namespace moo {

/**
 * The definition of objective of MOO.
 */
typedef double (*Objective)(const std::vector<double>& variables);

typedef double (*Constraint)(const std::vector<double>& variables);

} // namespace moo

#endif // CORE_OBJECTIVES_H_
