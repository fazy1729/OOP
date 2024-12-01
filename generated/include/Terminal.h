#ifndef TERMINAL_H
#define TERMINAL_H
#include "EVERYTHING.h"

/**
 * @brief Class representing a Terminal.
 *
 * Provides functionality for navigating a file system and executing common terminal commands.
 */
class Terminal {
private:
    std::map<std::string, std::vector<std::string>> fileSystem; /**< The file system structure */
    std::string currentDirectory; /**< The current directory the terminal is in */

public:
    /**
     * @brief Default constructor for Terminal.
     */
    Terminal();

    /**
     * @brief Copy constructor for Terminal.
     *
     * @param other The other Terminal object to copy from.
     */
    Terminal(const Terminal& other);

    /**
     * @brief Assignment operator for Terminal using copy-and-swap.
     *
     * @param other The other Terminal object to assign from.
     * @return Terminal& Reference to this Terminal object.
     */
    Terminal& operator=(const Terminal& other);

    /**
     * @brief Friend function to output the Terminal object to an output stream.
     *
     * @param os The output stream.
     * @param terminal The Terminal object to print.
     * @return std::ostream& The output stream after inserting the Terminal object.
     */
    friend std::ostream& operator<<(std::ostream& os, const Terminal& terminal);

    /**
     * @brief Returns the current directory in the terminal.
     *
     * @return std::string The current directory.
     */
    std::string getCurrentDirectory();

    /**
     * @brief Displays the player's name in the terminal.
     *
     * @param playerName The name of the player.
     */
    void displayPlayerName(const std::string& playerName);

    /**
     * @brief Lists the available commands in the terminal help.
     */
    static void list_commands_help();

    /**
     * @brief Executes the 'ls' command to list the files in the current directory.
     */
    void ls() const;

    /**
     * @brief Changes the current directory to the specified directory.
     *
     * @param directory The directory to change to.
     */
    void cd(const std::string& directory);

    /**
     * @brief Prints the current working directory.
     */
    void pwd() const;

    /**
     * @brief Executes the 'cat' command to display the content of a file.
     *
     * @param key The key of the file.
     * @param catFile The map containing the file's content.
     */
    void cat(const std::string& key, const std::map<std::string, std::vector<std::string>>& catFile) const;

    /**
     * @brief Destructor for Terminal.
     */
    ~Terminal() = default;
};

#endif
