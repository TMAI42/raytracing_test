//
// Created by tmai42 on 12/6/23.
//

#ifndef TIME_TRACKER_HPP
#define TIME_TRACKER_HPP
#include <chrono>
#include <iostream>

class ScopeTimeTracker {
    using time = std::chrono::time_point<std::chrono::steady_clock>;

public:
    ScopeTimeTracker(std::string tracker_name): m_start(std::chrono::steady_clock::now()), m_tracker_name(std::move(tracker_name)){}
    ~ScopeTimeTracker() {
        const auto end = std::chrono::steady_clock::now();

        const std::chrono::duration<double> diff = end - m_start;
        std::clog << "Process " << m_tracker_name << " is done in " << diff << "\n";
    }

private:
    std::string m_tracker_name;
    time m_start;
};

#endif