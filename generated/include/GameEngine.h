#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "EVERYTHING.h"
#include "Hacker.h"
#include "CryptoHacker.h"
#include "ForensicsHacker.h"
#include "Interface.h"
#include "Level.h"
#include "NetworkingHacker.h"

// GameEngine class: Manages the game flow and interaction between different hacker types.
class GameEngine {
private:
    Hacker &root;
    CryptoHacker cryptoHacker; ///< Instance of CryptoHacker to perform cryptographic tasks.
    ForensicHacker forensicHacker; ///< Instance of ForensicHacker to perform forensic tasks.
    NetworkingHacker networkingHacker; ///< Instance of NetworkingHacker to handle network-related tasks.
    Interface interface; ///< Instance of Interface for user interaction.
    Level level; ///< Instance of Level to manage game progression.
    Terminal terminal; ///< Instance of Terminal for command processing.

    std::ifstream inputFile; ///< Input file stream for reading commands from a file.
    bool readingFromFile; ///< Flag to determine whether commands are being read from a file.
    bool run; ///< Flag to control whether the game engine should keep running.

public:
    /**
     * @brief Constructs the GameEngine with a file containing commands.
     * @param fileName The name of the file containing the commands to be executed.
     */
    explicit GameEngine(const std::string& fileName);

    /**
     * @brief Copy constructor for GameEngine.
     * @param other The GameEngine instance to be copied.
     */
    GameEngine(const GameEngine &other);

    // Deleted default constructor to prevent its use.
    GameEngine() = delete;

    // Default destructor.
    ~GameEngine() = default;

    /**
     * @brief Executes the 'cd' command to change the current directory.
     */
    void executeCdCommand();

    /**
     * @brief Executes the 'cat' command to display the content of a file.
     */
    void executeCATCommand();

    /**
     * @brief Executes the Caesar cipher decryption command.
     * @param inputFile The file stream containing input data to be decrypted.
     * @param readingFromFile Flag indicating whether input is being read from a file.
     */
    void executeCaesarCommand(std::ifstream &inputFile, bool readingFromFile);

    /**
     * @brief Executes the SHA256 hashing command.
     * @param file The file stream containing data to be hashed.
     * @param readingFromFile Flag indicating whether input is being read from a file.
     */
    void executeSHA256Command(std::ifstream &file, bool readingFromFile);

    /**
     * @brief Executes the command to extract metadata from a file.
     * @param file The file stream containing the data to extract metadata from.
     * @param readingFromFile Flag indicating whether input is being read from a file.
     */
    void executeExtractMetadataCommand(std::ifstream &file, bool readingFromFile);

    /**
     * @brief Executes the command to search for a keyword within a file.
     * @param file The file stream to be searched.
     * @param readingFromFile Flag indicating whether input is being read from a file.
     */
    void executeSearchKeywordCommand(std::ifstream &file, bool readingFromFile);

    /**
     * @brief Executes the command to analyze patterns within a file.
     * @param file The file stream containing the data to be analyzed.
     * @param readingFromFile Flag indicating whether input is being read from a file.
     */
    void executeAnalyzePatternsCommand(std::ifstream &file, bool readingFromFile);

    /**
     * @brief Executes the command to scan ports from a given input file.
     * @param inputFileStream The input file stream containing port scan data.
     * @param isReadingFromFile Flag indicating whether input is being read from a file.
     */
    void executePortScanCommand(std::ifstream &inputFileStream, bool isReadingFromFile);

    /**
     * @brief Executes the command to intercept network packets from a given input file.
     * @param inputFileStream The input file stream containing packet interception data.
     * @param isReadingFromFile Flag indicating whether input is being read from a file.
     */
    void executeInterceptPacketsCommand(std::ifstream &inputFileStream, bool isReadingFromFile);

    /**
     * @brief Executes the command to spoof network requests from a given input file.
     * @param inputFileStream The input file stream containing spoof request data.
     * @param isReadingFromFile Flag indicating whether input is being read from a file.
     */
    void executeSpoofRequestCommand(std::ifstream &inputFileStream, bool isReadingFromFile);

    /**
     * @brief Executes the command to capture network traffic from a given input file.
     * @param inputFileStream The input file stream containing traffic capture data.
     * @param isReadingFromFile Flag indicating whether input is being read from a file.
     */
    void executeCaptureTrafficCommand(std::ifstream &inputFileStream, bool isReadingFromFile);

    /**
     * @brief Duplicates the current hacker and prepares for the next instance.
     */
    void duplicateHacker();

    /**
     * @brief Performs a hack based on the current game state.
     */
    void performHack();

    /**
     * @brief Displays the help menu with available commands and their usage.
     * @param fileName The file stream containing help content.
     * @param fileRead Boolean flag indicating whether the help content was successfully read.
     */
    void displayHelp(std::ifstream &fileName, const bool &fileRead);

    /**
     * @brief Executes commands based on user input.
     * @param input The string containing the command to execute.
     */
    void exec_commands(const std::string &input);

    /**
     * @brief Displays the prompt for user input.
     */
    void display_prompt();

    /**
     * @brief Reads commands from a file and executes them.
     */
    void readingCommandsFromFile();

    /**
     * @brief Starts the game engine and initiates the command processing loop.
     */
    void start();
};

#endif
