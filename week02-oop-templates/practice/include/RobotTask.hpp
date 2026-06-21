// RobotTask.hpp
#pragma once
#include <string>

struct RobotTask {
    int         priority;    // higher number = higher priority
    std::string name;
    std::string description;

    // std::priority_queue needs operator< to compare elements
    // when a < b, b has higher priority — so higher number wins

    bool operator<(const RobotTask& rhs) const{
        return priority < rhs.priority;
    }

    // bool operator<(const RobotTask& other) const {
    //     return priority < other.priority;
    // }
};