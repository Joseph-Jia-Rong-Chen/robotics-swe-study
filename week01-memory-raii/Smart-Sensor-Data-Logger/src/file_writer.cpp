#include "sensor_logger/file_writer.hpp"

FileWriter::FileWriter(const std::string& path) : file_(path) {
    if (!file_.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }
}

FileWriter::~FileWriter(){
    file_.close(); // ofstream manages itself, but for clarity we put it here
}

void FileWriter::write(const SensorReading& reading) {
    file_ << reading.timestamp << ","
          << reading.frame_id;
    for (const auto& val : reading.data) {
        file_ << "," << val;
    }
    file_ << "\n";
}


