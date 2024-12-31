#ifndef HACKERFACTORY_H
#define HACKERFACTORY_H

#include "Hacker.h"
#include "CryptoHacker.h"
#include "NetworkingHacker.h"
#include "ForensicsHacker.h"
#include <string>

// Factory Method: Creates Hacker objects based on a type string.
    class HackerFactory {
    public:
        static Hacker* createHacker(const std::string& type) {
            if (type == "CryptoHacker") {
                return new CryptoHacker();
            } else if (type == "NetworkingHacker") {
                return new NetworkingHacker();
            } else if (type == "ForensicsHacker") {
                return new ForensicHacker();
            }
            return nullptr; // If no match, return nullptr.
        }
    };

#endif // HACKERFACTORY_H
