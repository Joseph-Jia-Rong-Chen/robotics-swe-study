#include "sensor_logger/sensorBuffer.hpp"
#include "sensor_logger/sensor_reading.hpp"

SensorBuffer::SensorBuffer(int capacity) : capacity_(capacity){
    buffer_.reserve(capacity_);
}

void SensorBuffer::push(std::unique_ptr<SensorReading> reading){
    std::lock_guard<std::mutex> lock(mtx_);
    if(buffer_.size() < capacity_){
        buffer_.emplace_back(std::move(reading));
    }
    else{
        buffer_.erase(buffer_.begin());
        buffer_.emplace_back(std::move(reading));
    }
}

std::vector<std::unique_ptr<SensorReading>> SensorBuffer::drain(){
    std::lock_guard<std::mutex> lock(mtx_);
    std::vector<std::unique_ptr<SensorReading> > drained_buffer;
    drained_buffer.reserve(buffer_.size());
    for(auto& reading : buffer_){
        drained_buffer.emplace_back(std::move(reading));
    }
    buffer_.clear();
    return drained_buffer;
}

int SensorBuffer::size() const{
    std::lock_guard<std::mutex> lock(mtx_);
    return buffer_.size();
}

bool SensorBuffer::empty() const{
    std::lock_guard<std::mutex> lock(mtx_);
    return buffer_.empty();
}