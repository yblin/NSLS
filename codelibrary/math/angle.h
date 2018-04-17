//
// Copyright 2012 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef MATH_ANGLE_H_
#define MATH_ANGLE_H_

#include "codelibrary/base/constants.h"
#include "codelibrary/math/vector.h"

namespace cl {
namespace angle {

/**
 * Convert degree angle to radian angle.
 */
inline double DegreeToRadian(double degree) {
    return degree * PI / 180.0;
}

/**
 * Convert radian angle to degree angle.
 */
inline double RadianToDegree(double radian) {
    return radian * 180.0 / PI;
}

/**
 * Get the radian angle of 2d vector.
 */
template <typename T>
inline double Radian(const Vector2D<T>& v) {
    double radian = std::atan2(v.y, v.x);
    return radian < 0.0 ? radian + PI + PI : radian;
}

/**
 * Get the degree angle of 2d vector.
 */
template <typename T>
inline double Degree(const Vector2D<T>& v) {
    return RadianToDegree(Radian(v));
}

/**
 * Get the radian angle between two vectors.
 */
template <class Vector>
double Radian(const Vector& v1, const Vector& v2) {
    double l1 = v1.length();
    double l2 = v2.length();

    if (l1 == 0.0 || l2 == 0.0) return 0.0;

    return std::acos(DotProduct(v1, v2) / l1 / l2);
}

/**
 * Get the degree between two two vectors.
 */
template <typename Vector>
double Degree(const Vector& v1, const Vector& v2) {
    return RadianToDegree(Radian(v1, v2));
}

} // namespace angle
} // namespace cl

#endif // MATH_ANGLE_H_
