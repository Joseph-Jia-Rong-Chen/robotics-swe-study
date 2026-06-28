#pragma once
#include "SensorReading.hpp"
#include <string>

class ISensor{
    public:
        virtual SensorReading read() = 0;
        virtual void calibrate() = 0;
        virtual std::string getName() const = 0;
        virtual ~ISensor() = default;
    private:
};