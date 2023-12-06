//
// Created by tmai42 on 12/7/23.
//

#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <concepts>
#include <limits>

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

/**
 * @brief The Interval class represents a mathematical interval for arithmetic types.
 *
 * This template class provides a generic representation of an interval, defined by its minimum and
 * maximum values. It supports both integral and floating-point types as specified by the arithmetic
 * concept. The class offers functionality to check if a value lies within or surrounds the interval
 * and provides static methods to create universal and empty intervals.
 *
 * @tparam T The arithmetic type of the interval. Must be either an integral or a floating-point type.
 */
template<typename T> requires arithmetic<T>
struct Interval {

    /**
     * @brief Constructs an interval with specified minimum and maximum values.
     *
     * @param min The minimum value of the interval.
     * @param max The maximum value of the interval.
     */
    Interval(T min, T max) : m_min(min), m_max(max) {}

    /**
     * @brief Checks if a value is contained within the interval [min, max].
     *
     * @param x The value to check.
     * @return True if x is within the interval, false otherwise.
     */
    inline bool contains(T x) const {
        return m_min <= x && x <= m_max;
    }

    /**
     * @brief Checks if a value is surrounded by the interval (min, max).
     *
     * @param x The value to check.
     * @return True if x is inside the bounds of the interval but not equal to min or max, false otherwise.
     */
    inline bool surrounds(T x) const {
        return m_min < x && x < m_max;
    }

    /**
     * @brief Creates a universal interval.
     *
     * For integral types, the interval spans from the minimum to the maximum value of the type.
     * For floating-point types, it spans from negative to positive infinity.
     *
     * @return An interval representing the entire range of the type T.
     */
    static Interval universal() {
        if constexpr (std::integral<T>) {
            return Interval(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        } else if constexpr (std::floating_point<T>) {
            return Interval(-std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
        }
    }

    /**
     * @brief Creates an empty interval.
     *
     * For integral types, the interval is defined with max as the lower bound and min as the upper bound.
     * For floating-point types, it is defined from positive to negative infinity.
     *
     * @return An interval that cannot contain any value of type T.
     */
    static Interval empty() {
        if constexpr (std::integral<T>) {
            return Interval(std::numeric_limits<T>::max(), std::numeric_limits<T>::min());
        } else if constexpr (std::floating_point<T>) {
            return Interval(std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity());
        }
    }

    T m_min; ///< The minimum value of the interval.
    T m_max; ///< The maximum value of the interval.
};


#endif //INTERVAL_HPP
