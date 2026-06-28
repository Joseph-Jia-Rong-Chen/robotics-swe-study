#pragma once
#include "SensorTransform.hpp"
#include <vector>
#include <algorithm> 

std::vector<Point3D> transformToRobotFrame(
    const std::vector<Point3D>& input,
    const SensorTransform& transform)
    {
        std::vector<Point3D> result;

        std::transform(input.begin(), input.end(),
            std::back_inserter(result),
            [&transform](const Point3D& p){
                return transform.apply(p);
            });

        return result;
    }