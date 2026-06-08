#pragma once
#include "sensor_reading.hpp"
#include <memory>
#include <mutex>
#include <vector>

class SensorBuffer {
    public:
        explicit SensorBuffer(int capacity);
        void push(std::unique_ptr<SensorReading> reading);
        std::vector<std::unique_ptr<SensorReading> > drain();

        int size() const;
        bool empty() const;

    private:
        int capacity_;
        std::vector<std::unique_ptr<SensorReading> > buffer_;
        mutable std::mutex mtx_;
};