#include <EVERYTHING.h>
#include "Level.h"

/**
 * @brief Constructor for the Level class.
 *
 * Initializes a Level object with a specific level number, objective,
 * target, and associated files. Also, sets the ports for the level and
 * prints out initial mission details.
 *
 * @param currentLevel The level number to initialize the object with.
 */
Level::Level(int currentLevel) {
    this->currentlevel = currentLevel;
    std::cout << "LEVEL " << currentLevel;
    catFiles.clear();

    if (currentLevel == 1) {
        objective = "Your mission is clear: decrypt the message, find the password, and uncover crucial information about the mysterious MOSSAD agent. The clock is ticking...\n";

        catFiles["caesar.txt"] = {"Kdvk wklv phvvdjh zlwk wkh WDUJHW dqg WLPH Dojkrulwp"};
        levelPorts[currentLevel] = {
            {80, true},
            {22, false},
            {443, true},
            {8080, false}
        };
        this->target = "SHAd aku";

        // Atmospheric context for the player
        std::cout << "------------------------------------------------------------\n";
        std::cout << "Level 1: The mission begins...\n";
        std::cout << "Location: TEL AVIV 32.0929° N, 34.8072° E\n";
        std::cout << "Time: 14:56\n";
        std::cout << "------------------------------------------------------------\n";
        std::cout << "Your objective is to decrypt the message. Once decrypted, you'll need to hash it in some way. Your first step is clear...\n";
        std::cout << "------------------------------------------------------------\n";
        std::cout << "TARGET: " << target << "...\n";
        std::cout << "------------------------------------------------------------\n";
    }
    if (currentLevel == 2) {
        objective =
    "------------------------------------------------------------\n"
    "LEVEL 2: The Trail Has Gone Cold\n"
    "------------------------------------------------------------\n"
    "\n"
    "The trail has gone cold. You've decrypted the first message, but now the situation has escalated. "
    "A file points to a new IP address, and time is running out.\n"
    "\n"
    "Your task is to discover the hidden clues behind the firewall. "
    "See the open ports, hinting that a secure site may hold the key.\n"
    "\n"
    "You must analyze the available files, extract the IP address, and visit the site to gather vital intelligence.\n"
    "\n"
    "But beware, not everything is as it seems—someone may be watching your every move.\n"
    "\n"
    "Find the password and you might uncover the next step in your mission...\n"
    "\n"
    "PS: ONE OF THE BEST UNIVERSITIES? (+RANKING)??\n"
    "\n"
    "------------------------------------------------------------\n";
        levelPorts[currentLevel] = {
            {80, true},
            {22, false},
            {443, true},
            {8080, false}
        };
        catFiles["file2.txt"] = {"Nothing"};
        catFiles["file3.txt"] = {"Hello, contact us at support@example.com.\n Visit https://shorturl.at/UtRvu for more details.Server IP is 192.168.0.1."};
        catFiles["file4.txt"] = {"Test4"};
        catFiles["file5.txt"] = {"Test5"};
        catFiles["file6.txt"] = {"Test6"};
        catFiles["file7.txt"] = {"haawaiajdajwdakdaksdkasnSTANFORDPINESadhawdhajdkaskda"};
        catFiles["file8.txt"] = {"Test8"};

    }
}

/**
 * @brief Sets the ports for a specific level.
 *
 * This method allows the configuration of network ports for a given level.
 *
 * @param level The level number for which ports are being set.
 * @param ports A vector of PortStatus objects representing the port configurations.
 */
void Level::setPortsForLevel(int level, const std::vector<PortStatus>& ports) {
    levelPorts[level] = ports;
}

/**
 * @brief Retrieves the ports for a specific level.
 *
 * This method returns the ports associated with a particular level.
 * If the level does not exist, it returns an empty vector.
 *
 * @param level The level number whose ports are to be retrieved.
 * @return A vector of PortStatus objects representing the ports for the level.
 */
std::vector<PortStatus> Level::getPortsForLevel(int level) const {
    auto it = levelPorts.find(level);
    if (it != levelPorts.end()) {
        return it->second;
    }
    return {};
}

/**
 * @brief Copy constructor for the Level class.
 *
 * Creates a new Level object as a copy of an existing Level object.
 *
 * @param level The Level object to copy.
 */
Level::Level(const Level &level) : Terminal(level) {
    this->currentlevel = level.currentlevel;
    this->objective = level.objective;
    this->target = level.target;
    this->catFiles = level.catFiles;
}

/**
 * @brief Assignment operator for the Level class.
 *
 * Allows one Level object to be assigned the values of another.
 *
 * @param level The Level object to assign from.
 * @return A reference to the assigned Level object.
 */
Level & Level::operator=(const Level &level) {
    if (this != &level) {
        currentlevel = level.currentlevel;
        objective = level.objective;
        target = level.target;
        catFiles = level.catFiles;
    }
    return *this;
}

/**
 * @brief Retrieves the objective for the current level.
 *
 * This method returns the mission objective for the current level.
 *
 * @return A string containing the objective.
 */
std::string Level::getObjective() const {
    return objective;
}

/**
 * @brief Retrieves the files associated with the current level.
 *
 * This method returns the map of files associated with the current level.
 *
 * @return A map of file names to their contents for the current level.
 */
std::map<std::string, std::vector<std::string>> Level::getCatFiles() {
    return catFiles;
}

/**
 * @brief Retrieves the current level number.
 *
 * This method returns the number of the current level.
 *
 * @return An integer representing the current level.
 */
int Level::getCurrentLevel() const {
    return this->currentlevel;
}

/**
 * @brief Verifies if the player has entered the correct password for the current level.
 *
 * At Level 1, the player is asked to enter the password. If the password is correct,
 * the level advances to the next one.
 *
 * @param currLevel The current level of the player.
 * @return True if the password is correct, false otherwise.
 */
bool Level::getPassword(int currLevel) {
    if (currLevel == 1) {
        const std::string verif = "0ea1c6dd1697dc4e8035da6149a2d680e847a57ff69ee7e73662b507c1a58698";
        std::cout << "Please enter the password: ";
        std::string pass;
        std::cin >> pass;
        if (pass == verif) {
            currLevel += 1;
            std::cout << "Level 2 unlocked\n";
            return true;
        } else {
            std::cout << "ACCESS DENIED\n";
            return false;
        }
    }
    if (currLevel == 2) {
        const std::string verif = "STANFORDPINES2";
        std::cout << "Please enter the password: ";
        std::string pass;
        std::cin >> pass;
        if (pass == verif) {
            currLevel += 1;
            std::cout << "Level 3 unlocked! New objective coming soon...\n";
            return true;
        }
        std::cout << "ACCESS DENIED\n";
        return false;
    }
    return false;
}

/**
 * @brief Overloads the stream insertion operator to print the level information.
 *
 * This operator allows a Level object to be printed in a human-readable format.
 *
 * @param os The output stream to write to.
 * @param level The Level object to print.
 * @return The output stream with the level information inserted.
 */
std::ostream &operator<<(std::ostream &os, const Level &level) {
    os << "Current level is: " << level.currentlevel;
    os << "Target is: " << level.target;
    return os;
}
