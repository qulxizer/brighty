#include <string>
#include <vector>

enum class Command {
    LIST,
    GET,
    SET,
    INC,
    DEC,
    MAX,
    UNKNOWN,
};

class Device {
    std::string devicePath;
    unsigned int maxBrightness;

    public:
        Device(const std::string& name);
        void setBrightness(const unsigned int);
        const unsigned int getBrightness();
        const unsigned int getMaxBrightness();
        const std::string getDeviceName();
};

Command parseCmd(const std::string& s);
std::vector<std::string> listDevices();
