#pragma once
#include "sensor_reading.hpp"
#include "isensor.hpp"

class LidarSensor : public ISensor {
    public:
        LidarSensor();
        virtual SensorReading read() override;
        virtual std::string name() const override;
    private:
        int tick_;
};