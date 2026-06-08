#pragma once

#include "sensor_reading.hpp"
#include "isensor.hpp"
#include <string>

class IMUSensor : public ISensor {
    public:
        IMUSensor();
        SensorReading read() override;
        std::string name() const override;
    private:
        int tick_;
};