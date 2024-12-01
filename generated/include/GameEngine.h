#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "EVERYTHING.h"
#include "Hacker.h"
#include "CryptoHacker.h"
#include "ForensicsHacker.h"
#include "Interface.h"
#include "Level.h"
#include "NetworkingHacker.h"
using namespace std;
class GameEngine {
private:
    Hacker &root;
    CryptoHacker cryptoHacker;
    ForensicHacker forensicHacker;
    NetworkingHacker networkingHacker;
    Interface interface;
    Level level;
    Terminal terminal;

    ifstream inputFile;
    bool readingFromFile;
    bool run;
public:

    explicit GameEngine(const string& fileName);
    GameEngine(const GameEngine &other);
    GameEngine() = delete;
    ~GameEngine() = default;

    void executeCdCommand();
    void executeCATCommand();

    void executeCaesarCommand(ifstream &inputFile, bool readingFromFile);
    void executeSHA256Command(ifstream &file, bool readingFromFile);


    void executeExtractMetadataCommand(ifstream &file, bool readingFromFile);
    void executeSearchKeywordCommand(ifstream &file, bool readingFromFile);
    void executeAnalyzePatternsCommand(ifstream &file, bool readingFromFile);


    void executePortScanCommand(ifstream &inputFileStream, bool isReadingFromFile);
    void executeInterceptPacketsCommand(ifstream &inputFileStream, bool isReadingFromFile);
    void executeSpoofRequestCommand(ifstream &inputFileStream, bool isReadingFromFile);
    void executeCaptureTrafficCommand(ifstream &inputFileStream, bool isReadingFromFile);



    void duplicateHacker();
    void performHack();
    void displayHelp(ifstream &fileName, const bool &fileRead);
    void exec_commands(const string &input);
    void display_prompt();
    void readingCommandsFromFile();
    void start();

};

#endif