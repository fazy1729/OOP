#include "Hacker.h"
#include <ForensicsHacker.h>

/**
 * @brief Constructor that initializes the Hacker object with specialization and skills.
 *
 * @param specialization Specialization of the hacker.
 * @param skills Skills of the hacker.
 */
Hacker::Hacker(const std::string &specialization, const std::string &skills)
{
    this->specialization = specialization;
    this->skills = skills;

    commands_list[0][0] = "Decryption Alghoritms";
    commands_list[0][1] = "Hash Functions";
    commands_list[0][2] = "Key Exchange Protocols";

    commands_list[1][0] = "Metadata Analysis";
    commands_list[1][1] = "Searching Files";
    commands_list[1][2] = "Find Patterns";

    commands_list[2][0] = "Port scan";
    commands_list[2][1] = "Packet Analysis";
    commands_list[2][2] = "Spoofing";

    hacker_personality[0] = "CryptoHacker";
    hacker_personality[1] = "ForensicsHacker";
    hacker_personality[2] = "NetworkingHacker";
}

/**
 * @brief Copy constructor to create a copy of an existing Hacker object.
 *
 * @param other Another Hacker object to copy.
 */
Hacker::Hacker(const Hacker &other) {
    specialization = other.specialization;
    skills = other.skills;

    for(int i = 0; i < 3; i++)
        for(int j=0; j < 3; j++)
            commands_list[i][j] = other.commands_list[i][j];
    for(int i = 0; i < 3; i++)
        hacker_personality[i] = other.hacker_personality[i];
}

/**
 * @brief Assignment operator to assign the data from another Hacker object.
 *
 * @param other Another Hacker object to copy data from.
 * @return Hacker& The current Hacker object.
 */
Hacker& Hacker::operator=(const Hacker &other) {
    if(this !=  &other) {
        specialization = other.specialization;
        skills = other.skills;

        for(int i = 0; i < 3; i++)
            for(int j=0; j < 3; j++)
                commands_list[i][j] = other.commands_list[i][j];
        for(int i = 0; i < 3; i++)
            hacker_personality[i] = other.hacker_personality[i];
    }
    return *this;
}

/**
 * @brief Print the hacker's personality list.
 */
void Hacker::printHackerPersonality() const {
    for(int i = 0; i < 3; i++) {
        std::cout << i+1 << ". " << hacker_personality[i] << std::endl;
    }
}

/**
 * @brief Check if a given personality exists in the hacker's personality list.
 *
 * @param personality The personality to check.
 * @return true If the personality exists.
 * @return false If the personality does not exist.
 */
bool Hacker::checkPersonality(const std::string &personality) {
    for(const auto &i : hacker_personality)
        if(personality == i)
            return true;
    return false;
}

/**
 * @brief Get the command at the specified position in the commands list.
 *
 * @param i The row index in the commands list.
 * @param j The column index in the commands list.
 * @return std::string The command at the given position.
 */
std::string Hacker::getCommands(const int i, const int j) const {
    return commands_list[i][j];
}

/**
 * @brief Check if a given command exists in the commands list.
 *
 * @param command The command to check.
 * @return true If the command exists.
 * @return false If the command does not exist.
 */
bool Hacker::checkCommandExist(const std::string &command) {
    for(auto &i : commands_list)
        for(const auto &j : i)
            if(command == j)
                return true;
    return false;
}

/**
 * @brief Display the help commands based on the given category number.
 *
 * @param number The category number (1 for Decryption, 2 for Metadata, 3 for Network).
 */
void Hacker::help_commands(const int number) const {
    if(number == 1)
        for(int i=0; i<3; i++)
            std::cout << getCommands(0,i) << std::endl;
    else if(number == 2)
        for(int i=0; i<3; i++)
            std::cout << getCommands(1,i) << std::endl;
    else
        for(int i=0; i<3; i++)
            std::cout << getCommands(2,i) << std::endl;
}

/**
 * @brief Overloaded insertion operator to display the hacker's specialization and skills.
 *
 * @param os The output stream.
 * @param hacker The Hacker object to display.
 * @return std::ostream& The output stream.
 */
std::ostream &operator<<(std::ostream &os, const Hacker &hacker) {
    os << "Specialization: " << hacker.specialization << "\n";
    os << "Skills: " << hacker.skills << "\n";
    return os;
}

void analyzeHacker(Hacker* hacker) {
    ForensicHacker* forensicHacker = dynamic_cast<ForensicHacker*>(hacker);
    if (forensicHacker) {
        std::cout << "This Hacker is of type ForensicHacker. Performing analysis..." << std::endl;
        forensicHacker->ExtractMetadata("example.txt", { /* exemplu map */ });
    } else {
        std::cout << "This is a generic Hacker or an    other specialization." << std::endl;
    }
}
