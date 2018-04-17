//
// Copyright 2013 Bili Chen. All Rights Reserved.
//
// Author: bilichen.xmu@qq.com (Bili Chen)
//
// This file is part of the Multi-objective Optimization.
//

#ifndef CONSTRAINT_H
#define CONSTRAINT_H
#include <vector>

namespace moo {

/**
 * The definition of constraint of MOO.
 */

typedef double (*Constraint)(const std::vector<double>& variables);

} // namespace moo
#endif // CONSTRAINT_H
