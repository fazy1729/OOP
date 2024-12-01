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
    friend ostream& operator<<(ostream &os, const Hacker &hacker);


    virtual void hack() = 0;

    virtual Hacker* clone() const = 0;  // Pure virtual clone method

    // Afișare virtuală
    virtual void display() const {
        cout << "Hacker of specialization: " << specialization << endl;
        cout << "Skills: " << skills << endl;
    }

    // Afișare non-virtuală
    void showInfo() const {
        cout << "This is a hacker with specialization: " << specialization << endl;
    }

    void printHackerPersonality() const;
    bool checkPersonality(const string &personality);
    string getCommands(const int i, const int j) const;
    bool checkCommandExist(const string &command);
    void help_commands(const int number) const;
    virtual ~Hacker() = default;
};


#endif