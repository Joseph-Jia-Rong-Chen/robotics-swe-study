#pragma once

#include "Isensor.hpp"
#include <string>


class CameraSensor : public ISensor{
    public:
        CameraSensor(const std::string camera_id);
        SensorReading read() override;
        void calibrate() override;
        std::string getName() const override;


};