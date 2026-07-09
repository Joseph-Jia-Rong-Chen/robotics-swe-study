#pragma once

#include <functional>
#include <deque>
#include "sensor_logger/sensor_reading.hpp"



class DataProcessor{
    public:
        DataProcessor(int window_size, 
            double z_score_threshold, 
            std::function<void(SensorReading)> callback);

        void process(const SensorReading& reading);

    private:
        int window_size_;
        double z_score_threshold_;
        std::function<void(SensorReading)> callback_;
        std::deque<float> window_;

        float computeMean() const;
        float computeStdDev(float mean) const;
        float extractScalar(const SensorReading& reading) const;
};