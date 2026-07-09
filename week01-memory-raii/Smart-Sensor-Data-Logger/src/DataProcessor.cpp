#include "sensor_logger/DataProcessor.hpp"
#include "sensor_logger/sensor_reading.hpp"
#include <cmath>

DataProcessor::DataProcessor(int window_size, 
            double z_score_threshold, 
            std::function<void(SensorReading)> callback):
            window_size_(window_size), z_score_threshold_(z_score_threshold),
            callback_(std::move(callback)){};

void DataProcessor::process(const SensorReading& reading){
    
    float scalar = extractScalar(reading);
    
    if(window_.size() >= window_size_){
        window_.pop_front();
    }
    else{
        window_.push_back(scalar);
        float mean = computeMean();
        float stdev = computeStdDev(mean);

        if(stdev > 1e-6f){
            float z_score = std::abs(scalar - mean) / stdev;
            if(z_score > z_score_threshold_){
                return; // outlier - reject and do not update window
            }
        }

        window_.pop_front();
        window_.push_back(scalar);
    }

    SensorReading result;
    result.timestamp = reading.timestamp;
    result.frame_id = reading.frame_id;
    result.data = {computeMean()};

    callback_(result);

}

float DataProcessor::computeMean() const{
    float tot = 0;
    for(int i = 0; i < window_.size(); ++i){
        tot += window_[i];
    }
    return tot / window_.size();
}

float DataProcessor::computeStdDev(float mean) const{
    float sum_sq = 0.0f;
    for (float val : window_) {
        float diff = val - mean;
        sum_sq += diff * diff;
    }
    float stddev = std::sqrt(sum_sq / window_.size());
    return stddev;
}

float DataProcessor::extractScalar(const SensorReading& reading) const{
    // simplify for practice, average all reading regardless of imu or lidar
    float tot = 0.0f;
    for(int i = 0; i < reading.data.size(); ++i){
        tot += reading.data[i];
    }
    return tot / reading.data.size();
}

