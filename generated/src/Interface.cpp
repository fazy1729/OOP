#include "Interface.h"

Interface::Interface(const string& fileName) {
    // Welcome message to engage the player
    cout << "------------------------------------------------------------\n";
    cout << "WELCOME TO INTRUSION\n";
    cout << "------------------------------------------------------------\n";
    cout << "At any time, you can type --help to view the available commands, or --exit to quit the game.\n\n";
    cout << "Your mission: Infiltrate the SECRET directory. The path to it is hidden within a series of puzzles. Solve them to obtain the PASSWORD, which will unlock the folder and reveal critical information.\n\n";
    cout << "If you need assistance at any time, simply use the --objective command to remind yourself of your task.\n\n";
    cout << "------------------------------------------------------------\n";
    cout << "Please enter your name to begin your mission: \n\n";

    // Reading player name from the file
    inputFile.open(fileName);
    getline(inputFile, name);

    cout << "Welcome, " << name << ". Your journey begins now...\n";
    cout << "------------------------------------------------------------\n";
}


Interface::Interface(const Interface& other) : name(other.name) {}
string Interface::getPlayerName() const {
    return name;
}
Interface& Interface::operator=(const Interface& other) {
    if(this != &other) {
        name = other.name;
        if (inputFile.is_open()) {
            inputFile.close();
        }

    }
    return *this;

}

ostream& operator<<(ostream& os, const Interface& obj) {
    os << "Your name is: " << obj.name;
    return os;
}
