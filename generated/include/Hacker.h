#ifndef HACKER_H
#define HACKER_H

#include "EVERYTHING.h"

using namespace std;

class Hacker {
private:
    string specialization;
    string skills;
    string commands_list[3][3];
    string hacker_personality[3];

public:
    Hacker() = default;
    Hacker(const string &specialization,const string &skills);
    Hacker(const Hacker &other);
    Hacker& operator=(const Hacker &other);
    void printHackerPersonality() const;
    bool checkPersonality(const string &personality);
    string getCommands(const int i, const int j) const;
    bool checkCommandExist(const string &command);
    void help_commands(const int number) const;
    virtual ~Hacker() = default;
};


#endif
