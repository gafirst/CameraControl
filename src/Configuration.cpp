#include "Configuration.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

using namespace std;

Configuration::Configuration(string filepath) {
    YAML::Node config = YAML::LoadFile(filepath);

    for(const auto &node : config["cameras"]) {
        if(!node["name"] || !node["ip"]) {
            cerr << "Error: configuration entries must include the camera's Name and IP." << endl;
            continue;
        }

        CameraDetails camera;
        camera.name = node["name"].as<string>();
        camera.ip_address = node["ip"].as<string>();

        if(node["dafault-preset"])
            camera.default_preset = node["default-preset"].as<uint8_t>();

        _cameras.push_back(camera);
    }
}

const std::vector<CameraDetails> &Configuration::cameras() const {
    return _cameras;
}
