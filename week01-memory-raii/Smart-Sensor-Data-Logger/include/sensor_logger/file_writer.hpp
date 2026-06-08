#pragma once
#include "sensor_logger/sensor_reading.hpp"
#include <string>
#include <fstream>

class FileWriter{
    public:
        explicit FileWriter(const std::string& path);
        // no explicit destructor needed — ofstream closes itself
        ~FileWriter();
        // write one reading as a CSV line:
        // timestamp,frame_id,val0,val1,...
        void write(const SensorReading& reading);
    
        FileWriter(const FileWriter&)            = delete;
        FileWriter& operator=(const FileWriter&) = delete;
    
    private:
        std::ofstream file_;
};