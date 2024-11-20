#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "EVERYTHING.h"
#include "Hacker.h"
#include "CryptoHacker.h"
#include "Interface.h"
#include "Level.h"
using namespace std;
class GameEngine {
private:
    Hacker root;
    CryptoHacker cryptohacker;
    Interface interface;
    Level level;
    Terminal terminal;

    ifstream inputFile;
    bool readingFromFile;
    bool run;
public:

    explicit GameEngine(const string& fileName);
    GameEngine(const GameEngine &other);
    GameEngine() = default;
    GameEngine& operator=(const GameEngine &other);

    void executeCdCommand();
    void executeCaesarCommand(ifstream &inputFile, bool readingFromFile);
    void executeSHA256Command(ifstream &file, bool readingFromFile);
    void executeCATCommand();
    void displayHelp(ifstream &fileName, const bool &fileRead);
    void exec_commands(const string &input);

    void display_prompt();
    void readingCommandsFromFile();
    void start();
    ~GameEngine() = default;
};

#endif
