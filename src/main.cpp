#include "device.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

std::string getDeviceName(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.find("--device=") == 0) {
            return arg.substr(9);
        }
    }
    return "";
}


int main (int argc, char *argv[]) {

    Command cmd = parseCmd(argv[2]);
    if (cmd == Command::LIST) {
            std::vector<std::string> devices = listDevices();
            for (auto device: devices) {
                std::cout << device.c_str() << std::endl;
            }
        return 0;
    }

    std::string deviceName = getDeviceName(argc, argv);
    Device dev = Device(deviceName) ;
    switch (cmd) {
    case Command::GET:{
            std::cout << dev.getBrightness() << std::endl;
            break;

        }
    case Command::SET:{
            int value = std::atoi(argv[3]);
        }

    case Command::INC:
    case Command::DEC:
    case Command::MAX:
        std::cout << dev.getMaxBrightness() << std::endl;
        break;

    default:
      break;
    }

    return 0;
}

