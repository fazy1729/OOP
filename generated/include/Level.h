#ifndef LEVEL_H
#define LEVEL_H

#include "EVERYTHING.h"
#include "Terminal.h"

using namespace std;
struct PortStatus {
    int port;
    bool isOpen;
};

class Level : public Terminal {
private:
    int currentlevel;
    string objective;
    string target;

    map<int, vector<PortStatus>> levelPorts;
    map<string, vector<string>> catFiles;

public:
    explicit Level(int currentLevel);
    Level() = default;
    Level(const Level& level);
    friend ostream& operator<<(ostream &os, const Level &level);
    Level& operator=(const Level& level);
    string getObjective() const;
    map<string, vector<string>> getCatFiles();
    void setPortsForLevel(int level, const vector<PortStatus>& ports);
    vector<PortStatus> getPortsForLevel(int level) const;
    int getCurrentLevel() const;

    bool getPassword(int currLevel);


    ~Level() = default;

};

#endif
