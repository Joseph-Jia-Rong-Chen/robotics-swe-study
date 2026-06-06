#include <iostream>
#include <memory>
#include "releasecamera.hpp"

CameraInterface::CameraInterface(){
    std::cout << "Camera Opened" << std::endl;
}

CameraInterface::~CameraInterface(){
    std::cout << "Camera Closed" << std::endl;
}

SensorManager::SensorManager(){
    camera = std::make_unique<CameraInterface>();
}

SensorManager::~SensorManager(){
}

CameraInterface* SensorManager::getCamera(){
    return camera.get();
}

std::unique_ptr<CameraInterface> SensorManager::releaseCamera(){
    return std::move(camera);
}


