#pragma once
#include "sensor_reading.hpp"

class ISensor {
public:
    virtual ~ISensor() = default;

    // reads current sensor data — returns a reading by value
    virtual SensorReading read() = 0;

    // returns sensor name — "IMU", "LiDAR", etc.
    virtual std::string name() const = 0;
};