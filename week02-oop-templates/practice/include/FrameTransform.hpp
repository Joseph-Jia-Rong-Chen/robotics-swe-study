#pragma once
#include "SensorTransform.hpp"
#include <vector>
#include <algorithm> 

std::vector<Point3D> transformToRobotFrame(
    const std::vector<Point3D>& input,
    const SensorTransform& tf)
    {
        std::vector<Point3D> result;

        std::transform(input.begin(), input.end(),
            std::back_inserter(result),
            [&tf](const Point3D& p){
                return tf.apply(p);
            });

        return result;
    }