//
// Copyright 2012 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_DATE_TIME_DATE_H_
#define UTIL_DATE_TIME_DATE_H_

#include <cassert>

namespace cl {

/// Date.
class Date {
public:
    Date(int year, int month, int day)
        : year_(year), month_(month), day_(day) {
        days_month_[1] = 31;
        days_month_[2] = IsLeapYear() ? 29 : 28;
        days_month_[3] = 31;
        days_month_[4] = 30;
        days_month_[5] = 31;
        days_month_[6] = 30;
        days_month_[7] = 31;
        days_month_[8] = 31;
        days_month_[9] = 30;
        days_month_[10] = 31;
        days_month_[11] = 30;
        days_month_[12] = 31;

        assert(IsValid());

        day_week_ = GetDayWeek(year, month, day);
    }

    bool operator ==(const Date& rhs) const {
        return day_ == rhs.day_ && month_ == rhs.month_ && year_ == rhs.year_;
    }

    bool operator !=(const Date& rhs) const {
        return day_ != rhs.day_ || month_ != rhs.month_ || year_ != rhs.year_;
    }

    Date& operator++() {
        ++day_;
        if (day_ > days_month_[month_]) {
            day_ = 1;
            ++month_;
        }
        if (month_ > 12) {
            ++year_;
            days_month_[2] = IsLeapYear() ? 29 : 28;
            month_ = 1;
        }
        day_week_ = (day_week_ + 1) % 7;

        return *this;
    }

    Date operator++(int /*n*/) {
        Date tmp = *this;
        ++*this;
        return tmp;
    }

    /**
     * Check if the year of date is leap year.
     */
    bool IsLeapYear() const {
        return (year_ % 400 == 0) || (year_ % 4 == 0 && year_ % 100 != 0);
    }

    /**
     * Return the day of the week (0==Sunday, 1==Monday, etc).
     */
    int day_week() const { return day_week_;  }

    int day()   const { return day_;   }
    int month() const { return month_; }
    int year()  const { return year_;  }

private:
    /**
     * Get the day of week by given year month and day.
     * Using the Sakamoto's method, it is accurate for any Gregorian date.
     */
    static int GetDayWeek(int year, int month, int day) {
        static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        year -= month < 3;
        return (year + year / 4 - year / 100 +
                year / 400 + t[month - 1] + day) % 7;
    }

    /**
     * Check the given year, month and day is valid.
     */
    bool IsValid() {
        if (month_ < 1 || month_ > 12) return false;
        return day_ >= 1 && day_ <= days_month_[month_];
    }

    int day_week_;       // The day of week.
    int year_;           // Year from 0.
    int month_;          // Month of year from 1 to 12.
    int day_;            // Day of month from 1 to 31.
    int days_month_[13]; // The day of month.
};

} // namespace cl

#endif // UTIL_DATE_TIME_DATE_H_
