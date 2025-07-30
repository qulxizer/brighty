#include "device.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string getDeviceName(int argc, char *argv[]) {
  std::string deviceName = "";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.find("--device=") != std::string::npos) {
      deviceName = arg.substr(9);
    }
  }
  if (deviceName == "") {
    throw std::runtime_error("Failed to get device name");
  }
  return deviceName;
}

int main(int argc, char *argv[]) {
  Command cmd;
  int cmdIndex;
  for (int i = 0; i < argc; i++) {
    Command parsedCmd = parseCmd(argv[i]);
    if (parsedCmd != Command::UNKNOWN) {
      cmd = parsedCmd;
      cmdIndex = i;
    }
  }

  // Pre-Device switch
  switch (cmd) {
  case Command::LIST: {
    std::vector<std::string> devices = listDevices();
    for (const auto &device : devices) {
      std::cout << device << std::endl;
    }
    return 0;
  }

  case Command::HELP: {
    std::cout
        << "Usage:\n"
           "  brighty list                      List available devices\n"
           "  brighty help                      Show this help message\n"
           "  brighty <device> get              Show current brightness\n"
           "  brighty <device> set <value>      Set brightness to value\n"
           "  brighty <device> inc <value>      Increase brightness by value\n"
           "  brighty <device> dec <value>      Decrease brightness by value\n"
           "  brighty <device> max              Show max brightness\n";
    return 0;
  }
  default:
    break;
  }

  std::string deviceName;
  try {
    deviceName = getDeviceName(argc, argv);
  } catch (const std::exception &e) {
    std::cerr << "Failed to find device" << std::endl;
    return 1;
  }

  Device dev(deviceName);
  switch (cmd) {
  case Command::GET:
    try {
      std::cout << dev.getBrightness() << std::endl;
    } catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
    return 1;
    break;

  case Command::SET: {
    int value = std::atoi(argv[cmdIndex + 1]);
    dev.setBrightness(value);
    break;
  }

  case Command::INC: {
    std::string valueStr = argv[cmdIndex + 1];
    try {
      if (valueStr.find('%') == std::string::npos) {
        int value = std::atoi(valueStr.c_str());
        dev.setBrightness(value + dev.getBrightness());
        break;
      }
      std::erase(valueStr, '%');
      float value = std::atoi(valueStr.c_str());
      unsigned int brightness =
          dev.getBrightness() - ((value / 100) * dev.getMaxBrightness());
      if (brightness > dev.getMaxBrightness()) {
        brightness = dev.getMaxBrightness();
      }
      dev.setBrightness(dev.getBrightness() +
                        ((value / 100) * dev.getMaxBrightness()));
    } catch (std::exception &e) {
      std::cerr << "Failed to set brightness, " << e.what();
    }
    break;
  }

  case Command::DEC: {
    std::string valueStr = argv[cmdIndex + 1];
    try {
      if (valueStr.find('%') != std::string::npos) {
        int value = std::atoi(valueStr.c_str());
        dev.setBrightness(dev.getBrightness() - 20);
        break;
      }
      std::erase(valueStr, '%');
      float value = std::atoi(valueStr.c_str());
      unsigned int brightness =
          dev.getBrightness() - ((value / 100) * dev.getMaxBrightness());
      dev.setBrightness(brightness);
    } catch (std::exception &e) {
      std::cerr << "Failed to set brightness: " << e.what();
    }
    break;
  }

  case Command::MAX:
    std::cout << dev.getMaxBrightness() << std::endl;
    break;

  default:
    std::cerr << "Unknown command" << std::endl;
    return 1;
  }

  return 0;
}
