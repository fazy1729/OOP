#ifndef HACKERMANAGER_H
#define HACKERMANAGER_H

#include "Hacker.h"
#include "CryptoHacker.h"
#include "ForensicHacker.h"
#include "EVERYTHING.h"

/**
 * @brief Manager class for handling Hacker objects.
 */
class HackerManager {
private:
    std::shared_ptr<Hacker> hackerPtr;  /**< Smart pointer to the base class Hacker */

public:
    /**
     * @brief Constructor that initializes HackerManager with a Hacker object.
     *
     * @param hacker A shared pointer to a Hacker object.
     */
    HackerManager(std::shared_ptr<Hacker> hacker) : hackerPtr(hacker) {}

    /**
     * @brief Copy constructor for HackerManager.
     *
     * @param other Another HackerManager object to copy from.
     */
    HackerManager(const HackerManager& other) : hackerPtr(other.hackerPtr) {}

    /**
     * @brief Copy-and-swap assignment operator for HackerManager.
     *
     * @param other Another HackerManager object to assign from.
     * @return HackerManager& Reference to the current HackerManager object.
     */
    HackerManager& operator=(HackerManager other) {
        swap(hackerPtr, other.hackerPtr);
        return *this;
    }

    /**
     * @brief Calls the hack method of the Hacker object.
     */
    void performHack() const {
        hackerPtr->hack();  /**< Call the hack method via the base pointer */
    }

    /**
     * @brief Calls the showInfo method of the Hacker object.
     */
    void showInfo() const {
        hackerPtr->showInfo();  /**< Call the showInfo method via the base pointer */
    }

    /**
     * @brief Example of dynamic casting a shared pointer to CryptoHacker.
     */
    void dynamicCastExample() {
        auto cryptoHacker = std::dynamic_pointer_cast<CryptoHacker>(hackerPtr);
        if (cryptoHacker) {
            std::cout << "Successfully casted to CryptoHacker!" << std::endl;
        } else {
            std::cout << "Failed to cast to CryptoHacker." << std::endl;
        }
    }
};

#endif
