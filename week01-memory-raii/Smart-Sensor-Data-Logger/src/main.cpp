#include "sensor_logger/imu_sensor.hpp"
#include "sensor_logger/lidar_sensor.hpp"
#include "sensor_logger/sensorBuffer.hpp"
#include "sensor_logger/file_writer.hpp"
#include "sensor_logger/DataProcessor.hpp"
#include <memory>
#include <iostream>



int main(){
    // what could be done to do abstraction layer
    // std::vector<std::unique_ptr<ISensor>> sensors;
    // sensors.push_back(std::make_unique<IMUSensor>());
    // sensors.push_back(std::make_unique<LidarSensor>());

    SensorBuffer imu_buffer(100);
    SensorBuffer lidar_buffer(100);

    auto imu_callback = [&imu_buffer](SensorReading result){
                    imu_buffer.push(std::make_unique<SensorReading>(result));
                };
    auto lidar_callback = [&lidar_buffer](SensorReading result) {
        lidar_buffer.push(std::make_unique<SensorReading>(result));};

    // one DataProcessor per sensor type
    DataProcessor imu_processor(3, 2.0, imu_callback);
    DataProcessor lidar_processor(3, 2.0, lidar_callback);


    // sensors
    IMUSensor imu;
    LidarSensor lidar;

    FileWriter writer("sensor_log.csv");

    // main loop — read, process, results automatically land in buffers via callbacks
    for (int i = 0; i < 100; ++i) {
        imu_processor.process(imu.read());      // callback fires → imu_buffer gets result
        lidar_processor.process(lidar.read());  // callback fires → lidar_buffer gets result
    }

    // drain buffers and write to file
    auto imu_readings = imu_buffer.drain();
    for (const auto& r : imu_readings) {
        writer.write(*r);
    }

    auto lidar_readings = lidar_buffer.drain();
    for (const auto& r : lidar_readings) {
        writer.write(*r);
    }

//
    // for (int i = 0; i < 100; ++i) {
    //     for (auto& sensor : sensors) {
    //         auto reading = std::make_unique<SensorReading>(sensor -> read());
    //         if(reading -> frame_id == "IMU_"){
    //             auto callback = [&imu_buffer](SensorReading result){
    //                 imu_buffer.push(std::move(reading))
    //             }
    //         }
    //         else{
    //             lidar_buffer.push(std::move(reading));
    //         }
    //     }

    //     auto imu_reading = imu_buffer.drain();
    //     auto lidar_reading = imu_buffer.drain();
    //     for(const auto& r : reading){
    //         writer.write(*r);
    //     }
    // }

    std::cout << "Done. Check sensor_log.csv\n";
}
