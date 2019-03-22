#ifndef FIRST_CAMERACONTROL_CONFIGURATION_H
#define FIRST_CAMERACONTROL_CONFIGURATION_H

#include <string>
#include <vector>

struct CameraDetails {
    std::string name;
    std::string ip_address;
    uint8_t default_preset = 0;
};

class Configuration {
public:

    Configuration(std::string filepath);

    const std::vector<CameraDetails> &cameras() const;

private:
    std::vector<CameraDetails> _cameras;

};


#endif //FIRST_CAMERACONTROL_CONFIGURATION_H
