#ifndef HACKERMANAGER_H
#define HACKERMANAGER_H

#include "Hacker.h"
#include "CryptoHacker.h"
#include "ForensicHacker.h"
#include "EVERYTHING.h"

class HackerManager {
private:
    shared_ptr<Hacker> hackerPtr;  // Smart pointer către clasa de bază Hacker

public:
    // Constructori
    HackerManager(shared_ptr<Hacker> hacker) : hackerPtr(hacker) {}
    HackerManager(const HackerManager& other) : hackerPtr(other.hackerPtr) {}

    // Operator de atribuire folosind copy-and-swap
    HackerManager& operator=(HackerManager other) {
        swap(hackerPtr, other.hackerPtr);
        return *this;
    }

    // Funcție pentru a apela metoda virtuală hack
    void performHack() const {
        hackerPtr->hack();  // Apelul se face prin pointerul de bază
    }

    // Funcție pentru a apela funcția non-virtuală showInfo
    void showInfo() const {
        hackerPtr->showInfo();  // Apelul se face prin pointerul de bază
    }

    // Funcție pentru downcast folosind dynamic_cast
    void dynamicCastExample() {
        auto cryptoHacker = dynamic_pointer_cast<CryptoHacker>(hackerPtr);
        if (cryptoHacker) {
            cout << "Successfully casted to CryptoHacker!" << endl;
        } else {
            cout << "Failed to cast to CryptoHacker." << endl;
        }
    }
};

#endif
