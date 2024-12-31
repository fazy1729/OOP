#include "GameEngine.h"
#include "HackerExceptions.h"

GameEngine::GameEngine(const std::string& fileName) :
    root(cryptoHacker),
    cryptoHacker("Crypto Skills"),
    forensicHacker("Forensic Skills"),
    networkingHacker("Networking Skills"),
    interface(fileName),
    level(1),
    readingFromFile(true),
    run(true)

{
    std::ifstream tempInputFile;
    tempInputFile.open("tastatura.txt");
    if (!tempInputFile) {
        std::cerr << "Unable to open file " << fileName << std::endl;
        readingFromFile = false;
    } else {
        inputFile = std::move(tempInputFile);
    }

}



void GameEngine::executeCdCommand() {
    std::string dir;
    std::getline(std::cin, dir);

    std::size_t poz = dir.find(' ');

    if (poz != std::string::npos) {
        dir = dir.substr(poz + 1);
        if (dir != "SECRET") {
            terminal.cd(dir);
        } else {
            bool correctPassword = level.getPassword(level.getCurrentLevel());

            if (correctPassword) {
                if (level.getCurrentLevel() == 1) {
                    std::cout << "Congratulations! You've advanced to Level 2!\n";
                    level = Level(2);
                    std::cout << level.getObjective() << std::endl;
                }
            } else {
                std::cout << "You cannot advance to the next level. Try again.\n";
            }
        }
    } else {
        std::cout << "The correct format is: cd <directory>\n";
    }
}

void GameEngine::executeCaesarCommand(std::ifstream &inputFileStream, bool isReadingFromFile) {
    std::string file;
    if (isReadingFromFile == false)
        std::getline(std::cin, file);
    else {
        std::cout << "You entered: " << file << "\n";
        std::getline(inputFileStream, file);
    }

    std::size_t pos = file.find(' ');
    if (pos != std::string::npos) {
        file = file.substr(pos + 1);
        std::map<std::string, std::vector<std::string>> catFiles = level.getCatFiles();
        auto it = catFiles.find(file);
        if (it != catFiles.end()) {
            for (auto &text : it->second) {
                cryptoHacker.CaesarDecypher(text);
            }
            logger.log("Executed Caesar cipher on file: " + file);  // Logare succes
        } else {
            logger.log("File not found: " + file);  // Logare eroare
            std::cout << "File not found" << std::endl;
        }
    } else {
        logger.log("Invalid command format for Caesar cipher");  // Logare eroare
        std::cout << "The correct format is: --caesar <file.txt>\n";
    }
}


void GameEngine::executeSHA256Command(std::ifstream &inputFileStream, bool isReadingFromFile) {
    std::string fileName;
    if(isReadingFromFile == false)
        std::getline(std::cin, fileName);
    else
        std::getline(inputFileStream, fileName);

    std::size_t pos = fileName.find(' ');
    if(pos != std::string::npos) {
        fileName = fileName.substr(pos+1);
        std::string hash = cryptoHacker.SHA256(fileName, level.getCatFiles());
        std::cout << "SHA256 hash: " << hash << std::endl;
    }
    else
        std::cout << "The correct format is: --sha256 <file.txt>\n";
}

void GameEngine::performHack() {
    std::cout << "Initiating hack...\n";
    root.hack();  // Calls the correct hack() method based on root's type
}

void GameEngine::executeCATCommand() {
    std::string file;
    std::getline(std::cin, file);
    terminal.cat(file, level.getCatFiles());
}

void GameEngine::displayHelp(std::ifstream &inputFileStream, const bool &isFileRead) {
    std::cout << "HOW MIGHT I HELP YOU TODAY?" << std::endl;
    std::cout << "1. List of personalities: " << std::endl;
    std::cout << "2. List of commands: " << std::endl;
    std::cout << "Enter a number:";

    int number;
    if(isFileRead == false)
        std::cin >> number;
    else {
        inputFileStream >> number;
        std::cout << "You've entered number " << number << "\n";
    }
    if(number == 1) {
        std::cout << "Enter your personality from the list: " << std::endl;

        root.printHackerPersonality();
        int hackerPersonality;

        std::cout << "Enter a number from the list: ";
        if(isFileRead == false)
            std::cin >> hackerPersonality;
        else {
            inputFileStream >> hackerPersonality;
            std::cout << "You've entered number " << hackerPersonality << "\n";
        }
        if( (hackerPersonality == 1 || hackerPersonality == 2) || hackerPersonality == 3)
            root.help_commands(hackerPersonality);
        else {
            std::cout << "That was a nice try, writing a name that is not in a list... You lost...";
            run = false;
        }
    }
    else if(number == 2)
        terminal.list_commands_help();

    else {
        std::cout << "You tried to trick me by inserting something else than a number... Dissapointing...";
        run = false;
    }
}

void GameEngine::executeExtractMetadataCommand(std::ifstream &inputFileStream, bool isReadingFromFile) {
    std::string fileName;
    if (isReadingFromFile)
        std::getline(inputFileStream, fileName);
    else {
        std::cout << "Enter the file name: ";
        std::getline(std::cin, fileName);
    }

    std::size_t pos = fileName.find(' ');
    if (pos != std::string::npos) {
        fileName = fileName.substr(pos + 1);
        forensicHacker.ExtractMetadata(fileName, level.getCatFiles());
    } else {
        std::cout << "The correct format is: --extract-metadata <file.txt>\n";
    }
}

void GameEngine::executeSearchKeywordCommand(std::ifstream &inputFileStream, bool isReadingFromFile) {
    std::string input;
    std::string input2;
    std::string keyword;
    if(isReadingFromFile == false)
        std::getline(std::cin, input);
    else
        std::getline(inputFileStream ,input);
    std::size_t start = input.find(' ');
    std::size_t start2 = input.find(' ', start+1);
    if (start != std::string::npos and start2 != std::string::npos) {
        input2 = input.substr(start+1, start2-start-1);
        keyword = input.substr(start2+1);
        forensicHacker.SearchKeyword(input2, keyword, level.getCatFiles());
    }
    else
        std::cout << "The correct format is: --search-keyword <file.txt> <keyword>\n";
}

void GameEngine::executeAnalyzePatternsCommand(std::ifstream &inputFileStream, bool isReadingFromFile) {
    std::string input;
    if(isReadingFromFile == false)
        std::getline(std::cin, input);
    else
        std::getline(inputFileStream ,input);

    std::size_t startPos = input.find(' ');
    if (startPos != std::string::npos) {
        input = input.substr(startPos + 1);
        forensicHacker.AnalyzeFilePatterns(input, level.getCatFiles());
    }
    else
        std::cout << "The correct format is: --analyze-patterns <file.txt>\n";
}

void GameEngine::executePortScanCommand(std::ifstream &inputFileStream, bool isReadingFromFile) {
    std::string target;
    if (isReadingFromFile)
        std::getline(inputFileStream, target);
    else {
        std::cout << "Enter target IP or hostname: ";
        std::getline(std::cin, target);
    }

    std::vector<int> ports = {22, 80, 443, 8080, 3306};
    networkingHacker.SimulatePortScan(target, ports, level);
}
/**
 * @brief Executes the --intercept-packets command by collecting packet data and invoking the appropriate method.
 *
 * @param inputFileStream The input stream for reading data from file if necessary.
 * @param isReadingFromFile Flag indicating whether commands are being read from a file.
 */
void GameEngine::executeInterceptPacketsCommand(std::ifstream &inputFileStream, bool isReadingFromFile) {
    std::vector<std::string> packets;

    if (isReadingFromFile) {
        std::string line;
        while (std::getline(inputFileStream, line)) {
            packets.push_back(line);
        }
    } else {
        std::cout << "Enter packets to intercept (type 'done' to finish):\n";
        std::string packet;
        while (true) {
            std::cout << "Packet: ";
            std::getline(std::cin, packet);
            if (packet == "done") break;
            packets.push_back(packet);
        }
    }
    if (level.getCurrentLevel() == 1) {
        packets.push_back("SRC: 192.168.1.1 -> DEST: 10.0.0.1 | DATA: Simple Request");
        packets.push_back("SRC: 10.0.0.1 -> DEST: 192.168.1.1 | DATA: Simple Response");
    } else if (level.getCurrentLevel() == 2) {
        std::cout << "Level 2: Intercepting more complex packets...\n";
        packets.push_back("SRC: 192.168.1.1 -> DEST: 10.0.0.1 | DATA: LOGIN Request | Protocol: HTTPS");
        packets.push_back("SRC: 10.0.0.1 -> DEST: 192.168.1.1 | DATA: ACK Response | Protocol: HTTPS");
        packets.push_back("SRC: 192.168.1.2 -> DEST: 10.0.0.1 | DATA: FILE Transfer | Protocol: FTP");
    } else if (level.getCurrentLevel() == 3) {
        std::cout << "Level 3: Intercepting advanced packets with protocol analysis...\n";
        packets.push_back("SRC: 192.168.1.100 -> DEST: 10.0.0.50 | DATA: AUTH Request | Protocol: TLS 1.3");
        packets.push_back("SRC: 10.0.0.50 -> DEST: 192.168.1.100 | DATA: AUTH Response | Protocol: TLS 1.3");
        packets.push_back("SRC: 192.168.2.1 -> DEST: 10.0.0.1 | DATA: DNS Query | Protocol: DNS");
        packets.push_back("SRC: 10.0.0.1 -> DEST: 192.168.2.1 | DATA: DNS Response | Protocol: DNS");
    }

    networkingHacker.InterceptPackets(packets);
}

/**
 * @brief Executes the --spoof-request command by collecting target IP and message, and invoking the appropriate method.
 *
 * @param inputFileStream The input stream for reading data from file if necessary.
 * @param isReadingFromFile Flag indicating whether commands are being read from a file.
 */
void GameEngine::executeSpoofRequestCommand(std::ifstream &inputFileStream, bool isReadingFromFile) {
    std::string targetIP, message;

    if (isReadingFromFile) {
        if (!std::getline(inputFileStream, targetIP) || !std::getline(inputFileStream, message)) {
            std::cout << "Error reading from file." << std::endl;
            return;
        }
    } else {
        std::cout << "Enter target IP: ";
        std::getline(std::cin, targetIP);
        std::cout << "Enter message to spoof: ";
        std::getline(std::cin, message);
    }

    if (level.getCurrentLevel() == 1) {
        std::cout << "Level 1: Spoofing simple request...\n";
    } else if (level.getCurrentLevel() == 2) {
        std::cout << "Level 2: Spoofing advanced request...\n";
    } else if (level.getCurrentLevel() == 3) {
        std::cout << "Level 3: Spoofing very sophisticated request...\n";
    }

    networkingHacker.SpoofRequest(targetIP, message);
}

/**
 * @brief Executes the --capture-traffic command by collecting traffic log data and invoking the appropriate method.
 *
 * @param inputFileStream The input stream for reading data from file if necessary.
 * @param isReadingFromFile Flag indicating whether commands are being read from a file.
 */
void GameEngine::executeCaptureTrafficCommand(std::ifstream &inputFileStream, bool isReadingFromFile) {
    std::vector<std::string> trafficLogs;
    if (isReadingFromFile) {
        std::string line;
        while (std::getline(inputFileStream, line)) {
            trafficLogs.push_back(line);
        }
    } else {
        std::cout << "Enter traffic logs (type 'done' to finish):\n";
        std::string log;
        while (true) {
            std::cout << "Log: ";
            std::getline(std::cin, log);
            if (log == "done") break;
            trafficLogs.push_back(log);
        }
    }

    if (level.getCurrentLevel() == 1) {
        std::cout << "Level 1: Capturing simple traffic logs...\n";
        trafficLogs.push_back("IP: 192.168.0.1 SENT: 100 bytes");
        trafficLogs.push_back("IP: 192.168.1.3 SENT: 200 bytes");
    } else if (level.getCurrentLevel() == 2) {
        std::cout << "Level 2: Capturing more complex traffic logs...\n";
        trafficLogs.push_back("IP: 192.168.1.1 SENT: 500 bytes | Protocol: HTTP");
        trafficLogs.push_back("IP: 10.0.0.1 SENT: 1000 bytes | Protocol: HTTPS");
    } else if (level.getCurrentLevel() == 3) {
        std::cout << "Level 3: Capturing advanced traffic with detailed analysis...\n";
        trafficLogs.push_back("IP: 192.168.1.100 SENT: 2000 bytes | Protocol: TLS 1.3");
        trafficLogs.push_back("IP: 10.0.0.50 SENT: 1500 bytes | Protocol: FTP");
    }

    networkingHacker.CaptureTraffic(trafficLogs);
}

/**
 * @brief Executes commands based on user input.
 *
 * @param input The command input by the user.
 */
void GameEngine::exec_commands(const std::string &input) {
    try {
        if (input == "ls")
            terminal.ls();
        else if (input == "pwd")
            terminal.pwd();
        else if (input == "cd")
            executeCdCommand();
        else if (input == "--caesar")
            executeCaesarCommand(inputFile, readingFromFile);
        else if (input == "--sha256")
            executeSHA256Command(inputFile, readingFromFile);
        else if (input == "cat")
            executeCATCommand();
        else if (input == "--help")
            displayHelp(inputFile, readingFromFile);
        else if (input == "--extract-metadata")
            executeExtractMetadataCommand(inputFile, readingFromFile);
        else if (input == "--search-keyword")
            executeSearchKeywordCommand(inputFile, readingFromFile);
        else if (input == "--analyze-patterns")
            executeAnalyzePatternsCommand(inputFile, readingFromFile);
        else if (input == "--port-scan")
            executePortScanCommand(inputFile, readingFromFile);
        else if (input == "--intercept-packets")
            executeInterceptPacketsCommand(inputFile, readingFromFile);
        else if (input == "--spoof-request")
            executeSpoofRequestCommand(inputFile, readingFromFile);
        else if (input == "--capture-traffic")
            executeCaptureTrafficCommand(inputFile, readingFromFile);
        else if (input == "--objective")
            std::cout << level.getObjective();
        else if(input == "--perform-hack")
            performHack();
        else if (input == "--exit")
            run = false;
        else {
                ///run = false;
            throw InvalidCommandException(input);
        }
        logger.log("Command executed successfully: " + input);
    }
    catch (const InvalidCommandException& e) {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Please type --help to see the list of available commands." << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "An unexpected error occurred: " << e.what() << std::endl;
    }
}

/**
 * @brief Displays the prompt with the player's name and current directory.
 */
void GameEngine::display_prompt() {
    std::string playerName = interface.getPlayerName();
    terminal.displayPlayerName(playerName);
}

/**
 * @brief Reads commands from a file and executes them.
 */
void GameEngine::readingCommandsFromFile() {
    std::string commandLine;
    while (std::getline(inputFile, commandLine)) {
        display_prompt();
        std::cout << "Executing from file: " << commandLine << std::endl;
        exec_commands(commandLine);
    }
    readingFromFile = false;
    inputFile.close();
}

/**
 * @brief Starts the game engine and runs it in a loop until the `run` flag is set to false.
 *
 * The method displays the prompt, reads the command from the input (either from file or from console),
 * and executes the appropriate command.
 */
void GameEngine::start() {
    while (run) {
        display_prompt();
        if (readingFromFile)
            readingCommandsFromFile();
        else {
            std::string input;
            std::cin >> input;
            exec_commands(input);
        }
    }
}

/**
 * @brief Copy constructor for creating a new `GameEngine` from another instance.
 *
 * This constructor performs a deep copy of the attributes of another `GameEngine` object.
 * It also attempts to open the input file if the `readingFromFile` flag is true.
 *
 * @param other The `GameEngine` instance to copy.
 */
GameEngine::GameEngine(const GameEngine &other)
    : root(other.root),
      cryptoHacker(other.cryptoHacker),
      interface(other.interface),
      level(other.level),
      readingFromFile(other.readingFromFile),
      run(other.run) {
    if (readingFromFile && other.inputFile.is_open()) {
        inputFile.open("tastatura.txt");
        if (!inputFile) {
            std::cerr << "Unable to open file tastatura.txt" << std::endl;
            readingFromFile = false;
        }
    }
}


void GameEngine::duplicateHacker() {
    Hacker* clonedHacker = root.clone();
    clonedHacker->hack();
    delete clonedHacker;
}