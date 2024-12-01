#ifndef LEVEL_H
#define LEVEL_H

#include "EVERYTHING.h"
#include "Terminal.h"

/**
 * @brief Struct to represent the status of a port.
 */
struct PortStatus {
    int port; /**< The port number */
    bool isOpen; /**< Status of the port (open or closed) */
};

/**
 * @brief Class to represent a level in the game, derived from Terminal.
 */
class Level : public Terminal {
private:
    int currentlevel; /**< The current level */
    std::string objective; /**< The objective for the current level */
    std::string target; /**< The target for the current level */

    std::map<int, std::vector<PortStatus>> levelPorts; /**< Map of levels to corresponding port statuses */
    std::map<std::string, std::vector<std::string>> catFiles; /**< Map of file names to file contents */

public:
    /**
     * @brief Constructor for the Level class.
     *
     * @param currentLevel The starting level.
     */
    explicit Level(int currentLevel);

    /**
     * @brief Default constructor for the Level class.
     */
    Level() = default;

    /**
     * @brief Copy constructor for the Level class.
     *
     * @param level Another Level object to copy from.
     */
    Level(const Level& level);

    /**
     * @brief Overloaded stream insertion operator for Level class.
     *
     * @param os The output stream to insert into.
     * @param level The Level object to insert.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream &os, const Level &level);

    /**
     * @brief Overloaded assignment operator for Level class.
     *
     * @param level Another Level object to assign from.
     * @return Level& The current Level object.
     */
    Level& operator=(const Level& level);

    /**
     * @brief Gets the objective of the current level.
     *
     * @return std::string The objective of the level.
     */
    std::string getObjective() const;

    /**
     * @brief Gets the files for the current level.
     *
     * @return std::map<std::string, std::vector<std::string>> The files for the current level.
     */
    std::map<std::string, std::vector<std::string>> getCatFiles();

    /**
     * @brief Sets the ports for a specific level.
     *
     * @param level The level number.
     * @param ports The ports associated with the level.
     */
    void setPortsForLevel(int level, const std::vector<PortStatus>& ports);

    /**
     * @brief Gets the ports for a specific level.
     *
     * @param level The level number.
     * @return std::vector<PortStatus> The ports for the level.
     */
    std::vector<PortStatus> getPortsForLevel(int level) const;

    /**
     * @brief Gets the current level.
     *
     * @return int The current level number.
     */
    int getCurrentLevel() const;

    /**
     * @brief Gets the password for a specific level.
     *
     * @param currLevel The current level number.
     * @return bool Whether the password is correct or not.
     */
    bool getPassword(int currLevel);

    /**
     * @brief Destructor for the Level class.
     */
    ~Level() = default;
};

#endif
