#include <EVERYTHING.h>
#include "Level.h"
using namespace std;

Level:: Level(int currentLevel) {
    this->currentlevel = currentLevel;
    cout << "LEVEL " << currentLevel;

    if (currentLevel == 1) {
        objective = "Decrypt the MESSAGE, find the PASSWORD, to gain important knowledge about the MOSSAD agent\n";
        catFiles["caesar.txt"] = {"Kdvk wklv phvvdjh zlwk wkh WDUJHW dqg WLPH Dojkrulwp"};
        this->target = "SHAd aku";
        cout << ": TEL AVIV  32.0929 N 34.8072 E..." << "TARGET: " << target << "...TIME 14:56...\n";
    }
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

void Level:: getPassword(int currLevel)  {
    ///VERIFICAM DACA LA FIECARE UTILIZATOR JUCATORUL IDENTIFICA CORECT PAROLA DE LA DIRECTORUL SECRET
    if (currLevel == 1) {
        const string verif = "0ea1c6dd1697dc4e8035da6149a2d680e847a57ff69ee7e73662b507c1a58698";
        cout<<"Please enter the password: ";
        string pass;cin>>pass;
        if(pass == verif) {
            cout<<"You got it\n";
            currLevel+=1;
        }
        else
            cout<<"ACCESS DENIED\n";
    }
}

ostream &operator<<(ostream &os, const Level &level) {
    os<<"Current level is: "<<level.currentlevel;
    os<<"Target is: "<<level.target;
    return os;
}

