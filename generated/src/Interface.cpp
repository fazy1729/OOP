#include "Interface.h"

/**
 * @brief Constructor for Interface class that initializes the game and reads player name from a file.
 *
 * @param fileName The name of the file containing the player's name.
 */
Interface::Interface(const std::string& fileName) {
    std::cout << "------------------------------------------------------------\n";
    std::cout << "WELCOME TO INTRUSION\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "At any time, you can type --help to view the available commands, or --exit to quit the game.\n\n";
    std::cout << "Your mission: Infiltrate the SECRET directory. The path to it is hidden within a series of puzzles. Solve them to obtain the PASSWORD, which will unlock the folder and reveal critical information.\n\n";
    std::cout << "If you need assistance at any time, simply use the --objective command to remind yourself of your task.\n\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "Please enter your name to begin your mission: \n\n";

    inputFile.open(fileName);
    std::getline(inputFile, name);

    std::cout << "Welcome, " << name << ". Your journey begins now...\n";
    std::cout << "------------------------------------------------------------\n";
}

/**
 * @brief Copy constructor for Interface class.
 *
 * @param other Another Interface object to copy from.
 */
Interface::Interface(const Interface& other) : name(other.name) {}

/**
 * @brief Retrieves the player's name.
 *
 * @return std::string The player's name.
 */
std::string Interface::getPlayerName() const {
    return name;
}

/**
 * @brief Assignment operator for Interface class.
 *
 * @param other Another Interface object to assign from.
 * @return Interface& The updated Interface object.
 */
Interface& Interface::operator=(const Interface& other) {
    if (this != &other) {
        name = other.name;
        if (inputFile.is_open()) {
            inputFile.close();
        }
    }
    return *this;
}

/**
 * @brief Overloads the stream insertion operator to output Interface information.
 *
 * @param os The output stream.
 * @param obj The Interface object to output.
 * @return std::ostream& The updated output stream.
 */
std::ostream& operator<<(std::ostream& os, const Interface& obj) {
    os << "Your name is: " << obj.name;
    return os;
}
