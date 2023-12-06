//
// Created by tmai42 on 12/6/23.
//

#ifndef TIME_TRACKER_HPP
#define TIME_TRACKER_HPP
#include <chrono>
#include <iostream>

/**
 * @brief The ScopeTimeTracker class is designed to measure and log the duration of a scope.
 *
 * This class utilizes the RAII (Resource Acquisition Is Initialization) idiom to measure
 * the time spent in a scope. The duration is measured from the point of creation of the
 * object to the point where the object goes out of scope, which triggers the destructor.
 *
 * Example usage:
 * {
 *     ScopeTimeTracker tracker("MyProcess");
 *     // Code to measure goes here
 * }
 * // When the tracker goes out of scope, it logs the duration.
 */
class ScopeTimeTracker {
    using time = std::chrono::time_point<std::chrono::steady_clock>; // Alias for the steady clock time point.

public:
    /**
     * @brief Constructs a ScopeTimeTracker object and starts the timer.
     *
     * @param tracker_name The name of the tracker. This name is used in the logging output
     *                     to identify the scope being measured.
     */
    ScopeTimeTracker(std::string tracker_name): m_start(std::chrono::steady_clock::now()), m_tracker_name(std::move(tracker_name)){}

    /**
     * @brief Destructor for the ScopeTimeTracker.
     *
     * When the ScopeTimeTracker object is destroyed (goes out of scope), this destructor
     * calculates the duration from the point of creation to destruction and logs it.
     * The time duration is logged along with the tracker's name.
     */
    ~ScopeTimeTracker() {
        const auto end = std::chrono::steady_clock::now(); // Marks the end time.

        const std::chrono::duration<double> diff = end - m_start; // Calculates the time difference.
        std::clog << "Process " << m_tracker_name << " is done in " << diff << "\n"; // Logs the time spent in the scope.
    }

private:
    std::string m_tracker_name; // Name of the tracker.
    time m_start;               // Time point representing when the tracker started.
};


#endif