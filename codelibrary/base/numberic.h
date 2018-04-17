//
// Copyright 2015 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef BASE_NUMBERIC_H_
#define BASE_NUMBERIC_H_

namespace cl {

/**
 * Clamp the value to make sure it is in the range [low, high].
 */
template <typename T>
inline const T Clamp(const T& value, const T& low, const T& high) {
    return value < low ? low : (value > high ? high : value);
}

} // namespace cl

#endif // BASE_NUMBERIC_H_
