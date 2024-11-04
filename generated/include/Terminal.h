#ifndef TERMINAL_H
#define TERMINAL_H
#include "EVERYTHING.h"

using namespace std;
class Terminal {
private:
    map<string, vector<string>> fileSystem;
    string currentDirectory;
public:
    Terminal();
    Terminal(const Terminal& other);
    Terminal &operator=(const Terminal &other);
    friend ostream &operator<<(ostream &os, const Terminal &terminal);
    string getCurrentDirectory();
    void displayPlayerName(const string& playerName);
    static void list_commands_help();

    void ls() const;
    void cd(const string &directory);
    void pwd() const;
    void cat(const string &key, const map<string, vector<string>> &catFile) const;

    ~Terminal() = default;
};


#endif
