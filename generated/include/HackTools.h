#ifndef HACKTOOLS_H
#define HACKTOOLS_H

#include <iostream>
#include <string>

// Clasa șablon pentru un instrument de hacking generic
template <typename T>
class HackTool {
private:
    std::string name;    // Numele instrumentului de hacking
    T powerLevel;        // Nivelul de putere al instrumentului (poate fi un int sau un float)

public:
    // Constructor
    HackTool(std::string n, T p) : name(n), powerLevel(p) {}

    // Funcție pentru a afișa informații despre instrumentul de hacking
    void displayInfo() const {
        std::cout << "HackTool Name: " << name << ", Power Level: " << powerLevel << std::endl;
    }

    // Returnează nivelul de putere
    T getPowerLevel() const {
        return powerLevel;
    }

    // Setează nivelul de putere
    void setPowerLevel(T p) {
        powerLevel = p;
    }
};

// Funcție șablon care compară două instrumente de hacking
template <typename T>
void compareHackTools(const HackTool<T>& tool1, const HackTool<T>& tool2) {
    if (tool1.getPowerLevel() > tool2.getPowerLevel()) {
        std::cout << tool1.getPowerLevel() << " is stronger than " << tool2.getPowerLevel() << std::endl;
    } else if (tool1.getPowerLevel() < tool2.getPowerLevel()) {
        std::cout << tool2.getPowerLevel() << " is stronger than " << tool1.getPowerLevel() << std::endl;
    } else {
        std::cout << "Both HackTools have equal power levels!" << std::endl;
    }
}

#endif
