#pragma once

#include <memory>
#include <string>

class CameraInterface{
    public:
        CameraInterface();
        ~CameraInterface();

};

class SensorManager{
    public:
        SensorManager();
        ~SensorManager();
        CameraInterface* getCamera();
        std::unique_ptr<CameraInterface> releaseCamera();

    private:
        std::unique_ptr<CameraInterface> camera;

};