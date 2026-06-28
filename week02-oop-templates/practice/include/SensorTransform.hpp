// SensorTransform.hpp
#pragma once
#include "Point3D.hpp"

struct SensorTransform {
    double offset_x;   // how far forward the sensor is from robot center
    double offset_y;   // how far left/right
    double offset_z;   // how far up/down

    // Applies this transform to a point — converts sensor frame to robot frame
    Point3D apply(const Point3D& p) const {
        return {p.x + offset_x, p.y + offset_y, p.z + offset_z};
    }
};