#pragma once

#include <vector>
#include <string>
#include <cstdint>

struct SensorReading {
    uint64_t timestamp; // Timestamp of the reading
    std::vector<float> data; // IMU and Lidar data
    std::string frame_id; // Unique identifier for the sensor
};