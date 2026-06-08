#include <cmath>
#include <chrono>
#include <random>

#include "sensor_logger/lidar_sensor.hpp"
#include "sensor_logger/sensor_reading.hpp"


LidarSensor::LidarSensor() : tick_(0) {
}

SensorReading LidarSensor::read() {
    SensorReading reading;

    // call this sensor Lidar
    reading.frame_id = "Lidar_";

    std::random_device rd;              
    std::mt19937 gen(rd()); 

    // Generate the current timestamp in nanoseconds
    reading.timestamp = static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
        ).count()
    );

    // Simulate Lidar data (a 360-degree scan with 360 points)
    reading.data.resize(360);
    std::uniform_real_distribution<float> dis(0.0, 100.0);
    for (auto& value : reading.data) {
        value = dis(gen);
    }
    
    return reading;
}

std::string LidarSensor::name() const {
    return "Lidar";
}