#ifndef INTERFACE_H
#define INTERFACE_H

#include "EVERYTHING.h"

/**
 * @brief Class to manage the interface for the game.
 */
class Interface {
private:
    std::string name; /**< Player's name */
    std::ifstream inputFile; /**< Input file stream for reading commands */

public:
    /**
     * @brief Default constructor for Interface class.
     */
    Interface() = default;

    /**
     * @brief Copy constructor for Interface class.
     *
     * @param other Another Interface object to copy from.
     */
    Interface(const Interface& other);

    /**
     * @brief Constructor that initializes the interface with a given file.
     *
     * @param fileName The name of the file to be used for the interface.
     */
    explicit Interface(const std::string& fileName);

    /**
     * @brief Overloaded stream insertion operator for Interface class.
     *
     * @param os Output stream to insert into.
     * @param obj The Interface object to insert.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Interface& obj);

    /**
     * @brief Overloaded assignment operator for Interface class.
     *
     * @param other Another Interface object to assign from.
     * @return Interface& The current Interface object.
     */
    Interface &operator=(const Interface &other);

    /**
     * @brief Gets the player's name.
     *
     * @return std::string The player's name.
     */
    std::string getPlayerName() const;

    /**
     * @brief Destructor for the Interface class.
     */
    ~Interface() = default;
};

#endif
