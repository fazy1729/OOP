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
    tempInputFile.open(R"(D:\CloneProjectsGIT\proiect_oop\OOP\tastatura.txt)");
    if (!tempInputFile) {
        std::cerr << "Unable to open file " << fileName << std::endl;
        readingFromFile = false;
    } else {
        inputFile = std::move(tempInputFile);
    }
}

void GameEngine::executeCdCommand() {
    // FACEM CD DIN LINUX - EFECTIV NE PLIMBAM PRIN HASHMAP
    std::string dir;
    std::getline(std::cin, dir);
    std::size_t poz = dir.find(' ');
    if(poz != std::string::npos) {
        dir = dir.substr(poz + 1);
        if(dir != "SECRET")
            terminal.cd(dir);
        else
            level.getPassword(level.getCurrentLevel());
    }
    else
        std::cout << "The correct format is: cd <directory>\n";
}

void GameEngine::executeCaesarCommand(std::ifstream &inputFileStream, bool isReadingFromFile) {
    // EXECUTAM ALGORITMUL CEZAR
    std::string file;
    if (isReadingFromFile == false)
        std::getline(std::cin, file);
    else {
        std::cout << "You entered: " << file << "\n";
        std::getline(inputFileStream, file);
    }
    std::size_t pos = file.find(' ');
    if(pos != std::string::npos) {
        file = file.substr(pos + 1);
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
    // EXECUTAM ALGORITMUL DE HASHING
    std::string fileName;
    if(isReadingFromFile == false)
        std::getline(std::cin, fileName);
    else
        std::getline(inputFileStream, fileName);

    std::size_t pos = fileName.find(' ');
    if(pos != std::string::npos) {
        fileName = fileName.substr(pos + 1);
        std::string hash = cryptoHacker.SHA256(fileName, level.getCatFiles());
        std::cout << "SHA256 hash: " << hash << std::endl;
    }
    else
        std::cout << "The correct format is: --sha256 <file.txt>\n";
}

void GameEngine::executeCATCommand() {
    // COMANDA CAT EFECTIV NE ARATA CE SE AFLA IN CHEIA MAPULUI
    std::string file;
    std::getline(std::cin, file);
    terminal.cat(file, level.getCatFiles());
}

void GameEngine::displayHelp(std::ifstream &inputFileStream, const bool &isFileRead) {
    // PREZENTARE DIVERSE FUNCTII CARE EXISTA PE BAZA CATEGORIEI DIN CARE FAC PARTE
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
    std::size_t start2 = input.find(' ', start + 1);
    if (start != std::string::npos and start2 != std::string::npos) {
        input2 = input.substr(start + 1, start2 - start - 1);
        keyword = input.substr(start2 + 1);
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
    // Trim leading spaces
    std::size_t startPos = input.find(' ');
    if (startPos != std::string::npos) {
        input = input.substr(startPos + 1);
        forensicHacker.AnalyzeFilePatterns(input, level.getCatFiles());
    }
    else
        std::cout << "The correct format is: --analyze-patterns <file.txt>\n";
}

void GameEngine::exec_commands(const std::string &input) {
    // IN FUNCTIE DE INPUT-UL UTILIZATORIULUI EXECUTAM COMANDA, DACA NU EXISTA ATUNCI NE VA AFISA UN MESAJ CORESPUNZATOR
    if(input == "ls")
        terminal.ls();
    else if(input == "pwd")
        terminal.pwd();
    else if(input == "cd")
        executeCdCommand();
    else if(input == "--caesar")
        executeCaesarCommand(inputFile, readingFromFile);
    else if(input == "--sha256")
        executeSHA256Command(inputFile, readingFromFile);
    else if(input == "cat")
        executeCATCommand();
    else if(input == "--help")
        displayHelp(inputFile, readingFromFile);
    else if (input == "--extract-metadata")
        executeExtractMetadataCommand(inputFile, readingFromFile);
    else if (input == "--search-keyword")
        executeSearchKeywordCommand(inputFile, readingFromFile);
    else if (input == "--analyze-patterns")
        executeAnalyzePatternsCommand(inputFile, readingFromFile);
    else if(input == "--objective")
        std::cout << level.getObjective();
    else if(input == "--exit")
        run = false;
    else {
        std::cout << "Command not found... Type --help to see the list of commands..." << std::endl;
        run = false;
    }
}

void GameEngine::display_prompt() {
    // NE ARATA PROMPTUL
    std::string playerName = interface.getPlayerName();
    terminal.displayPlayerName(playerName);
}

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

void GameEngine::start() {
    while(run) {
        display_prompt();
        if(readingFromFile)
            readingCommandsFromFile();
        else {
            std::string input;
            std::cin >> input;
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
      run(other.run)
{
    if (readingFromFile && other.inputFile.is_open()) {
        inputFile.open("tastatura.txt");
        if (!inputFile) {
            std::cerr << "Unable to open file tastatura.txt" << std::endl;
            readingFromFile = false;
        }
    }
}

GameEngine& GameEngine::operator=(const GameEngine &other) {
    if (this != &other) {
        root = other.root;
        cryptoHacker = other.cryptoHacker;
        level = other.level;
        readingFromFile = other.readingFromFile;
        run = other.run;

        if (inputFile.is_open()) {
            inputFile.close();
        }
        if (readingFromFile && other.readingFromFile) {
            inputFile.open(R"(D:\CloneProjectsGIT\proiect_oop\OOP\tastatura.txt)");
            if (!inputFile) {
                std::cerr << "Unable to open file tastatura.txt" << std::endl;
                readingFromFile = false;
            }
        }
    }
    return *this;
}
