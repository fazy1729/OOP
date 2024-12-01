#include "EVERYTHING.h"
#include "Terminal.h"

/**
 * @brief Default constructor for Terminal.
 * Initializes the file system structure and sets the current directory.
 */
Terminal::Terminal() {
    fileSystem["/"] = {"home", "etc", "SECRET"};
    fileSystem["/home"] = {"user1", "user2"};
    fileSystem["/home/user1"] = {"caesar.txt", "file2.txt", "file3.txt","file4.txt","file5.txt","file6.txt","file7.txt", "projects"};
    fileSystem["/etc"] = {"passwd", "hosts"};
    fileSystem["/SECRET"] = {"CIA"};

    currentDirectory = "/";
}

/**
 * @brief Copy constructor for Terminal.
 *
 * @param other The other Terminal object to copy from.
 */
Terminal::Terminal(const Terminal& other) {
    this->fileSystem = other.fileSystem;
    this->currentDirectory = other.currentDirectory;
}

/**
 * @brief Assignment operator for Terminal using copy-and-swap.
 *
 * @param other The other Terminal object to assign from.
 * @return Terminal& Reference to this Terminal object.
 */
Terminal& Terminal::operator=(const Terminal& other) {
    if (this != &other) {
        fileSystem = other.fileSystem;
        currentDirectory = other.currentDirectory;
    }
    return *this;
}

/**
 * @brief Returns the current directory in the terminal.
 *
 * @return std::string The current directory.
 */
std::string Terminal::getCurrentDirectory() {
    return currentDirectory;
}

/**
 * @brief Displays the player's name in the terminal with the current directory.
 *
 * @param playerName The name of the player.
 */
void Terminal::displayPlayerName(const std::string& playerName) {
    std::cout << playerName << "@" << getCurrentDirectory() << ":$";
}

/**
 * @brief Displays the available commands and their descriptions based on the user's choice.
 */
void Terminal::list_commands_help() {
    std::cout << "1. Linux commands - Commands to use in the terminal\n";
    std::cout << "2. Hacker commands - Commands that can help you pass a level\n";
    std::cout << "Enter a number: ";
    int number;
    std::cin >> number;
    if (number == 1) {
        std::cout << "ls - Prints the contents in a directory: usage example: ls <directory>\n";
        std::cout << "cd - Navigate to another directory: usage example: cd <directory>\n";
        std::cout << "pwd - Prints the working directory: usage example: pwd\n";
        std::cout << "--objective - See the objective for this level\n";
    }
    else if (number == 2) {
        std::cout << "--sha256 - You can hash a message using the SHA256 algorithm: usage example: --sha256 <file.txt>\n";
        std::cout << "--caesar - You can decrypt an encrypted message that is shifted with 3 positions: usage example: --caesar <file.txt>\n";
        std::cout << "--extract-metadata - You can extract metadata from a given file, such as author, creation date, and other information. Usage example: --extract-metadata <file.txt>\n";
        std::cout << "--search-keyword - You can search for a specific keyword within a file and return the results. Usage example: --search-keyword <file.txt> <keyword>\n";
        std::cout << "--analyze-patterns - You can analyze a file for certain patterns or anomalies. Usage example: --analyze-patterns <file.txt>\n";
        std::cout << "--port-scan - You can perform a port scan on a target IP to check open ports. Usage example: --port-scan <target_ip>\n";
        std::cout << "--intercept-packets - You can intercept and analyze network packets to monitor traffic. Usage example: --intercept-packets <file.txt>\n";
        std::cout << "--spoof-request - You can spoof a network request with a target IP and custom message. Usage example: --spoof-request <target_ip> <message>\n";
        std::cout << "--capture-traffic - You can capture network traffic logs, such as IP addresses and data sent. Usage example: --capture-traffic <file.txt>\n";
    }
}

/**
 * @brief Executes the 'ls' command to list the files in the current directory.
 */
void Terminal::ls() const {
    std::cout << "Listing files in: " << currentDirectory << std::endl;
    auto it = fileSystem.find(currentDirectory);
    if (it != fileSystem.end()) {
        for (const std::string& fileName : it->second)
            std::cout << fileName << std::endl;
    }
    else {
        std::cout << "Files not found";
    }
}

/**
 * @brief Changes the current directory to the specified directory.
 *
 * @param directory The directory to change to.
 */
void Terminal::cd(const std::string& directory) {
    if (directory == "..") {
        if (currentDirectory != "/") {
            size_t pos = currentDirectory.find_last_of('/');
            currentDirectory = currentDirectory.substr(0, pos);
            if (currentDirectory.empty() == true) currentDirectory = "/";
        }
    }
    else {
        std::string newPath;
        if (currentDirectory == "/")
            newPath = "/" + directory;
        else
            newPath = currentDirectory + "/" + directory;

        if (fileSystem.contains(newPath)) {
            currentDirectory = newPath;
            std::cout << "Changed directory to: " << currentDirectory << "\n";
        }
        else
            std::cout << "Directory not found\n";
    }
}

/**
 * @brief Prints the current working directory.
 */
void Terminal::pwd() const {
    std::cout << "Current directory: " << currentDirectory << "\n";
}

/**
 * @brief Executes the 'cat' command to display the content of a file.
 *
 * @param input The input containing the file name.
 * @param catFile The map containing the file's content.
 */
void Terminal::cat(const std::string& input, const std::map<std::string, std::vector<std::string>>& catFile) const {
    size_t pos = input.find(' ');
    if (pos != std::string::npos) {
        std::string key = input.substr(pos + 1);
        if (key.size() >= 4 && key.substr(key.size() - 4) == ".txt") {
            auto ex = catFile.find(key);
            if (ex != catFile.end()) {
                std::cout << "Contents of the folder: ";
                for (auto& text : ex->second)
                    std::cout << text << std::endl;
            }
        }
        else
            std::cout << "The file may not exist or is not a .txt file...\n";
    }
    else
        std::cout << "The correct format is: cat <file.txt>\n";
}

/**
 * @brief Friend function to output the Terminal object to an output stream.
 *
 * @param os The output stream.
 * @param terminal The Terminal object to print.
 * @return std::ostream& The output stream after inserting the Terminal object.
 */
std::ostream& operator<<(std::ostream& os, const Terminal& terminal) {
    os << "Current directory: " << terminal.currentDirectory << "\n";
    return os;
}
