#ifndef LEVEL_H
#define LEVEL_H

#include "EVERYTHING.h"
#include "Terminal.h"

using namespace std;

class Level : public Terminal {
private:
    int currentlevel;
    string objective;
    string target;

    map<string, vector<string>> catFiles;

public:
    explicit Level(int currentLevel);
    Level() = default;
    Level(const Level& level);
    friend ostream& operator<<(ostream &os, const Level &level);
    Level& operator=(const Level& level);
    string getObjective() const;
    map<string, vector<string>> getCatFiles();
    int getCurrentLevel() const;

    static void getPassword(int currLevel);


    ~Level() = default;

};

#endif
