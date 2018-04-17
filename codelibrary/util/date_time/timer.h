//
// Copyright 2012 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_DATE_TIME_TIMER_H_
#define UTIL_DATE_TIME_TIMER_H_

#include <cstdint>
#include <ctime>

namespace cl {

/// A timer for calculating user's process time.
class Timer {
public:
    Timer()
        : running_(false), elapsed_(0), started_(0) {}

    /**
     * Reset the timer.
     */
    void Reset() {
        elapsed_ = 0;
        if (running_) {
            started_ = clock();
        } else {
            started_ = 0;
        }
    }

    /**
     * Timer start.
     */
    void Start() {
        running_ = true;
        started_ = clock(); // clock() is faster than std::chrono.
    }

    /**
     * Timer stop.
     */
    void Stop() {
        if (running_) {
            running_ = false;
            elapsed_ += clock() - started_;
            started_ = 0;
        }
    }

    /**
     * Return the elapsed time.
     */
    double elapsed() const {
        return static_cast<double>(elapsed_) / CLOCKS_PER_SEC;
    }

private:
    bool running_;    // True if timer is running.
    int64_t elapsed_; // The elapsed time.
    int64_t started_; // The time of started.
};

} // namespace cl

#endif // UTIL_DATE_TIME_TIMER_H_
