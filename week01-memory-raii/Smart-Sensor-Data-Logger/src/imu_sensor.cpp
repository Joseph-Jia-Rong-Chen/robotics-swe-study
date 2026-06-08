#include <cmath>
#include <chrono>
#include <random>

#include "sensor_logger/imu_sensor.hpp"
#include "sensor_logger/sensor_reading.hpp"

IMUSensor::IMUSensor() : tick_(0) {
}

SensorReading IMUSensor::read() {
    SensorReading reading;

    // call this sensor IMU
    reading.frame_id = "IMU_";

    std::random_device rd;              
    std::mt19937 gen(rd()); 

    // Generate the current timestamp in nanoseconds
    reading.timestamp = static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
        ).count()
    );

    // Simulate IMU data (a 3-axis accelerometer and a 3-axis gyroscope)
    reading.data.resize(6);
    std::uniform_real_distribution<float> dis(-10.0, 10.0);
    for (auto& value : reading.data) {
        value = dis(gen);
    }
    
    return reading;
}

std::string IMUSensor::name() const {
    return "IMU";
}