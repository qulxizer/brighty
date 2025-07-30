#include "device.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <format>
#include <vector>

#define BACKLIGHT_DIRECTORY "/sys/class/backlight"

Device::Device(const std::string& name) {
    devicePath = std::format("{}/{}", BACKLIGHT_DIRECTORY, name);
    bool isDirectory = std::filesystem::is_directory(devicePath);
    if (!isDirectory) {
        throw std::invalid_argument("couldn't find device: " + devicePath);
    }
    std::filesystem::path maxBrightnessPath = std::filesystem::path(devicePath) / "max_brightness";
    std::ifstream file(maxBrightnessPath);
    std::string line;
    std::getline(file, line);
    file.close();
    maxBrightness = std::stoi(line);
}

void Device::setBrightness(unsigned int brightness) {

    std::filesystem::path brightnessPath = std::filesystem::path(devicePath) / "brightness";
    std::ofstream file(brightnessPath, std::ios::trunc);
    if (file.is_open()) {
        file << std::to_string(brightness);
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    file.close();
    return;
}

const unsigned int Device::getBrightness()  {
    std::string brightnessFile = std::format("{}/{}", devicePath, "brightness");
    std::ifstream file(brightnessFile);
    if (!file.is_open()) {
        throw std::ios_base::failure("Failed to open file: " + brightnessFile);
    }
    std::string line;
    std::getline(file, line);
    file.close();
    return std::stoi(line);
}


const unsigned int Device::getMaxBrightness()  {
    return maxBrightness;
}


const std::string Device::getDeviceName()  {
    std::filesystem::path p(devicePath);
    return p.filename().string();
}


std::vector<std::string> listDevices() {
    std::vector<std::string> devices;
    for (auto &dir : std::filesystem::directory_iterator("/sys/class/backlight/")) {
        devices.push_back(dir.path().string());
    };
    return devices;
}

Command parseCmd(const std::string& s) {
    if (s == "list") return Command::LIST;
    if (s == "help") return Command::HELP;
    if (s == "get") return Command::GET;
    if (s == "set") return Command::SET;
    if (s == "inc") return Command::INC;
    if (s == "dec") return Command::DEC;
    if (s == "max") return Command::MAX;

    return Command::UNKNOWN;
}
