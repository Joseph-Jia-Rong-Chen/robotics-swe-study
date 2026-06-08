#include "sensor_logger/imu_sensor.hpp"
#include "sensor_logger/lidar_sensor.hpp"
#include "sensor_logger/sensorBuffer.hpp"
#include "sensor_logger/file_writer.hpp"
#include <memory>
#include <iostream>



int main(){
    std::vector<std::unique_ptr<ISensor>> sensors;
    sensors.push_back(std::make_unique<IMUSensor>());
    sensors.push_back(std::make_unique<LidarSensor>());

    SensorBuffer buffer(100);
    FileWriter writer("sensor_log.csv");

    for (int i = 0; i < 10; ++i) {
        for (auto& sensor : sensors) {
            auto reading = std::make_unique<SensorReading>(sensor -> read());
            buffer.push(std::move(reading));
        }

        auto reading = buffer.drain();
        for(const auto& r : reading){
            writer.write(*r);
        }
    }

    std::cout << "Done. Check sensor_log.csv\n";
}
