#include "GameEngine.h"

GameEngine::GameEngine(const std::string& fileName) :
    root("CryptoHacker", "ROOT"),
    cryptoHacker("1"),
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
    if(pos != std::string::npos) {
        file = file.substr(pos+1);
        std::map<std::string, std::vector<std::string>> catFiles = level.getCatFiles();
        auto it = catFiles.find(file);
        if(it != catFiles.end())
            for(auto &text : it->second)
                cryptoHacker.CaesarDecypher(text);
        else
            std::cout << "File not found" << std::endl;
    }
    else
        std::cout << "The correct format is: --caesar <file.txt>\n";
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
void GameEngine::executeInterceptPacketsCommand(ifstream &inputFileStream, bool isReadingFromFile) {
    vector<string> packets;

    if (isReadingFromFile) {
        string line;
        while (getline(inputFileStream, line)) {
            packets.push_back(line);
        }
    } else {
        cout << "Enter packets to intercept (type 'done' to finish):\n";
        string packet;
        while (true) {
            cout << "Packet: ";
            getline(cin, packet);
            if (packet == "done") break;
            packets.push_back(packet);
        }
    }
    if (level.getCurrentLevel() == 1) {
        packets.push_back("SRC: 192.168.1.1 -> DEST: 10.0.0.1 | DATA: Simple Request");
        packets.push_back("SRC: 10.0.0.1 -> DEST: 192.168.1.1 | DATA: Simple Response");
    } else if (level.getCurrentLevel() == 2) {
        cout << "Level 2: Intercepting more complex packets...\n";
        packets.push_back("SRC: 192.168.1.1 -> DEST: 10.0.0.1 | DATA: LOGIN Request | Protocol: HTTPS");
        packets.push_back("SRC: 10.0.0.1 -> DEST: 192.168.1.1 | DATA: ACK Response | Protocol: HTTPS");
        packets.push_back("SRC: 192.168.1.2 -> DEST: 10.0.0.1 | DATA: FILE Transfer | Protocol: FTP");
    } else if (level.getCurrentLevel() == 3) {
        cout << "Level 3: Intercepting advanced packets with protocol analysis...\n";
        packets.push_back("SRC: 192.168.1.100 -> DEST: 10.0.0.50 | DATA: AUTH Request | Protocol: TLS 1.3");
        packets.push_back("SRC: 10.0.0.50 -> DEST: 192.168.1.100 | DATA: AUTH Response | Protocol: TLS 1.3");
        packets.push_back("SRC: 192.168.2.1 -> DEST: 10.0.0.1 | DATA: DNS Query | Protocol: DNS");
        packets.push_back("SRC: 10.0.0.1 -> DEST: 192.168.2.1 | DATA: DNS Response | Protocol: DNS");
    }

    networkingHacker.InterceptPackets(packets);
}

void GameEngine::executeSpoofRequestCommand(ifstream &inputFileStream, bool isReadingFromFile) {
    string targetIP, message;

    if (isReadingFromFile) {
        if (!getline(inputFileStream, targetIP) || !getline(inputFileStream, message)) {
            cout << "Error reading from file." << endl;
            return;
        }
    } else {
        cout << "Enter target IP: ";
        getline(cin, targetIP);
        cout << "Enter message to spoof: ";
        getline(cin, message);
    }

    if (level.getCurrentLevel() == 1) {
        cout << "Level 1: Spoofing simple request...\n";
    } else if (level.getCurrentLevel() == 2) {
        cout << "Level 2: Spoofing advanced request...\n";
    } else if (level.getCurrentLevel() == 3) {
        cout << "Level 3: Spoofing very sophisticated request...\n";
    }

    networkingHacker.SpoofRequest(targetIP, message);
}

void GameEngine::executeCaptureTrafficCommand(ifstream &inputFileStream, bool isReadingFromFile) {
    vector<string> trafficLogs;
    if (isReadingFromFile) {
        string line;
        while (getline(inputFileStream, line)) {
            trafficLogs.push_back(line);
        }
    } else {
        cout << "Enter traffic logs (type 'done' to finish):\n";
        string log;
        while (true) {
            cout << "Log: ";
            getline(cin, log);
            if (log == "done") break;
            trafficLogs.push_back(log);
        }
    }

    if (level.getCurrentLevel() == 1) {
        cout << "Level 1: Capturing simple traffic logs...\n";
        trafficLogs.push_back("IP: 192.168.0.1 SENT: 100 bytes");
        trafficLogs.push_back("IP: 192.168.1.3 SENT: 200 bytes");
    } else if (level.getCurrentLevel() == 2) {
        cout << "Level 2: Capturing more complex traffic logs...\n";
        trafficLogs.push_back("IP: 192.168.1.1 SENT: 500 bytes | Protocol: HTTP");
        trafficLogs.push_back("IP: 10.0.0.1 SENT: 1000 bytes | Protocol: HTTPS");
    } else if (level.getCurrentLevel() == 3) {
        cout << "Level 3: Capturing advanced traffic with detailed analysis...\n";
        trafficLogs.push_back("IP: 192.168.1.100 SENT: 2000 bytes | Protocol: TLS 1.3");
        trafficLogs.push_back("IP: 10.0.0.50 SENT: 1500 bytes | Protocol: FTP");
    }

    networkingHacker.CaptureTraffic(trafficLogs);
}

void GameEngine::exec_commands(const string &input) {
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
        cout << level.getObjective();
    else if (input == "--exit")
        run = false;
    else {
        cout << "Command not found... Type --help to see the list of commands..." << endl;
        run = false;
    }
}

void GameEngine::display_prompt() {
    string playerName = interface.getPlayerName();
    terminal.displayPlayerName(playerName);
}

void GameEngine::readingCommandsFromFile() {
    string commandLine;
    while (getline(inputFile, commandLine)) {
        display_prompt();
        cout << "Executing from file: " << commandLine << endl;
        exec_commands(commandLine);
    }
    readingFromFile = false;
    inputFile.close();
}

void GameEngine::start() {
    while (run) {
        display_prompt();
        if (readingFromFile)
            readingCommandsFromFile();
        else {
            string input;
            cin >> input;
            exec_commands(input);
        }
    }
}

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
            cerr << "Unable to open file tastatura.txt" << endl;
            readingFromFile = false;
        }
    }
}
