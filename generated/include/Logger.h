#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

// Observer class: Logs events from hackers.
class Logger {
public:
    void log(const std::string& message) {
        std::cout << "[LOG]: " << message << std::endl;
    }
};

#endif // LOGGER_H
