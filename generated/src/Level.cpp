#include <EVERYTHING.h>
#include "Level.h"
using namespace std;

Level:: Level(int currentLevel) {
    this->currentlevel = currentLevel;
    cout << "LEVEL " << currentLevel;
    catFiles.clear();

    if (currentLevel == 1) {
        objective = "Your mission is clear: decrypt the message, find the password, and uncover crucial information about the mysterious MOSSAD agent. The clock is ticking...\n";

        catFiles["caesar.txt"] = {"Kdvk wklv phvvdjh zlwk wkh WDUJHW dqg WLPH Dojkrulwp"};

        this->target = "SHAd aku";

        // Atmospheric context for the player
        cout << "------------------------------------------------------------\n";
        cout << "Level 1: The mission begins...\n";
        cout << "Location: TEL AVIV 32.0929° N, 34.8072° E\n";
        cout << "Time: 14:56\n";
        cout << "------------------------------------------------------------\n";
        cout << "Your objective is to decrypt the message. Once decrypted, you'll need to hash it in some way. Your first step is clear...\n";
        cout << "------------------------------------------------------------\n";
        cout << "TARGET: " << target << "...\n";
        cout << "------------------------------------------------------------\n";
    }
    if (currentLevel == 2) {
        objective = "TEST";
        catFiles["file2.txt"] = {"Salut"};
        catFiles["file3.txt"] = {"Hello, contact us at support@example.com.\n Visit https://shorturl.at/UtRvu for more details.Server IP is 192.168.0.1."};
        levelPorts[currentLevel] = {
            {80, true},
            {22, false},
            {443, true},
            {8080, false}
        };
        this->target = "SHAd aku";
        cout << ": TEL AVIV  32.0929 N 34.8072 E..." << "TARGET: " << target << "...TIME 14:56...\n";
    }
}

void Level::setPortsForLevel(int level, const vector<PortStatus>& ports) {
    levelPorts[level] = ports;
}

std::vector<PortStatus> Level::getPortsForLevel(int level) const {
    auto it = levelPorts.find(level);
    if (it != levelPorts.end()) {
        return it->second;
    }
    return {};
}

Level::Level(const Level &level) : Terminal(level) {
    this->currentlevel = level.currentlevel;
    this->objective = level.objective;
    this->target = level.target;
    this->catFiles = level.catFiles;
}

Level & Level::operator=(const Level &level) {
    if(this != &level) {
        currentlevel = level.currentlevel;
        objective = level.objective;
        target = level.target;
        catFiles = level.catFiles;
    }
    return *this;
}

string Level::getObjective() const {return objective;}
map<string, vector<string>> Level:: getCatFiles() {return catFiles;}
int Level:: getCurrentLevel() const {return this->currentlevel;}

bool Level::getPassword(int currLevel)  {
    ///VERIFICAM DACA LA FIECARE UTILIZATOR JUCATORUL IDENTIFICA CORECT PAROLA DE LA DIRECTORUL SECRET
    if (currLevel == 1) {
        const string verif = "0ea1c6dd1697dc4e8035da6149a2d680e847a57ff69ee7e73662b507c1a58698";
        cout<<"Please enter the password: ";
        string pass;cin>>pass;
        if(pass == verif) {
            cout<<"You got it\n";
            currLevel+=1;
            cout << "Level 2 unlocked! New objective coming soon...\n";
            return true;
        }
        else {
            cout<<"ACCESS DENIED\n";
            return false;
        }
    }
    if(currLevel==2) {
        cout<<"Please enter the password: ";
    }
    return false;
}

ostream &operator<<(ostream &os, const Level &level) {
    os<<"Current level is: "<<level.currentlevel;
    os<<"Target is: "<<level.target;
    return os;
}

