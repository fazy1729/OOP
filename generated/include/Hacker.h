#ifndef HACKER_H
#define HACKER_H

#include "EVERYTHING.h"
#include <string>  // Ensure this line is present for std::string

// Hacker class: Represents a generic hacker with a specialization, skills, and command list.
class Hacker {
private:
    std::string specialization; ///< The specialization of the hacker.
    std::string skills; ///< The skills of the hacker.
    std::string commands_list[3][3]; ///< A 2D array containing commands for the hacker.
    std::string hacker_personality[3]; ///< An array representing the hacker's personality.

public:
    /**
     * @brief Default constructor for the Hacker class.
     */
    Hacker() = default;

    /**
     * @brief Constructs a Hacker with a specified specialization and skills.
     * @param specialization The specialization of the hacker.
     * @param skills The skills of the hacker.
     */
    Hacker(const std::string &specialization, const std::string &skills);

    /**
     * @brief Copy constructor for the Hacker class.
     * @param other The Hacker object to be copied.
     */
    Hacker(const Hacker &other);

    /**
     * @brief Assignment operator for the Hacker class.
     * @param other The Hacker object to be assigned.
     * @return Reference to this Hacker object.
     */
    Hacker& operator=(const Hacker &other);

    /**
     * @brief Overloaded output stream operator to print the hacker's details.
     * @param os The output stream.
     * @param hacker The Hacker object to be printed.
     * @return The output stream after printing the hacker's details.
     */
    friend std::ostream& operator<<(std::ostream &os, const Hacker &hacker);

    /**
     * @brief A pure virtual method for performing the hack. Must be implemented by derived classes.
     */
    virtual void hack() = 0;

    /**
     * @brief A pure virtual method to clone the Hacker object. Must be implemented by derived classes.
     * @return A pointer to a new copy of the Hacker object.
     */
    virtual Hacker* clone() const = 0;

    /**
     * @brief Displays the hacker's specialization and skills.
     * Displays information about the hacker in a simple format.
     */
    virtual void display() const {
        std::cout << "Hacker of specialization: " << specialization << std::endl;
        std::cout << "Skills: " << skills << std::endl;
    }

    /**
     * @brief Displays basic information about the hacker.
     * This is a non-virtual method for displaying general hacker information.
     */
    void showInfo() const {
        std::cout << "This is a hacker with specialization: " << specialization << std::endl;
    }

    /**
     * @brief Prints the hacker's personality traits.
     */
    void printHackerPersonality() const;

    /**
     * @brief Checks if the hacker has a certain personality.
     * @param personality The personality to check.
     * @return True if the hacker has the specified personality, false otherwise.
     */
    bool checkPersonality(const std::string &personality);

    /**
     * @brief Gets a specific command from the command list.
     * @param i The row index of the command.
     * @param j The column index of the command.
     * @return The command at position [i][j].
     */
    std::string getCommands(const int i, const int j) const;

    /**
     * @brief Checks if a given command exists in the command list.
     * @param command The command to check.
     * @return True if the command exists, false otherwise.
     */
    bool checkCommandExist(const std::string &command);

    /**
     * @brief Displays help information for a given command number.
     * @param number The command number for which to show help.
     */
    void help_commands(const int number) const;

    /**
     * @brief Destructor for the Hacker class.
     */
    virtual ~Hacker() = default;
};

#endif
